#include <glog/logging.h>
#include <plugins/PluginBase.h>
#include <plugins/PluginRegistry.h>
#include <serializer/JsonSerializer.h>
#include <string>

//TODO move to a macro
#ifdef _WIN32
#define CONTROLLER_PLUGIN_API _declspec(dllexport)
#elif __linux__
#define CONTROLLER_PLUGIN_API()
#endif

namespace msge
{
class Core;
}



const static std::string pluginName = "DefaultPlugin";

extern "C" CONTROLLER_PLUGIN_API void getInfo(common::PluginInfo& info)
{
    info.name = pluginName;
}

extern "C" CONTROLLER_PLUGIN_API void registerPlugin(msge::plugins::PluginRegistry& registry)
{
    try
    {
        auto proto = common::GenericFactory<msge::plugin::JsonSerializer, msge::Core&>::proto();
        
        registry.registerPlugin("JsonSerializer", proto);
        LOG(INFO) << "registered plugin "
                  << "JsonSerializer";
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Error registering plugin " << std::quoted(pluginName) << ": " << e.what();
    }
}
