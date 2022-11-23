#pragma once

#include <array>
#include <cstring>
#include <fmt/core.h>
#include <stdexcept>
#include <string>
/**
 * String-like interface to an fixed length identifier
 */
template <size_t LENGTH>
class FixedString
{
public:
    explicit(false) FixedString(std::string_view s)
    {
        if (s.length() > LENGTH)
        {
            throw std::invalid_argument(fmt::format("{} too long for FixedString<{}>", s, LENGTH));
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
        //#FIXME: we need to stop comparing if \0 is encountered
        return std::ranges::equal(string.data, data );
    }
    auto operator<=>(const FixedString<LENGTH>& string) const
    {
        // #FIXME: we need to stop comparing if \0 is encountered
        return string.data <=> data;
    }
    std::array<char, LENGTH> data;
};