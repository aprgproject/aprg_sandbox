#include <AprgUniqueProblems/DynamicProgramming/Subsequence/LongestCommonSubsequence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Sequence=LongestCommonSubsequence::Sequence;
}

TEST(LongestCommonSubsequenceTest, GetLongestCommonSubsequenceLengthUsingRecursionWorksOnExample1)
{
    LongestCommonSubsequence searchToTest(
    {1U, 2U, 3U, 4U, 7U, 8U},
    {1U, 5U, 4U, 6U, 8U, 18U});

    EXPECT_EQ(3U, searchToTest.getLongestCommonSubsequenceLengthUsingRecursion());
}

TEST(LongestCommonSubsequenceTest, GetLongestCommonSubsequenceLengthUsingDynamicProgrammingWorksOnExample1)
{
    LongestCommonSubsequence searchToTest(
    {1U, 2U, 3U, 4U, 7U, 8U},
    {1U, 5U, 4U, 6U, 8U, 18U});

    EXPECT_EQ(3U, searchToTest.getLongestCommonSubsequenceLengthUsingDynamicProgramming());
}

}
