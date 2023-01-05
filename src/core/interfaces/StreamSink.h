#pragma once
#include <SerializationBuffer.h>

namespace msge
{
class Core;

class StreamSink
{
public:
    StreamSink(Core& core)
        : core(core)
    {
    }

    virtual ~StreamSink()                                             = default;
    virtual void operator()(const msge::EntitySerializationBuffer& b) = 0;

    Core& core;
};


} // namespace msge