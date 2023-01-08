#include <SerializationBuffer.h>
#include <interfaces/StreamSink.h>
#include <iostream>

namespace msge::plugin
{
/**
 * Simple stream sink
 */

class SerializationStreamAdaptor : public StreamSink
{
public:
    using StreamSink::StreamSink;
    SerializationStreamAdaptor() = default;

    void setStream(const std::ostream& os)
    {
        stream = std::make_unique<std::ostream>(os.rdbuf());
    }

    void operator()(const EntitySerializationBuffer& b) override
    {
        *stream << b;
    }


private:
    std::unique_ptr<std::ostream> stream;
};

} // namespace msge::plugin