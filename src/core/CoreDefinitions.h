#pragma once
#include <algorithm>
#include <array>
#include <strings/FixedString.h>
#include <nlohmann/json.hpp>
namespace msge
{

using EntityId = FixedString<64>;
using TypeId = FixedString<64>;

using SceneId = FixedString<256>;

using JsonType = nlohmann::json;

using StreamSinkConfig = JsonType;
const auto EmtpyStreamSinkConfig = JsonType{"{}"_json};


} // namespace msge