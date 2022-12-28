#include "CorePluginInterface.h"

#include <any>
#include <iomanip>
#include <stdexcept>

#include <fmt/core.h>



using namespace msge::plugins;

CorePluginInterface::CorePluginInterface(const std::string& plugin_file_path)
    : common::PluginBase(plugin_file_path)
{
    registerPluginFn = bindFunction<void, Core&>(getHandle(), "registerPlugin");
}


bool CorePluginInterface::registerPlugin(Core& core) const
{
    if (registerPluginFn)
    {
        registerPluginFn(core);
        return true;
    }
    return false;
}
