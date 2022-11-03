#include "PluginRegistry.h"


auto msge::plugins::PluginRegistry::getInstancePrototype(std::string_view name)
{
    return visitorFactory.make(name);
}

void msge::plugins::PluginRegistry::registerPlugin(std::string_view prototypeName, BaseVisitorFactory::CtorFunc&& constructor)
{
    visitorFactory.registerPrototype(prototypeName, std::move(constructor));
}

void msge::plugins::PluginRegistry::registerPlugin(std::string_view prototypeName, CoreVisitorFactory::CtorFunc&& constructor)
{
    coreVisitorFactory.registerPrototype(prototypeName, std::move(constructor));
}