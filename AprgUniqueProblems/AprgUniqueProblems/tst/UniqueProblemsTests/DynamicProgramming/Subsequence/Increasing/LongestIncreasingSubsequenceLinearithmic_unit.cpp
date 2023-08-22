#include <UniqueProblems/DynamicProgramming/Subsequence/Increasing/LongestIncreasingSubsequenceLinearithmic.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Values = LongestIncreasingSubsequenceLinearithmic::Values;
}

TEST(LongestIncreasingSubsequenceLinearithmicTest, GetLongestLengthWorksOnExample1) {
    LongestIncreasingSubsequenceLinearithmic queryForTest({6, 2, 5, 1, 7, 4, 8, 3});

    EXPECT_EQ(4, queryForTest.getLongestLength());
}

TEST(LongestIncreasingSubsequenceLinearithmicTest, GetLongestSubsequenceWorksOnExample1) {
    LongestIncreasingSubsequenceLinearithmic queryForTest({6, 2, 5, 1, 7, 4, 8, 3});

    EXPECT_EQ((Values{2, 5, 7, 8}), queryForTest.getLongestSubsequence());
}

}  // namespace alba
