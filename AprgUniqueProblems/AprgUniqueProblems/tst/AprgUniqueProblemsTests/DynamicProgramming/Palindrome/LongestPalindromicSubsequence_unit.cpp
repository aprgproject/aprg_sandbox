#include <AprgUniqueProblems/DynamicProgramming/Palindrome/LongestPalindromicSubsequence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(LongestPalindromicSubsequenceTest, GetLongestLengthWorksOnExample1) {
    LongestPalindromicSubsequence queryForTest("GEEKSFORGEEKS");

    EXPECT_EQ(5, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(5, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(5, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(5, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
}

TEST(LongestPalindromicSubsequenceTest, GetLongestLengthWorksOnExample2) {
    LongestPalindromicSubsequence queryForTest("BBABCBCAB");

    EXPECT_EQ(7, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(7, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(7, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(7, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba