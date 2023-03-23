#include <AprgUniqueProblems/DynamicProgramming/Palindrome/PalindromePartitioning.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(PalindromePartitioningTest, GetMinimumNumberOfCutsWorksOnExample1)
{
    PalindromePartitioning queryForTest("ababbbabbababa");

    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfCutsUsingNaiveRecursion());
    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfCutsUsingMemoizationDP());
    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfCutsUsingIterativeDP());
    EXPECT_EQ(3U, queryForTest.getMinimumNumberOfCutsUsingIterativeDPAndTimeEfficient());
}

TEST(PalindromePartitioningTest, GetMinimumNumberOfCutsWorksOnExample2)
{
    PalindromePartitioning queryForTest("GEEKSFORGEEKS");

    EXPECT_EQ(10U, queryForTest.getMinimumNumberOfCutsUsingNaiveRecursion());    EXPECT_EQ(10U, queryForTest.getMinimumNumberOfCutsUsingMemoizationDP());
    EXPECT_EQ(10U, queryForTest.getMinimumNumberOfCutsUsingIterativeDP());
    EXPECT_EQ(10U, queryForTest.getMinimumNumberOfCutsUsingIterativeDPAndTimeEfficient());
}

TEST(PalindromePartitioningTest, GetMinimumNumberOfCutsWorksOnExample3)
{
    PalindromePartitioning queryForTest("BBABCBCAB");

    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfCutsUsingNaiveRecursion());    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfCutsUsingMemoizationDP());
    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfCutsUsingIterativeDP());
    EXPECT_EQ(4U, queryForTest.getMinimumNumberOfCutsUsingIterativeDPAndTimeEfficient());
}

}
