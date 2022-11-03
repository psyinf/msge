#include <glog/logging.h>
#include <plugins/PluginBase.h>
#include <plugins/PluginRegistry.h>
#include <serializer/JsonSerializer.h>
#include <string>


namespace msge
{
class Core;
}


#define CONTROLLER_PLUGIN_API _declspec(dllexport)
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
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Error registering plugin " << std::quoted(pluginName) << ": " << e.what();
    }
}
