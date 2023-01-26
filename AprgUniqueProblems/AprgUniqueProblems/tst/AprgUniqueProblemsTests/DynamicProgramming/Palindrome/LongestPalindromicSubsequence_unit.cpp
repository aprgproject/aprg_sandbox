#include <AprgUniqueProblems/DynamicProgramming/Palindrome/LongestPalindromicSubsequence.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(LongestPalindromicSubsequenceTest, GetLongestLengthWorksOnExample1)
{
    LongestPalindromicSubsequence queryForTest("GEEKSFORGEEKS");

    EXPECT_EQ(5U, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(5U, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(5U, queryForTest.getLongestLengthUsingTabularDP());
    EXPECT_EQ(5U, queryForTest.getLongestLengthUsingTabularDPAndSpaceEfficient());
}

TEST(LongestPalindromicSubsequenceTest, GetLongestLengthWorksOnExample2)
{
    LongestPalindromicSubsequence queryForTest("BBABCBCAB");

    EXPECT_EQ(7U, queryForTest.getLongestLengthUsingNaiveRecursion());
    EXPECT_EQ(7U, queryForTest.getLongestLengthUsingMemoizationDP());
    EXPECT_EQ(7U, queryForTest.getLongestLengthUsingTabularDP());
    EXPECT_EQ(7U, queryForTest.getLongestLengthUsingTabularDPAndSpaceEfficient());
}

}
