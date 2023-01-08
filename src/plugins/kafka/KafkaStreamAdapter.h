#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#undef WIN32_LEAN_AND_MEAN
#endif
#include <SerializationBuffer.h>
#include <interfaces/StreamSink.h>
#include <kafka/KafkaProducer.h>

namespace msge
{

using namespace kafka;
using namespace kafka::clients;
using namespace kafka::clients::producer;

const Properties props({
    {"bootstrap.servers", {"127.0.0.1:9092"}},
    {"enable.idempotence", {"true"}},
});

struct AdapterClientProperties
{
    std::string server = {"127.0.0.1:9092"};
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(AdapterClientProperties, server)
    Properties makeProperties() const
    {
        return Properties({{"bootstrap.servers", server},
                           {"enable.idempotence",
                            {"true"}}});
    }
};


struct StreamAdapterProperties
{
    AdapterClientProperties adapter = {};
    bool                    debug = false;
    bool                    async = true;
    NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(StreamAdapterProperties, adapter, debug, async)
};

class KafkaStreamAdaptor : public StreamSink
{
public:
    KafkaStreamAdaptor(Core& core, const StreamSinkConfig& cfg)
        : StreamSink(core, cfg)
        , properties(cfg.get<StreamAdapterProperties>())
        , producer(std::make_unique<KafkaProducer>( properties.adapter.makeProperties()))
    {}


    void operator()(std::string_view descriptor, const msge::EntitySerializationBuffer& b) override
    {
        auto record = ProducerRecord(Topic(descriptor),
                                     Key(b.key.data(), b.key.size()),
                                     Value(b.buffer.data(), b.buffer.size()));

        if (properties.async)
        {
            // Send the message.
            try
            {
                producer->send(
                    record,
                    // The delivery report handler
                    [this](const RecordMetadata& metadata, const Error& error) {
                        if (!error && properties.debug)
                        {
                            std::cout << "% Message delivered: " << metadata.toString() << std::endl;
                        }
                        else if (error)
                        {
                            std::cerr << "% Message delivery failed: " << error.message() << std::endl;
                        }
                    },
                    // The memory block given by record.value() would be copied
                    KafkaProducer::SendOption::ToCopyRecordValue);
            }
            catch (const KafkaException& e)
            {
                std::cerr << "% Message delivery failed: " << e.error().message() << std::endl;
            }
        }
        else
        {
            // Send the message.
            try
            {
                const RecordMetadata metadata = producer->syncSend(record);
                if (properties.debug)
                {
                    std::cout << "% Message delivered: " << metadata.toString() << std::endl;
                }
            }
            catch (const KafkaException& e)
            {
                std::cerr << "% Message delivery failed: " << e.error().message() << std::endl;
            }
        }
    }

private:
    StreamAdapterProperties        properties;
    std::unique_ptr<KafkaProducer>           producer;
   
};

} // namespace msge