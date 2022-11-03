#pragma once
#include <BaseEntityVisitor.h>
#include <CoreEntityVisitor.h>
#include <FactoryRegistry.h>


namespace msge::plugins
{
using BaseVisitorFactory = common::GenericFactory<BaseEntityVisitor>;
using CoreVisitorFactory = common::GenericFactory<CoreEntityVisitor, msge::Core&>;

/**
 * Registry to hold constructors for class prototypes.
 */
class PluginRegistry
{
public:
    /**
     * Generic visitor
     */
    void registerPlugin(std::string_view prototypeName, BaseVisitorFactory::CtorFunc&& constructor);
    /**
     * Visitors associated with the core reference
     */
    void registerPlugin(std::string_view prototypeName, CoreVisitorFactory::CtorFunc&& constructor);

    auto getInstancePrototype(std::string_view name);

private:
    BaseVisitorFactory visitorFactory;
    CoreVisitorFactory coreVisitorFactory;
};


} // namespace msge::plugins