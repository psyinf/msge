#pragma once
#include <algorithm>
#include <array>
#include <format>
#include <stdexcept>
#include <string>
#include <cstring>

namespace msge
{
/**
 * String-like fixed length
 * TODO: unit tests
 */
template <size_t LENGTH>
class FixedString
{
public:
    explicit(false) FixedString(std::string_view s)
    {
        if (s.length() > LENGTH)
        {
            throw std::invalid_argument(std::format("{} too long for FixedString<{}>", s, LENGTH));
        }
        data[std::min(data.size() - 1, s.length())] = '\0';
        std::ranges::copy(s, data.begin());
        
    }

    explicit(false) FixedString(const std::string& s)
        : FixedString(std::string_view(s)){};
   
    explicit(false) FixedString(const char* const s)
        : FixedString(std::string_view(s)){};
    
    explicit(false) operator std::string() const { return std::string(data.begin(), data.end()); }

    explicit(false) operator const char*() const { return data.data(); }

    bool operator==(const FixedString<LENGTH>& string) const  {
        return std::ranges::equal(string.data, data);
    }

    std::array<char, LENGTH> data;
};

using EntityId = FixedString<64>;

using SceneId = FixedString<256>;
} // namespace msge