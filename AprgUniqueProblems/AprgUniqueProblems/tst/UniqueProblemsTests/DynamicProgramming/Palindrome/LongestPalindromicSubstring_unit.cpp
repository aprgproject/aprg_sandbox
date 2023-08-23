#include <UniqueProblems/DynamicProgramming/Palindrome/LongestPalindromicSubstring.hpp>

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

TEST(LongestPalindromicSubstringTest, GetLongestLengthWorksOnExample3) {
    LongestPalindromicSubstring queryForTest("eeeeee");

    EXPECT_EQ(6, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(6, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(6, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(6, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ("eeeeee", queryForTest.getLongestStringUsingIterativeDPAndSpaceEfficient());
}

TEST(LongestPalindromicSubstringTest, GetLongestLengthWorksOnExample4) {
    LongestPalindromicSubstring queryForTest("bananas");

    EXPECT_EQ(5, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(5, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(5, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(5, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ("anana", queryForTest.getLongestStringUsingIterativeDPAndSpaceEfficient());
}

TEST(LongestPalindromicSubstringTest, GetLongestLengthWorksOnExample5) {
    LongestPalindromicSubstring queryForTest("abbcccbbbcaaccbababcbcabca");

    // EXPECT_EQ(7, queryForTest.getLongestLengthUsingNaiveRecursion());
    // EXPECT_EQ(7, queryForTest.getLongestLengthUsingMemoizationDP());
    // EXPECT_EQ(7, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(7, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ("bbcccbb", queryForTest.getLongestStringUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba
