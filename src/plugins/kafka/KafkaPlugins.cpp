#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#undef WIN32_LEAN_AND_MEAN
#endif
#include <glog/logging.h>
#include <Core.h>
#include <KafkaStreamAdapter.h>
#include <plugins/PluginBase.h>
#include <plugins/PluginRegistry.h>

#ifdef _WIN32
#define DEFAULT_PLUGIN_API _declspec(dllexport)
#elif __linux__
#define DEFAULT_PLUGIN_API
#endif

namespace msge
{
class Core;
}

auto registerPlugins(msge::Core& core)
{
    std::vector<std::string> names;
    auto&                    registry = core.getPluginRegistry();
    try
    {
        auto [name, proto] = std::make_pair("KafkaStream", common::GenericFactory<msge::KafkaStreamAdaptor, msge::Core&, const msge::StreamSinkConfig&>::proto());
        registry.registerPlugin(name, proto);
        names.emplace_back(name);
    }
    catch (const std::runtime_error& e)
    {
        LOG(ERROR) << "Error registering prototype: " << e.what();
    }
    return names;
}

const static std::string pluginName = "KafkaPlugin";

extern "C" DEFAULT_PLUGIN_API void getInfo(common::PluginInfo& info)
{
    info.name = pluginName;
}

extern "C" DEFAULT_PLUGIN_API void registerPlugin(msge::Core& core)
{
    auto registered_plugins = registerPlugins(core);
    LOG(INFO) << fmt::format("Registered interfaces(s): [ {} ]\n ", fmt::join(registered_plugins, " | "));
    
}
