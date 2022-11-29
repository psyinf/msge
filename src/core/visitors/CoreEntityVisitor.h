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
    Core& core;

    void setSink(EntitySerializationSink sink) {
        this->sink = sink;
    }

    CoreEntityVisitor(Core& core)
        : BaseEntityVisitor()
        , core(core)
    {
    }

protected:
    EntitySerializationSink sink;
};
} // namespace msge