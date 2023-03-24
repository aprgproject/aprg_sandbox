#include <AprgUniqueProblems/DynamicProgramming/Palindrome/LongestPalindromicSubstring.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(LongestPalindromicSubstringTest, GetLongestLengthWorksOnExample1)
{
    LongestPalindromicSubstring queryForTest("forgeeksskeegfor");

    EXPECT_EQ(10U, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(10U, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(10U, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(10U, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ("geeksskeeg", queryForTest.getLongestStringUsingIterativeDPAndSpaceEfficient());
}

TEST(LongestPalindromicSubstringTest, GetLongestLengthWorksOnExample2)
{
    LongestPalindromicSubstring queryForTest("Geeks");

    EXPECT_EQ(2U, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(2U, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(2U, queryForTest.getLongestLengthUsingIterativeDP());
    EXPECT_EQ(2U, queryForTest.getLongestLengthUsingIterativeDPAndSpaceEfficient());
    EXPECT_EQ("ee", queryForTest.getLongestStringUsingIterativeDPAndSpaceEfficient());
}

}
