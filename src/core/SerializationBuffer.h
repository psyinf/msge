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
};




using EntityKey   = FixedString < 64>;
using EntityBuffer = std::vector<std::uint8_t>;
using EntitySerializationBuffer = SerializationBuffer<EntityKey, EntityBuffer>;
}