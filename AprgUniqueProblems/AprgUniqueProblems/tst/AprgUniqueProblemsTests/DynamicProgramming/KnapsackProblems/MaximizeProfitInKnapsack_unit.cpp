#include <AprgUniqueProblems/DynamicProgramming/KnapsackProblems/MaximizeProfitInKnapsack.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MaximizeProfitInKnapsackTest, GetBestProfitWorksOnExample1) {
    MaximizeProfitInKnapsack queryForTest(50, {{10, 60}, {20, 100}, {30, 120}});

    EXPECT_EQ(220, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(220, queryForTest.getBestProfitUsingMemoizationDP());
    EXPECT_EQ(220, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(220, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());
}

TEST(MaximizeProfitInKnapsackTest, GetBestProfitWorksOnExample2) {
    MaximizeProfitInKnapsack queryForTest(
        8, {{1, 1}, {2, 5}, {3, 8}, {4, 9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}});

    EXPECT_EQ(22, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(22, queryForTest.getBestProfitUsingMemoizationDP());
    EXPECT_EQ(22, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(22, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba