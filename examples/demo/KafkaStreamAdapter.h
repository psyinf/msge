

#include <SerializationBuffer.h>
#include <kafka/KafkaProducer.h>


using namespace kafka;
using namespace kafka::clients;
using namespace kafka::clients::producer;

const Properties props({
    {"bootstrap.servers", {"127.0.0.1:9092"}},
    {"enable.idempotence", {"true"}},
});
const auto       topic = "test";
class KafkaStreamAdaptor
{
public:
    KafkaStreamAdaptor() = default;

    bool debug = false;
    bool async = true;

    void operator()(const msge::EntitySerializationBuffer& b)
    {
        auto record = ProducerRecord(topic,
                                     Key(b.key.data(), b.key.size()),
                                     Value(b.buffer.data(), b.buffer.size()));

        if (async)
        {
            // Send the message.
            try
            {
                producer.send(
                    record,
                    // The delivery report handler
                    [this](const RecordMetadata& metadata, const Error& error) {
                        if (!error && debug)
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
                const RecordMetadata metadata = producer.syncSend(record);
                if (debug)
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
        KafkaProducer producer = KafkaProducer{props};
    };