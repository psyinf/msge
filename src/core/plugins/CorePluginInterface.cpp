#include "CorePluginInterface.h"

#include <any>
#include <iomanip>
#include <stdexcept>

#include <fmt/core.h>



using namespace msge::plugins;

CorePluginInterface::CorePluginInterface(const std::string& plugin_file_path)
    : common::PluginBase(plugin_file_path)
{
    registerPluginFn = bindFunction<void, PluginRegistry&>(getHandle(), "registerPlugin");
}


bool CorePluginInterface::registerPlugin(PluginRegistry& pluginRegistry) const
{
    if (registerPluginFn)
    {
        registerPluginFn(pluginRegistry);
        return true;
    }
    return false;
}
