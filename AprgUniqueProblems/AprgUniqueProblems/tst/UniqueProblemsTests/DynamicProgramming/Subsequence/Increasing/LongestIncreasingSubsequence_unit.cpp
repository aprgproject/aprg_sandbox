#include <UniqueProblems/DynamicProgramming/Subsequence/Increasing/LongestIncreasingSubsequence.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
namespace {
using Values = LongestIncreasingSubsequence::Values;
}

TEST(LongestIncreasingSubsequenceTest, GetLongestLengthWorksOnExample1) {
    LongestIncreasingSubsequence queryForTest({6, 2, 5, 1, 7, 4, 8, 3});

    EXPECT_EQ(4, queryForTest.getLongestLength());
}

TEST(LongestIncreasingSubsequenceTest, GetLongestSubsequenceWorksOnExample1) {
    LongestIncreasingSubsequence queryForTest({6, 2, 5, 1, 7, 4, 8, 3});

    EXPECT_EQ((Values{2, 5, 7, 8}), queryForTest.getLongestSubsequence());
}

}  // namespace alba
