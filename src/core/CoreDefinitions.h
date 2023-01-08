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

using StreamSinkConfig = nlohmann::json;
const auto EmtpyStreamSinkConfig = nlohmann::json{"{}"_json};
} // namespace msge