#pragma once
#include <SerializationBuffer.h>
#include <functional>
#include <memory>
#include <visitors/BaseEntityVisitor.h>



namespace msge
{

using EntitySerializationSink = std::function<void(const msge::EntitySerializationBuffer&)>;

class Core;
/**
 * Abstract base class of BaseEntityVisitor classes that are associated with a Core instance
 */

class CoreEntityVisitor : public BaseEntityVisitor
{

public:
    
    void setSink(EntitySerializationSink&& _sink)
    {
        this->sink = std::move(_sink);
    }
    
    explicit CoreEntityVisitor(Core& core)
        : BaseEntityVisitor()
        , core(core)
    {
    }

protected:
    EntitySerializationSink& getSink() { return sink; }
    Core&                    getCore() { return core; }

private:
    EntitySerializationSink sink;
    Core&                   core;
};
} // namespace msge