#include "CorePluginInterface.h"

#include <any>
#include <iomanip>
#include <stdexcept>

#include <fmt/core.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif


using namespace msge::plugins;

CorePluginInterface::CorePluginInterface(const std::string& plugin_file_path)
    : common::PluginBase(plugin_file_path)
{
    registerPluginFn = bindFunction<void, PluginRegistry&>(getHandle(), "registerPlugin");
}


bool CorePluginInterface::registerPlugin(PluginRegistry& pluginRegistry)
{
    if (registerPluginFn)
    {
        registerPluginFn(pluginRegistry);
        return true;
    }
    return false;
}
