#include <glog/logging.h>
#include <serializer/register.h>
#include <taskengine/register.h>
#include <streamsink/register.h>

//TODO move to a macro
#ifdef _WIN32
#define DEFAULT_PLUGIN_API _declspec(dllexport)
#elif __linux__
#define DEFAULT_PLUGIN_API
#endif

namespace msge
{
class Core;
}



const static std::string pluginName = "DefaultPlugin";

extern "C" DEFAULT_PLUGIN_API void getInfo(common::PluginInfo& info)
{
    info.name = pluginName;
}

extern "C" DEFAULT_PLUGIN_API void registerPlugin(msge::Core& core)
{
    auto registered_plugins = registerPlugins(core);
    LOG(INFO) << fmt::format("Registered serializers(s): [ {} ]\n ", fmt::join(registered_plugins, " | "));
    auto registered_schedulers = registerSchedulers(core);
    LOG(INFO) << fmt::format("Registered schedulers(s): [ {} ]\n ", fmt::join(registered_schedulers, " | "));
    auto registered_streamsinks = registerStreamSinks(core);
    LOG(INFO) << fmt::format("Registered stream sink(s): [ {} ]\n ", fmt::join(registered_streamsinks, " | "));
}
