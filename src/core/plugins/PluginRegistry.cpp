#include "PluginRegistry.h"


auto msge::plugins::PluginRegistry::getInstancePrototype(std::string_view name) const
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

std::unique_ptr<msge::CoreEntityVisitor> msge::plugins::PluginRegistry::getCoreVisitorPrototype(const std::string_view name, msge::Core& core) const
{
    return coreVisitorFactory.make(name, core);
}
