#pragma once
#include "strings/FixedString.h"

#include <array>
#include <cstddef>
#include <vector>
namespace msge
{
/**
 * Class template for a buffer element that holds a serialized state
 */
template <typename Key, typename Buffer>
class SerializationBuffer
{
public:
    Key key;
    Buffer buffer;

    friend std::ostream& operator<<(std::ostream& out, const SerializationBuffer& c)
    {
        
        //TODO: out << c.buffer;
        return out;
    }
};



//TODO: use a fixed/limited size string representation
using EntityPath   = std::string;

using EntityBuffer = std::vector<std::uint8_t>;
using EntitySerializationBuffer = SerializationBuffer<EntityPath, EntityBuffer>;
}