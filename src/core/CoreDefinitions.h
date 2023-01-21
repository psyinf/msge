#pragma once
#include <algorithm>
#include <array>
#include <nlohmann/json.hpp>
#include <ranges>
#include <stack>
#include <string_view>
#include <strings/FixedString.h>
#include <strings/StringTools.h>

namespace msge
{

using EntityId = FixedString<64>;
using TypeId   = FixedString<64>;

using SceneId = FixedString<256>;

using JsonType = nlohmann::json;

using StreamSinkConfig           = JsonType;
const auto EmtpyStreamSinkConfig = JsonType{"{}"_json};


inline auto splitQualifiedName(std::string_view name)
{
    auto stack = std::vector<std::string_view>();

    /**
     * split the name by the separation character and put the result on a stack for later inspection
     */
    auto view = name
              | std::views::split('.')
              | std::views::transform([](const auto& rng) {
                    auto c = rng | std::views::common;
                    return std::string_view(c.begin(), c.end());
                });
    std::ranges::for_each(view, [&](const auto& s) { stack.emplace_back(s); });
    return stack;
}
template <typename T>
auto makeQualifiedName(const T& t)
{
   return Strings::concatWithSeparator(t, ".");
}

} // namespace msge