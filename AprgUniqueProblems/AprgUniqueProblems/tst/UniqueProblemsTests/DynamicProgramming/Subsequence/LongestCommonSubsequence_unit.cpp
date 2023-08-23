#include <UniqueProblems/DynamicProgramming/Subsequence/LongestCommonSubsequence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(LongestCommonSubsequenceTest, GetLongestLengthWorksOnExample1) {
    LongestCommonSubsequence queryForTest({1, 2, 3, 4, 7, 8}, {1, 5, 4, 6, 8, 18});

    EXPECT_EQ(3, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(3, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(3, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(3, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba
