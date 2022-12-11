#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <strings/StringTools.h>


TEST(StringTools_matches, MatchIdentity)
{
    EXPECT_TRUE(Strings::matches("abcd1234", "abcd1234"));
    
}

TEST(StringTools_matches, SimpleExpression)
{
    EXPECT_TRUE(Strings::matches("Simple testString", "String(.*)"));
    EXPECT_TRUE(Strings::matches("Simple testString", "Simple(.*)"));
    EXPECT_TRUE(Strings::matches("Simple testString", "(.*)String"));

    EXPECT_FALSE(Strings::matches("Simple testString", "(.*)string"));
}

TEST(StringTools_matchWildcard, matchStar)
{
    EXPECT_TRUE(Strings::matchesWildCard("SomeString.x", "*.x"));
    EXPECT_TRUE(Strings::matchesWildCard("*..Flat", "*"));
    EXPECT_TRUE(Strings::matchesWildCard("abcSOMEdefSOMEghi", "abc*def*gh*"));
    EXPECT_FALSE(Strings::matchesWildCard("abcSOMEdefSOMEghi", "abc*def*ghj*"));
    EXPECT_FALSE(Strings::matchesWildCard("*..Flat", "*.y"));
}

TEST(StringTools_matchWildcard, matchQuestionMark)
{
    EXPECT_TRUE(Strings::matchesWildCard("SomeString.x", "Some?tring.x"));
    EXPECT_TRUE(Strings::matchesWildCard("SomeString.xyz", "?ome?tring.???"));
}


TEST(StringTools, wildCardToRegex)
{
    EXPECT_EQ(Strings::wildcardToRegex("abc*.*"), "abc.*\\..*");
    EXPECT_EQ(Strings::wildcardToRegex("*.x"), ".*\\.x");
}

TEST(StringTools_tokenize, tokenize)
{
    EXPECT_THAT(Strings::tokenize("a.b.c.d.e", "."), ::testing::ElementsAreArray<std::string_view>({"a", "b", "c", "d", "e"}));
    EXPECT_THAT(Strings::tokenize("a.b.c.d.e", ""), ::testing::ElementsAreArray<std::string_view>({"a.b.c.d.e"}));
    EXPECT_THAT(Strings::tokenize("a.b.c.d.e", "x"), ::testing::ElementsAreArray<std::string_view>({"a.b.c.d.e"}));
    EXPECT_THAT(Strings::tokenize("", "x"), ::testing::ElementsAreArray<std::string_view>({}));
    EXPECT_THAT(Strings::tokenize("axcvd", "cv"), ::testing::ElementsAreArray<std::string_view>({"ax", "d"}));
}
