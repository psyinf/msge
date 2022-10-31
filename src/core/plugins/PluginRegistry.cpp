#include "PluginRegistry.h"
#include <magic_enum.hpp>


auto msge::plugins::PluginRegistry::getInstance(std::string_view name)
{
    return visitorFactory.make(name);
}

void msge::plugins::PluginRegistry::registerPlugin(std::string_view prototypeName, PluginRole role, EntityVisitorCtor&& constructor)
{
    auto name = std::string(prototypeName) + std::string(magic_enum::enum_name(role));
    visitorFactory.registerPrototype(name , std::move(constructor));
}
