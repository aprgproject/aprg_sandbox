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
    EXPECT_EQ(10U, queryForTest.getLongestLengthUsingTabularDP());
    EXPECT_EQ(10U, queryForTest.getLongestLengthUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ("geeksskeeg", queryForTest.getLongestStringUsingTabularDPAndSpaceEfficient());
}

TEST(LongestPalindromicSubstringTest, GetLongestLengthWorksOnExample2)
{
    LongestPalindromicSubstring queryForTest("Geeks");

    EXPECT_EQ(2U, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(2U, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(2U, queryForTest.getLongestLengthUsingTabularDP());
    EXPECT_EQ(2U, queryForTest.getLongestLengthUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ("ee", queryForTest.getLongestStringUsingTabularDPAndSpaceEfficient());
}

}
