#include "Core.h"
#include "CoreConfig.h"

#include <math/Spatial.h>

#include "plugins/PluginRegistry.h"
#include <plugins/CorePluginInterface.h>
#include "plugins/PluginManager.h"
#include <fmt/core.h>
#include <AbstractScheduler.h>
#include <AbstractTaskQueue.h>
#include <scenes/SimpleScene.h>




using namespace msge;

void Core::initializeLogging(const CommandLineArgs& cmdLineArgs)
{
    FLAGS_alsologtostderr    = 1;
    FLAGS_colorlogtostderr   = 1;
    FLAGS_log_year_in_prefix = false;
    FLAGS_stderrthreshold    = google::GLOG_WARNING;
    FLAGS_logbuflevel        = -1;

    try
    {
        std::filesystem::create_directory("logs");
        google::SetLogDestination(google::GLOG_INFO, "logs/info.log");
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Cannot create log directory at 'logs':" << e.what() << std::endl;
        google::SetLogDestination(google::GLOG_INFO, "info.log");
    }

    google::InitGoogleLogging(cmdLineArgs.at(0).data());

    LOG(INFO) << fmt::format("Starting Core (build: {0}/{1} )", __TIMESTAMP__, __DATE__);
}

Core::CommandLineArgs Core::makeCommandLineArgs(int argc, char** argv)
{
    return CommandLineArgs(argv, argv + argc);
}

void Core::setup(const CoreConfig& config, const CommandLineArgs& args)
{
    initializeLogging(args);

    pluginManager->scanForPlugins(config.plugins_path);
  
    for (const auto& [k, v] : pluginManager->getPluginList())
    {
        v->registerPlugin(*this);
    }    

    //scenes from configuration
    rootScenes.insert({SceneId(config.default_scene), std::make_unique<SimpleScene>("root")});

    scheduler = schedulerPrototypes.getPrototype(config.scheduler_name)();
    taskQueue = taskQueuePrototypes.getPrototype(config.task_queue_name)();
    scheduler->setTaskQueue(taskQueue);
}

Core::Core(const CoreConfig& config, const CommandLineArgs& args)
    : pluginRegistry(std::make_unique<plugins::PluginRegistry>())
    , pluginManager(std::make_unique<CorePluginManager>())
{
    setup(config, args);
}

void Core::addTask(std::string_view name, std::function<void(const FrameStamp&)> f)
{
    taskQueue->addTask(std::make_unique<FunctionTask>(f, TaskProperties{std::string(name)}));
}

std::future<void> Core::start()
{
    scheduler->start();
    return std::async(std::launch::async, [this]() { scheduler->run(); });   
}

Core::~Core() = default;

