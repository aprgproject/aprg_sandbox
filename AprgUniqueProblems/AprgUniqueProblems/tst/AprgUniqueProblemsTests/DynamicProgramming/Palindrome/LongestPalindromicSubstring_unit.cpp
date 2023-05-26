#include <AprgUniqueProblems/DynamicProgramming/Palindrome/LongestPalindromicSubstring.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(LongestPalindromicSubstringTest, GetLongestLengthWorksOnExample1) {
    LongestPalindromicSubstring queryForTest("forgeeksskeegfor");

    EXPECT_EQ(10, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(10, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(10, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(10, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ("geeksskeeg", queryForTest.getLongestStringUsingIterativeDPAndSpaceEfficient());
}

TEST(LongestPalindromicSubstringTest, GetLongestLengthWorksOnExample2) {
    LongestPalindromicSubstring queryForTest("Geeks");

    EXPECT_EQ(2, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(2, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(2, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(2, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ("ee", queryForTest.getLongestStringUsingIterativeDPAndSpaceEfficient());
}
}  // namespace alba