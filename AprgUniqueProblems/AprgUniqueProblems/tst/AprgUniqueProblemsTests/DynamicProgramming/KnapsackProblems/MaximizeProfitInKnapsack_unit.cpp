#include <AprgUniqueProblems/DynamicProgramming/KnapsackProblems/MaximizeProfitInKnapsack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(MaximizeProfitInKnapsackTest, GetBestProfitInKnapsackWorksOnExample1)
{
    MaximizeProfitInKnapsack queryForTest(50U, {{10U, 60U}, {20U, 100U}, {30U, 120U}});

    EXPECT_EQ(220U, queryForTest.getBestProfitInKnapsackUsingNaiveRecursion());
    EXPECT_EQ(220U, queryForTest.getBestProfitInKnapsackUsingTabularDP());
    EXPECT_EQ(220U, queryForTest.getBestProfitInKnapsackUsingTabularDPAndSpaceEfficient());
    EXPECT_EQ(220U, queryForTest.getBestProfitInKnapsackUsingMemoizationDP());
}

}
