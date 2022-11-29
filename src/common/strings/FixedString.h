#pragma once

#include <array>
#include <cstring>
#include <fmt/core.h>
#include <ranges>
#include <stdexcept>
#include <string>
/**
 * String-like interface to an fixed length identifier. The \0 character is not included if the input is either only the \0 character or uses up the capacity
 * TODO: interop between different sizes.
 */
template <size_t LENGTH>
class FixedString
{
    static_assert(LENGTH > 0, "Must use a non-zero value for length");

public:
    FixedString()
    {
        content[0] = '\0';
    }
    
    FixedString(const FixedString& rhs) {
        std::ranges::copy(rhs.content, content.begin());
        content_view = normalize( std::string_view(content));

    }
    
       explicit(false) FixedString(std::string_view s)
    {
        if (s.length() > LENGTH)
        {
            throw std::out_of_range(fmt::format("{} too long for FixedString<{}>", s, LENGTH));
        }
        auto length_to_consider = std::min(s.find_first_of('\0'), s.length());

        content[std::min(content.size() - 1, s.length())] = '\0';
        std::ranges::copy_n(s.begin(), length_to_consider, content.begin());

       
        content_view = std::string_view(content.data(), length_to_consider);
    }

    explicit(false) FixedString(const std::string& s)
        : FixedString(std::string_view(s)){};

    explicit(false) FixedString(const char* const s)
        : FixedString(std::string_view(s)){};

    explicit(false) operator std::string() const { return std::string(content_view); }

    explicit(false) operator const char*() const { return content_view.data(); }

    explicit(true) operator std::string_view() const
    {
        return content_view;
    }

    bool operator==(std::string_view rhs) const
    {
        return normalize(rhs) == content_view;
    }

    auto operator<=>(const std::string_view& rhs) const
    {
        return content_view <=> normalize(rhs);
    }

    size_t size() const { return content_view.size(); }

    const auto data() const
    {
        return content.data();
    };

private:
    static std::string_view normalize(std::string_view rhs)
    {
        auto length_to_consider = std::min(rhs.find_first_of('\0'), rhs.length());
        auto rhs_norm           = std::string_view(rhs.data(), length_to_consider);
        return rhs_norm;
    }

    
private:
    std::array<char, LENGTH> content;
    std::string_view         content_view;
};

/*
 * We need to specialize this to avoid char* comparison to be induced
*/
template <size_t L>
bool operator==(const FixedString<L>& lhs, const FixedString<L>& rhs)
{
    return std::string_view(lhs) == std::string_view(rhs);
}

template <size_t L>
auto operator<=>(const FixedString<L>& lhs, const FixedString<L>& rhs) 
{
    return lhs <=> std::string_view(rhs);
}