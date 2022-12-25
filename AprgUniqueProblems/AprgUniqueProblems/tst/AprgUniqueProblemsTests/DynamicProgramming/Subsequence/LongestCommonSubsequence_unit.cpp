#include <AprgUniqueProblems/DynamicProgramming/Subsequence/LongestCommonSubsequence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Sequence=LongestCommonSubsequence::Sequence;
}

TEST(LongestCommonSubsequenceTest, GetLongestCommonSubsequenceLengthUsingNaiveRecursionWorksOnExample1)
{
    LongestCommonSubsequence queryForTest(
    {1U, 2U, 3U, 4U, 7U, 8U},
    {1U, 5U, 4U, 6U, 8U, 18U});

    EXPECT_EQ(3U, queryForTest.getLongestCommonSubsequenceLengthUsingNaiveRecursion());
}

TEST(LongestCommonSubsequenceTest, GetLongestCommonSubsequenceLengthUsingDynamicProgrammingWorksOnExample1)
{
    LongestCommonSubsequence queryForTest(
    {1U, 2U, 3U, 4U, 7U, 8U},
    {1U, 5U, 4U, 6U, 8U, 18U});

    EXPECT_EQ(3U, queryForTest.getLongestCommonSubsequenceLengthUsingDynamicProgramming());
}

}
