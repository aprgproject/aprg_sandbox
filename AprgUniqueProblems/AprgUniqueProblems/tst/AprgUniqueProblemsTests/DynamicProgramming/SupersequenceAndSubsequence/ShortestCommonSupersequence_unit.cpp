#include <AprgUniqueProblems/DynamicProgramming/SupersequenceAndSubsequence/ShortestCommonSupersequence.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

TEST(ShortestCommonSupersequenceTest, GetLongestLengthWorksOnExample1)
{
    ShortestCommonSupersequence queryForTest(
    {7U, 5U, 5U, 11U},
    {5U, 11U, 5U});

    EXPECT_EQ(5U, queryForTest.getShortestLengthUsingNaiveRecursion());
    EXPECT_EQ(5U, queryForTest.getShortestLengthUsingMemoizationDP());
    EXPECT_EQ(5U, queryForTest.getShortestLengthUsingIterativeDP());
    EXPECT_EQ(5U, queryForTest.getShortestLengthUsingIterativeDPAndSpaceEfficient());
}

TEST(ShortestCommonSupersequenceTest, GetLongestLengthWorksOnExample2)
{
    ShortestCommonSupersequence queryForTest(
    {1U, 7U, 7U, 20U, 1U, 2U},
    {7U, 24U, 20U, 24U, 1U, 25U, 2U});

    EXPECT_EQ(9U, queryForTest.getShortestLengthUsingNaiveRecursion());
    EXPECT_EQ(9U, queryForTest.getShortestLengthUsingMemoizationDP());
    EXPECT_EQ(9U, queryForTest.getShortestLengthUsingIterativeDP());
    EXPECT_EQ(9U, queryForTest.getShortestLengthUsingIterativeDPAndSpaceEfficient());
}

}
