#include <AprgUniqueProblems/DynamicProgramming/SupersequenceAndSubsequence/IncreasingSubsequence/LongestIncreasingSubsequence.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace
{
using Values=LongestIncreasingSubsequence::Values;
}

TEST(LongestIncreasingSubsequenceTest, GetLongestLengthWorksOnExample1)
{
    LongestIncreasingSubsequence queryForTest({6U, 2U, 5U, 1U, 7U, 4U, 8U, 3U});

    EXPECT_EQ(4U, queryForTest.getLongestLength());
}

TEST(LongestIncreasingSubsequenceTest, GetLongestSubsequenceWorksOnExample1)
{
    LongestIncreasingSubsequence queryForTest({6U, 2U, 5U, 1U, 7U, 4U, 8U, 3U});

    EXPECT_EQ((Values{2U, 5U, 7U, 8U}), queryForTest.getLongestSubsequence());
}

}
