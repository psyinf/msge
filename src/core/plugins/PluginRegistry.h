#pragma once
#include <visitors/BaseEntityVisitor.h>
#include <visitors/CoreEntityVisitor.h>
#include <interfaces/StreamSink.h>
#include <CoreDefinitions.h>
#include <FactoryRegistry.h>



namespace msge::plugins
{
using BaseVisitorFactory = common::GenericFactory<BaseEntityVisitor>;
using CoreVisitorFactory = common::GenericFactory<CoreEntityVisitor, msge::Core&>;
using StreamSinkFactory = common::GenericFactory<StreamSink, msge::Core&, const StreamSinkConfig&>;

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
    /**
     * Stream sinks
     */
    void registerPlugin(std::string_view prototypeName, StreamSinkFactory::CtorFunc&& constructor);
    

    auto getInstancePrototype(std::string_view name) const;

    std::unique_ptr<msge::CoreEntityVisitor> getCoreVisitorPrototype(const std::string_view name, msge::Core&) const;

    std::unique_ptr<msge::StreamSink> getStreamSinkPrototype(const std::string_view name, msge::Core&, const StreamSinkConfig& cfg) const;

private:
    BaseVisitorFactory visitorFactory;
    CoreVisitorFactory coreVisitorFactory;
    StreamSinkFactory  streamSinkFactory;

};


} // namespace msge::plugins