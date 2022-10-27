#include "CorePluginInterface.h"

#include <any>
#include <format>
#include <iomanip>
#include <stdexcept>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif


using namespace msge::plugin;

CorePluginInterface::CorePluginInterface(const std::string& plugin_file_path)
    : common::PluginBase(plugin_file_path)
{

    if (HINSTANCE handle = std::any_cast<HINSTANCE>(getHandle()); ::GetProcAddress(handle, "registerPlugin"))
    {
        registerPluginFn = std::bind_front(std::bit_cast<int (*)(PluginRegistry&)>(::GetProcAddress(handle, "registerPlugin")));
    }

    // If the functions aren't found, we're going to assume this is
    // a plain simple DLL and not one of our plug-ins
    if (!registerPluginFn)
    {
        throw std::invalid_argument(std::format("{} is not a valid plug-in due to missing {} function", plugin_file_path, "registerPlugin"));
    }
    // TODO: check for version incompatibilities
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
