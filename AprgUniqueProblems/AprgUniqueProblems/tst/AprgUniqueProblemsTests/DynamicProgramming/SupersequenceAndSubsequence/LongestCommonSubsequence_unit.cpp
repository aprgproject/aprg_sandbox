#include <AprgUniqueProblems/DynamicProgramming/SupersequenceAndSubsequence/LongestCommonSubsequence.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba
{

TEST(LongestCommonSubsequenceTest, GetLongestLengthWorksOnExample1)
{
    LongestCommonSubsequence queryForTest(
    {1U, 2U, 3U, 4U, 7U, 8U},
    {1U, 5U, 4U, 6U, 8U, 18U});

    EXPECT_EQ(3U, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(3U, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(3U, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(3U, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
}

}
