#pragma once
#include <BaseEntityVisitor.h>
#include <FactoryRegistry.h>


namespace msge::plugins
{
using EntityVisitorCtor = common::GenericFactory<BaseEntityVisitor>::CtorFunc;

/**
 * Registry to hold constructors for class prototypes.
 * TODO: example
 * TODO: we need to change the key to reflect the fact that with the visitor pattern we need to specify the type of the visitor somehow
 */
class PluginRegistry
{
public:
    enum class PluginRole
    {
        SERIALIZER,   
    };
   
    void registerPlugin(std::string_view prototypeName, PluginRole role, EntityVisitorCtor&& constructor);
    auto getInstance(std::string_view name);

private:
    common::GenericFactory<BaseEntityVisitor> visitorFactory;
};


} // namespace msge::plugins