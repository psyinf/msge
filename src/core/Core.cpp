#include "Core.h"

#include "Spatial.h"

#include "plugins/PluginRegistry.h"
#include <plugins/CorePluginInterface.h>
#include "plugins/PluginManager.h"
#include <fmt/core.h>

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

void Core::setup(const Config& config, const CommandLineArgs& args)
{
    initializeLogging(args);
    pluginManager->scanForPlugins(config.plugins_path);
    //#TODO remove DEBUG code for testing: intialize plugins and move this to a "smoke"test
    for (auto& [k, v] : pluginManager->getPluginList())
    {
        v->registerPlugin(*pluginRegistry);
    } 
    auto jsonSerializer = pluginRegistry->getCoreVisitorPrototype("JsonSerializer", *this);
    
}

Core::Core(const Config& config, const CommandLineArgs& args)
    : pluginRegistry(std::make_unique<plugins::PluginRegistry>())
    , pluginManager(std::make_unique<CorePluginManager>())
{
    setup(config, args);
}



Core::~Core() = default;

