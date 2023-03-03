#include <gtest/gtest.h>

#include <strings/FixedLengthString.h>
TEST(FixedLengthString_construction, all)
{
    EXPECT_THROW(common::FixedLengthString<8>("abcdefgh1"), std::out_of_range);
    EXPECT_NO_THROW({ 
    
        auto x = common::FixedLengthString<1>(); 
        EXPECT_EQ(x.size(), 0);
        x = common::FixedLengthString<1>("\0");
        EXPECT_EQ(x.size(), 0);
        
     
        });
    common::FixedLengthString<1> fs;
    auto sv = std::string_view(fs);
   //TODO: test trailing \0 behavior;
}
TEST(FixedLengthString_operators, equalsFixed)
{
    EXPECT_TRUE(common::FixedLengthString<8>("123") == common::FixedLengthString<8>("123"));
    EXPECT_TRUE(std::string_view(common::FixedLengthString<8>("123")) == std::string_view(common::FixedLengthString<8>("123")));
}

TEST(FixedLengthString_operators, equals) 
{
    // size used exactly
    EXPECT_EQ(common::FixedLengthString<8>("abcd1234"), std::string("abcd1234"));
    EXPECT_EQ(std::string("abcd1234"), common::FixedLengthString<8>("abcd1234"));

    // not all capacity used up
    EXPECT_EQ(common::FixedLengthString<8>("abcd123"), std::string("abcd123"));
    EXPECT_EQ(std::string("abcd123"), common::FixedLengthString<8>("abcd123"));

    // equality comparison stops after \0
    EXPECT_EQ(common::FixedLengthString<8>("a1b2"), std::string("a1b2\0\'2'ab", 8));
    EXPECT_EQ(std::string("a1b2\0\'2'ab", 8), common::FixedLengthString<8>("a1b2"));

}
TEST(FixedLengthString_operators, nequals)
{
    EXPECT_NE(common::FixedLengthString<8>("abcd1234"), std::string("abcd1231"));
    EXPECT_NE(std::string("abcd1231"), common::FixedLengthString<8>("abcd1234"));

    EXPECT_NE(common::FixedLengthString<8>("abcd1234"), std::string("abcd1231abcded"));

    // equality comparison stops after \0
    EXPECT_NE(common::FixedLengthString<8>("a1b2"), std::string("a1b2v\02a", 8));
}

TEST(FixedLengthString_operators, spaceship)
{
    EXPECT_TRUE(std::string_view("abc") > std::string_view("abb"));
    
    EXPECT_TRUE(common::FixedLengthString<3>("abc") > common::FixedLengthString<3>("abb"));
    //TODO: no interop between different sizes yet
    //EXPECT_TRUE(FixedLengthString<4>("abc") > FixedLengthString<3>("abb"));
   
    EXPECT_TRUE(common::FixedLengthString<3>("abb") < common::FixedLengthString<3>("abc"));
    //EXPECT_TRUE(FixedLengthString<4>("abb") < FixedLengthString<3>("abc"));
}

//TODO: assigment, conversion operators