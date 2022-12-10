#include <gtest/gtest.h>

#include <strings/FixedString.h>
TEST(FixedString_construction, all)
{
    EXPECT_THROW(FixedString<8>("abcdefgh1"), std::out_of_range);
    EXPECT_NO_THROW({ 
    
        auto x = FixedString<1>(); 
        EXPECT_EQ(x.size(), 0);
        x = FixedString<1>("\0");
        EXPECT_EQ(x.size(), 0);
        
     
        });
    FixedString<1> fs;
    auto sv = std::string_view(fs);
   //TODO: test trailing \0 behavior;
}
TEST(FixedString_operators, equalsFixed)
{
    EXPECT_TRUE(FixedString<8>("123") == FixedString<8>("123"));
    EXPECT_TRUE(std::string_view(FixedString<8>("123")) == std::string_view(FixedString<8>("123")));
}

TEST(FixedString_operators, equals) 
{
    // size used exactly
    EXPECT_EQ(FixedString<8>("abcd1234"), std::string("abcd1234"));
    EXPECT_EQ(std::string("abcd1234"), FixedString<8>("abcd1234"));

    // not all capacity used up
    EXPECT_EQ(FixedString<8>("abcd123"), std::string("abcd123"));
    EXPECT_EQ(std::string("abcd123"), FixedString<8>("abcd123"));

    // equality comparison stops after \0
    EXPECT_EQ(FixedString<8>("a1b2"), std::string("a1b2\0\'2'ab", 8));
    EXPECT_EQ(std::string("a1b2\0\'2'ab", 8), FixedString<8>("a1b2"));

}
TEST(FixedString_operators, nequals)
{
    EXPECT_NE(FixedString<8>("abcd1234"), std::string("abcd1231"));
    EXPECT_NE(std::string("abcd1231"), FixedString<8>("abcd1234"));

    EXPECT_NE(FixedString<8>("abcd1234"), std::string("abcd1231abcded"));

    // equality comparison stops after \0
    EXPECT_NE(FixedString<8>("a1b2"), std::string("a1b2v\02a", 8));
}

TEST(FixedString_operators, spaceship)
{
    EXPECT_TRUE(std::string_view("abc") > std::string_view("abb"));
    
    EXPECT_TRUE(FixedString<3>("abc") > FixedString<3>("abb"));
    //TODO: no interop between different sizes yet
    //EXPECT_TRUE(FixedString<4>("abc") > FixedString<3>("abb"));
   
    EXPECT_TRUE(FixedString<3>("abb") < FixedString<3>("abc"));
    //EXPECT_TRUE(FixedString<4>("abb") < FixedString<3>("abc"));
}

//TODO: assigment, conversion operators