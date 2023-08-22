#include <UniqueProblems/DynamicProgramming/Palindrome/PalindromePartitioning.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(PalindromePartitioningTest, GetMinimumNumberOfCutsWorksOnExample1) {
    PalindromePartitioning queryForTest("ababbbabbababa");

    EXPECT_EQ(3, queryForTest.getMinimumNumberOfCutsUsingNaiveRecursion());
    EXPECT_EQ(3, queryForTest.getMinimumNumberOfCutsUsingMemoizationDP());
    EXPECT_EQ(3, queryForTest.getMinimumNumberOfCutsUsingIterativeDP());
    EXPECT_EQ(3, queryForTest.getMinimumNumberOfCutsUsingIterativeDPAndTimeEfficient());
}

TEST(PalindromePartitioningTest, GetMinimumNumberOfCutsWorksOnExample2) {
    PalindromePartitioning queryForTest("GEEKSFORGEEKS");

    EXPECT_EQ(10, queryForTest.getMinimumNumberOfCutsUsingNaiveRecursion());
    EXPECT_EQ(10, queryForTest.getMinimumNumberOfCutsUsingMemoizationDP());
    EXPECT_EQ(10, queryForTest.getMinimumNumberOfCutsUsingIterativeDP());
    EXPECT_EQ(10, queryForTest.getMinimumNumberOfCutsUsingIterativeDPAndTimeEfficient());
}

TEST(PalindromePartitioningTest, GetMinimumNumberOfCutsWorksOnExample3) {
    PalindromePartitioning queryForTest("BBABCBCAB");

    EXPECT_EQ(4, queryForTest.getMinimumNumberOfCutsUsingNaiveRecursion());
    EXPECT_EQ(4, queryForTest.getMinimumNumberOfCutsUsingMemoizationDP());
    EXPECT_EQ(4, queryForTest.getMinimumNumberOfCutsUsingIterativeDP());
    EXPECT_EQ(4, queryForTest.getMinimumNumberOfCutsUsingIterativeDPAndTimeEfficient());
}

}  // namespace alba
