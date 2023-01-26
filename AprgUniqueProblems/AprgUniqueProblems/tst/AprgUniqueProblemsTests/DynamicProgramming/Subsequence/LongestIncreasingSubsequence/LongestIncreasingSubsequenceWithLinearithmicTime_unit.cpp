#include <AprgUniqueProblems/DynamicProgramming/Subsequence/LongestIncreasingSubsequence/LongestIncreasingSubsequenceWithLinearithmicTime.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace
{
using Values=LongestIncreasingSubsequenceWithLinearithmicTime::Values;
}

TEST(LongestIncreasingSubsequenceWithLinearithmicTimeTest, GetLongestLengthWorksOnExample1)
{
    LongestIncreasingSubsequenceWithLinearithmicTime queryForTest({6U, 2U, 5U, 1U, 7U, 4U, 8U, 3U});

    EXPECT_EQ(4U, queryForTest.getLongestLength());
}

TEST(LongestIncreasingSubsequenceWithLinearithmicTimeTest, GetLongestSubsequenceWorksOnExample1)
{
    LongestIncreasingSubsequenceWithLinearithmicTime queryForTest({6U, 2U, 5U, 1U, 7U, 4U, 8U, 3U});

    EXPECT_EQ((Values{2U, 5U, 7U, 8U}), queryForTest.getLongestSubsequence());
}

}
