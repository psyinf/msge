#pragma once
#include <SerializationBuffer.h>
#include <functional>
#include <memory>
#include <visitors/BaseEntityVisitor.h>


namespace msge
{

using EntitySerializationSink = std::function<void(msge::EntitySerializationBuffer&&)>;

class Core;
/**
 * Abstract base class of BaseEntityVisitor classes that are associated with a Core instance
 */

class CoreEntityVisitor : public BaseEntityVisitor
{

public:
    void setSink(const EntitySerializationSink& _sink)
    {
        this->sink = _sink;
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