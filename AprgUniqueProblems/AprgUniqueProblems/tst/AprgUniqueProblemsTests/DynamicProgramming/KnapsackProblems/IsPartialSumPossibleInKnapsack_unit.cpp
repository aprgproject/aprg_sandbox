#include <AprgUniqueProblems/DynamicProgramming/KnapsackProblems/IsPartialSumPossibleInKnapsack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample1) {
    IsPartialSumPossibleInKnapsack queryForTest(9, {{3, 34, 4, 12, 5, 2}});

    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample2) {
    IsPartialSumPossibleInKnapsack queryForTest(30, {{3, 34, 4, 12, 5, 2}});

    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample3) {
    IsPartialSumPossibleInKnapsack queryForTest(11, {{1, 5, 5, 8}});

    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample4) {
    IsPartialSumPossibleInKnapsack queryForTest(2, {{1, 5, 8}});

    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample5) {
    IsPartialSumPossibleInKnapsack queryForTest(9, {{1, 5, 8}});

    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba
