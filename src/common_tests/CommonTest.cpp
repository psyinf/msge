#include <gtest/gtest.h>

#include <strings/FixedString.h>


TEST(FixedString_operators, equals)
{
    //size used exactly
    EXPECT_EQ(FixedString<8>("abcd1234"), std::string("abcd1234"));
    EXPECT_EQ(std::string("abcd1234"), FixedString<8>("abcd1234"));

   
    EXPECT_EQ(FixedString<8>("abcd123"), std::string("abcd123"));
    EXPECT_EQ(std::string("abcd123"), FixedString<8>("abcd123"));
}
TEST(FixedString_operators, nequals)
{
    EXPECT_NE(FixedString<8>("abcd1234"), std::string("abcd1231"));
    EXPECT_NE(std::string("abcd1231"), FixedString<8>("abcd1234"));
}