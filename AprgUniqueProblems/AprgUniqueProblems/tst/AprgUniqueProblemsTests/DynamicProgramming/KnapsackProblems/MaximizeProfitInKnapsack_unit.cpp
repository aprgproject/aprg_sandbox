#include <AprgUniqueProblems/DynamicProgramming/KnapsackProblems/MaximizeProfitInKnapsack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(MaximizeProfitInKnapsackTest, GetBestProfitWorksOnExample1)
{
    MaximizeProfitInKnapsack queryForTest(50U, {{10U, 60U}, {20U, 100U}, {30U, 120U}});

    EXPECT_EQ(220U, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(220U, queryForTest.getBestProfitUsingMemoizationDP());
    EXPECT_EQ(220U, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(220U, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());
}

TEST(MaximizeProfitInKnapsackTest, GetBestProfitWorksOnExample2){
    MaximizeProfitInKnapsack queryForTest(8U,
    {{1U, 1U}, {2U, 5U}, {3U, 8U}, {4U, 9U}, {5U, 10U}, {6U, 17U}, {7U, 17U}, {8U, 20U}});

    EXPECT_EQ(22U, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(22U, queryForTest.getBestProfitUsingMemoizationDP());
    EXPECT_EQ(22U, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(22U, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());
}

}