#include "Core.h"

#include "Spatial.h"
#include "plugins/PluginManager.h"


using namespace msge;

void Core::initializeLogging(const std::vector<std::string_view>& cmdLineArgs)
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

    LOG(INFO) << std::format("Starting Core (build: {0}/{1} )", __TIMESTAMP__, __DATE__);
}

void Core::setup(const Config& config)
{
    //TODO: load plugins and register
    //1. plugins for serializiation backends (JSON, protobuffer, ..)
    //2. plugins for sending data to external receivers (rendering backends, distributed computing, ...)
}
