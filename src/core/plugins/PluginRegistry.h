#pragma once
#include <BaseEntityVisitor.h>
#include <FactoryRegistry.h>

namespace msge::plugins
{
using EntityVisitorCtor = common::GenericFactory<BaseEntityVisitor>::CtorFunc;

class PluginRegistry
{
public:
    void registerPlugin(std::string_view prototypeName, EntityVisitorCtor&& constructor) {
        visitorFactory.registerPrototype(prototypeName, std::move(constructor));
    }
    auto getInstance(std::string_view name) {
        return visitorFactory.make(name);
    }

private:
    common::GenericFactory<BaseEntityVisitor> visitorFactory;
};


} // namespace msge::plugins