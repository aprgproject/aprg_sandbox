#include <AprgUniqueProblems/DynamicProgramming/Subsequence/LongestIncreasingSubsequence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Sequence=LongestIncreasingSubsequence::Sequence;
}

TEST(LongestIncreasingSubsequenceTest, GetLongestIncreasingSubsequenceLengthWorksOnExample1)
{
    LongestIncreasingSubsequence queryForTest({6U, 2U, 5U, 1U, 7U, 4U, 8U, 3U});

    EXPECT_EQ(4U, queryForTest.getLongestIncreasingSubsequenceLength());
}

TEST(LongestIncreasingSubsequenceTest, GetLongestIncreasingSubsequenceWorksOnExample1)
{
    LongestIncreasingSubsequence queryForTest({6U, 2U, 5U, 1U, 7U, 4U, 8U, 3U});

    EXPECT_EQ((Sequence{2U, 5U, 7U, 8U}), queryForTest.getLongestIncreasingSubsequence());
}

}