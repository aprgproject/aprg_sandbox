#include <UniqueProblems/DynamicProgramming/KnapsackProblems/IsPartialSumPossibleInZeroOneKnapsack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(IsPartialSumPossibleInZeroOneKnapsackTest, GetBestProfitWorksOnExample1) {
    IsPartialSumPossibleInZeroOneKnapsack queryForTest(9, {{3, 34, 4, 12, 5, 2}});

    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInZeroOneKnapsackTest, GetBestProfitWorksOnExample2) {
    IsPartialSumPossibleInZeroOneKnapsack queryForTest(30, {{3, 34, 4, 12, 5, 2}});

    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInZeroOneKnapsackTest, GetBestProfitWorksOnExample3) {
    IsPartialSumPossibleInZeroOneKnapsack queryForTest(11, {{1, 5, 5, 8}});

    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInZeroOneKnapsackTest, GetBestProfitWorksOnExample4) {
    IsPartialSumPossibleInZeroOneKnapsack queryForTest(2, {{1, 5, 8}});

    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInZeroOneKnapsackTest, GetBestProfitWorksOnExample5) {
    IsPartialSumPossibleInZeroOneKnapsack queryForTest(9, {{1, 5, 8}});

    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba
