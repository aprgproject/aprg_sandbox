#include <UniqueProblems/DynamicProgramming/KnapsackProblems/MaximizeProfitInZeroOneKnapsack.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(MaximizeProfitInZeroOneKnapsackTest, GetBestProfitWorksOnExample1) {
    MaximizeProfitInZeroOneKnapsack queryForTest(50, {{10, 60}, {20, 100}, {30, 120}});

    EXPECT_EQ(220, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(220, queryForTest.getBestProfitUsingMemoizationDP());
    EXPECT_EQ(220, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(220, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());
}

TEST(MaximizeProfitInZeroOneKnapsackTest, GetBestProfitWorksOnExample2) {
    MaximizeProfitInZeroOneKnapsack queryForTest(
        8, {{1, 1}, {2, 5}, {3, 8}, {4, 9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}});

    EXPECT_EQ(22, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(22, queryForTest.getBestProfitUsingMemoizationDP());
    EXPECT_EQ(22, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(22, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());
}

}  // namespace alba
