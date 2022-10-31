#include <plugins/PluginBase.h>
#include <plugins/PluginRegistry.h>

#include <serializer/StreamSerializer.h>

#include <glog/logging.h>

#include <string>


#define CONTROLLER_PLUGIN_API _declspec(dllexport)
const static std::string pluginName = "DefaultPIDController";

extern "C" CONTROLLER_PLUGIN_API void getInfo(common::PluginInfo& info)
{
    info.name = pluginName;
}

extern "C" CONTROLLER_PLUGIN_API void registerPlugin(msge::plugins::PluginRegistry& registry)
{
    try
    {
        auto proto = common::GenericFactory<msge::plugin::StreamSerializer>::proto();
        registry.registerPlugin("plaintext", msge::plugins::PluginRegistry::PluginRole::SERIALIZER, proto);
    }
    catch (const std::exception& e)
    {
        LOG(ERROR) << "Error registering plugin " << pluginName << ": " << e.what();
    }
}
