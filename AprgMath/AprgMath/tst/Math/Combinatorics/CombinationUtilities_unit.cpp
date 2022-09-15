#include <Math/Combinatorics/CombinationUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(CombinationUtilitiesTest, IsNumberOfCombinationsEqualToItsCounterpartWorks)
{
    EXPECT_FALSE(isNumberOfCombinationsEqualToItsCounterpart(2U, 4U)); // Wrong input so its false, it should be n>k
    EXPECT_TRUE(isNumberOfCombinationsEqualToItsCounterpart(4U, 2U));    EXPECT_TRUE(isNumberOfCombinationsEqualToItsCounterpart(10U, 5U));
}

TEST(CombinationUtilitiesTest, IsTheSumOfAllNumberOfCombinationsEqualTo2ToTheNWorks)
{
    EXPECT_TRUE(isTheSumOfAllNumberOfCombinationsEqualTo2ToTheN(4U));
    EXPECT_TRUE(isTheSumOfAllNumberOfCombinationsEqualTo2ToTheN(10U));
}

TEST(CombinationUtilitiesTest, GetNumberOfDerangementsWorks)
{
    EXPECT_EQ(0U, getNumberOfDerangements(0U));
    EXPECT_EQ(0U, getNumberOfDerangements(1U));
    EXPECT_EQ(1U, getNumberOfDerangements(2U));
    EXPECT_EQ(2U, getNumberOfDerangements(3U));
    EXPECT_EQ(9U, getNumberOfDerangements(4U));
    EXPECT_EQ(44U, getNumberOfDerangements(5U));
    EXPECT_EQ(1334961U, getNumberOfDerangements(10U));
    EXPECT_EQ(481066515734U, getNumberOfDerangements(15U));
}

}

}