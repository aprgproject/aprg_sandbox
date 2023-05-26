#include <AprgUniqueProblems/DynamicProgramming/SupersequenceAndSubsequence/IncreasingSubsequence/LongestIncreasingSubsequenceWithLinearithmicTime.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Values = LongestIncreasingSubsequenceWithLinearithmicTime::Values;
}

TEST(LongestIncreasingSubsequenceWithLinearithmicTimeTest, GetLongestLengthWorksOnExample1) {
    LongestIncreasingSubsequenceWithLinearithmicTime queryForTest({6, 2, 5, 1, 7, 4, 8, 3});

    EXPECT_EQ(4, queryForTest.getLongestLength());
}

TEST(LongestIncreasingSubsequenceWithLinearithmicTimeTest, GetLongestSubsequenceWorksOnExample1) {
    LongestIncreasingSubsequenceWithLinearithmicTime queryForTest({6, 2, 5, 1, 7, 4, 8, 3});

    EXPECT_EQ((Values{2, 5, 7, 8}), queryForTest.getLongestSubsequence());
}

}  // namespace alba