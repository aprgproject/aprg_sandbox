#include <UniqueProblems/DynamicProgramming/Supersequence/ShortestCommonSupersequence.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(ShortestCommonSupersequenceTest, GetLongestLengthWorksOnExample1) {
    ShortestCommonSupersequence queryForTest({7, 5, 5, 11}, {5, 11, 5});

    EXPECT_EQ(5, queryForTest.getShortestLengthUsingNaiveRecursion());
    EXPECT_EQ(5, queryForTest.getShortestLengthUsingMemoizationDP());
    EXPECT_EQ(5, queryForTest.getShortestLengthUsingIterativeDP());
    EXPECT_EQ(5, queryForTest.getShortestLengthUsingIterativeDPAndSpaceEfficient());
}

TEST(ShortestCommonSupersequenceTest, GetLongestLengthWorksOnExample2) {
    ShortestCommonSupersequence queryForTest({1, 7, 7, 20, 1, 2}, {7, 24, 20, 24, 1, 25, 2});

    EXPECT_EQ(9, queryForTest.getShortestLengthUsingNaiveRecursion());
    EXPECT_EQ(9, queryForTest.getShortestLengthUsingMemoizationDP());
    EXPECT_EQ(9, queryForTest.getShortestLengthUsingIterativeDP());
    EXPECT_EQ(9, queryForTest.getShortestLengthUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba
