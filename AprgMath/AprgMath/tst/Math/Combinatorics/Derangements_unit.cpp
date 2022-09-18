#include <Math/Combinatorics/Derangements.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(DerangementsTest, GetNumberOfDerangementsWorks)
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

TEST(DerangementsTest, GetNumberOfDerangementsApproximationWorks)
{
    EXPECT_EQ(0U, getNumberOfDerangementsApproximation(0U));
    EXPECT_EQ(0U, getNumberOfDerangementsApproximation(1U));
    EXPECT_EQ(1U, getNumberOfDerangementsApproximation(2U));
    EXPECT_EQ(2U, getNumberOfDerangementsApproximation(3U));
    EXPECT_EQ(9U, getNumberOfDerangementsApproximation(4U));
    EXPECT_EQ(44U, getNumberOfDerangementsApproximation(5U));
    EXPECT_EQ(1334961U, getNumberOfDerangementsApproximation(10U));
    EXPECT_EQ(481066515734U, getNumberOfDerangementsApproximation(15U)); // still accurate even at 15
}

TEST(DerangementsTest, GetDerangementsProbabilityWorks)
{
    EXPECT_DOUBLE_EQ(0, getDerangementsProbability(0U));
    EXPECT_DOUBLE_EQ(0, getDerangementsProbability(1U));
    EXPECT_DOUBLE_EQ(0.5, getDerangementsProbability(2U));
    EXPECT_DOUBLE_EQ(0.33333333333333331, getDerangementsProbability(3U));
    EXPECT_DOUBLE_EQ(0.375, getDerangementsProbability(4U));
    EXPECT_DOUBLE_EQ(0.36666666666666664, getDerangementsProbability(5U));
    EXPECT_DOUBLE_EQ(0.36805555555555558, getDerangementsProbability(6U));
    EXPECT_DOUBLE_EQ(0.36785714285714288, getDerangementsProbability(7U));
    // This approaches 1/e. Please check approximation formula for more information.
}

}

}
