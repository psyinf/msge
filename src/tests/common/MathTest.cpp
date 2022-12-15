#include <gtest/gtest.h>

#include <math/DeadReckoning.h>


TEST(DeadReckoning_simple, helpers)
{
    EXPECT_DOUBLE_EQ(1.0, common::math::DeadReckoning::toSeconds(std::chrono::milliseconds(1000)));  
    EXPECT_DOUBLE_EQ(9992159.512, common::math::DeadReckoning::toSeconds(std::chrono::milliseconds(9992159512))); 
    EXPECT_DOUBLE_EQ(0.001, common::math::DeadReckoning::toSeconds(std::chrono::milliseconds(1)));
    EXPECT_DOUBLE_EQ(0.0, common::math::DeadReckoning::toSeconds(std::chrono::milliseconds(0)));
}
