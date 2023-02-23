#include "Core.h"

#include "CoreConfig.h"
#include "plugins/PluginManager.h"
#include "plugins/PluginRegistry.h"

#include <AbstractScheduler.h>
#include <AbstractTaskQueue.h>
#include <fmt/core.h>
#include <math/Spatial.h>
#include <plugins/CorePluginInterface.h>
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
    switch  (config.plugins.loadTypes)
    {
    case CoreConfig::Plugins::PluginTypes::ALL:
        pluginManager->scanForPlugins(config.plugins.path, config.plugins.filter);
        break;
    case CoreConfig::Plugins::PluginTypes::DEFAULT:
        LOG(INFO) << fmt::format("Skipping load of user plugins and all set filters.");
        pluginManager->scanForPlugins(config.plugins.path + "/default" );
        break;
    case CoreConfig::Plugins::PluginTypes::NONE:
        LOG(WARNING) << fmt::format("Skipping load of all plugins.");
        break;

    }


    for (const auto& [k, v] : pluginManager->getPluginList())
    {
        v->registerPlugin(*this);
    }

    // scenes from configuration
    rootScenes.insert({SceneId(config.default_scene), std::make_unique<SimpleScene>("root")});

    scheduler = schedulerPrototypes.getPrototype(config.scheduler_name)();
    taskQueue = taskQueuePrototypes.getPrototype(config.task_queue_name)();
    scheduler->setTaskQueue(taskQueue);
}

Core::Core(const CoreConfig& config, const CommandLineArgs& args)
    : pluginManager(std::make_unique<CorePluginManager>())
    , pluginRegistry(std::make_unique<plugins::PluginRegistry>())
{
    setup(config, args);
}

void Core::addTask(std::string_view name, std::function<void(const FrameStamp&)>&& f)
{
    taskQueue->addTask(std::make_unique<FunctionTask>(std::move(f), TaskProperties{std::string(name)}));
}

std::future<void> Core::start()
{
    scheduler->start();
    return std::async(std::launch::async, [this]() { scheduler->run(); });
}

Core::~Core() = default;
