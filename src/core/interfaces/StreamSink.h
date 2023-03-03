#pragma once
#include <SerializationBuffer.h>
#include <CoreDefinitions.h>
namespace msge
{
class Core;

class StreamSink
{
public:
    StreamSink(Core& core, const StreamSinkConfig&)
        : core(core)
    {
    }

    virtual ~StreamSink()                                             = default;
    virtual void operator()(std::string_view descriptor, const msge::EntitySerializationBuffer& b) = 0;

    Core& core;
    StreamSinkConfig conf;
};


} // namespace msge