

#include <kafka/KafkaProducer.h>
#include <SerializationBuffer.h>


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
    

    void operator()(const msge::EntitySerializationBuffer& b)
    {
        auto record = ProducerRecord(topic,
                                     Key(b.key.data(), b.key.size()),
                                     Value(b.buffer.data(), b.buffer.size()));

        // Send the message.
        try
        {
            const RecordMetadata metadata = producer.syncSend(record);
            std::cout << "% Message delivered: " << metadata.toString() << std::endl;
        }
        catch (const KafkaException& e)
        {
            std::cerr << "% Message delivery failed: " << e.error().message() << std::endl;
        }

    }


private:
    KafkaProducer producer = KafkaProducer{props};
};