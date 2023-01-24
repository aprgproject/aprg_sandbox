#include <AprgUniqueProblems/DynamicProgramming/Palindrome/PalindromePartitioning.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(PalindromePartitioningTest, GetLongestLengthWorksOnExample1)
{
    PalindromePartitioning queryForTest("ababbbabbababa");

    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfCutsUsingNaiveRecursion());
    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfCutsUsingMemoizationDP());
    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfCutsUsingTabularDP());
    EXPECT_EQ(3U, queryForTest.getLongestLengthUsingTabularDPAndTimeEfficient());
}

TEST(PalindromePartitioningTest, GetLongestLengthWorksOnExample2)
{
    PalindromePartitioning queryForTest("GEEKSFORGEEKS");

    EXPECT_EQ(10U, queryForTest.getMinimumNumberOfCutsUsingNaiveRecursion());
    EXPECT_EQ(10U, queryForTest.getMinimumNumberOfCutsUsingMemoizationDP());
    EXPECT_EQ(10U, queryForTest.getMinimumNumberOfCutsUsingTabularDP());
    EXPECT_EQ(10U, queryForTest.getLongestLengthUsingTabularDPAndTimeEfficient());
}

TEST(PalindromePartitioningTest, GetLongestLengthWorksOnExample3)
{
    PalindromePartitioning queryForTest("BBABCBCAB");

    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfCutsUsingNaiveRecursion());
    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfCutsUsingMemoizationDP());
    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfCutsUsingTabularDP());
    EXPECT_EQ(4U, queryForTest.getLongestLengthUsingTabularDPAndTimeEfficient());
}

}
