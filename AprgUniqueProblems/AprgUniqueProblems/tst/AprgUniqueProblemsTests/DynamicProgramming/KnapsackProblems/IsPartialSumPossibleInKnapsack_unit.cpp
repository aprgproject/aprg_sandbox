#include <AprgUniqueProblems/DynamicProgramming/KnapsackProblems/IsPartialSumPossibleInKnapsack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample1)
{
    IsPartialSumPossibleInKnapsack queryForTest(9U, {{3U, 34U, 4U, 12U, 5U, 2U}});

    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample2){
    IsPartialSumPossibleInKnapsack queryForTest(30U, {{3U, 34U, 4U, 12U, 5U, 2U}});

    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample3){
    IsPartialSumPossibleInKnapsack queryForTest(11U, {{1U, 5U, 5U, 8U}});

    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample4){
    IsPartialSumPossibleInKnapsack queryForTest(2U, {{1U, 5U, 8U}});

    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_FALSE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

TEST(IsPartialSumPossibleInKnapsackTest, GetBestProfitWorksOnExample5){
    IsPartialSumPossibleInKnapsack queryForTest(9U, {{1U, 5U, 8U}});

    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingNaiveRecursion());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingMemoizationDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDP());
    EXPECT_TRUE(queryForTest.isPartialSumPossibleUsingIterativeDPAndSpaceEfficient());
}

}