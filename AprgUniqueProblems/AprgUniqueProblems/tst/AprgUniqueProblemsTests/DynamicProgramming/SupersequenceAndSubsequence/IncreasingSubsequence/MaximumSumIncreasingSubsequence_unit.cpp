#include <AprgUniqueProblems/DynamicProgramming/SupersequenceAndSubsequence/IncreasingSubsequence/MaximumSumIncreasingSubsequence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Values = MaximumSumIncreasingSubsequence::Values;
}

TEST(MaximumSumIncreasingSubsequenceTest, GetLongestLengthWorksOnExample1) {
    MaximumSumIncreasingSubsequence queryForTest({1U, 101U, 2U, 3U, 100U, 4U, 5U});

    EXPECT_EQ(106U, queryForTest.getMaximumSum());
}

TEST(MaximumSumIncreasingSubsequenceTest, GetSubsequenceWithMaximumSumWorksOnExample1) {
    MaximumSumIncreasingSubsequence queryForTest({1U, 101U, 2U, 3U, 100U, 4U, 5U});

    EXPECT_EQ((Values{1U, 2U, 3U, 100U}), queryForTest.getSubsequenceWithMaximumSum());
}

}  // namespace alba
