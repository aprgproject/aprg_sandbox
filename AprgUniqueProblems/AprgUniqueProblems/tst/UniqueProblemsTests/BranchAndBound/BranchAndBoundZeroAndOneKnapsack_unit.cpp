#include <UniqueProblems/BranchAndBound/BranchAndBoundZeroAndOneKnapsack.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(BranchAndBoundZeroAndOneKnapsackTest, GetBestProfitWorksOnExample1) {
    BranchAndBoundZeroAndOneKnapsack queryForTest;

    EXPECT_EQ(220, queryForTest.getBestProfit(50, {{10, 60}, {20, 100}, {30, 120}}));
}

TEST(BranchAndBoundZeroAndOneKnapsackTest, GetBestProfitWorksOnExample2) {
    BranchAndBoundZeroAndOneKnapsack queryForTest;

    EXPECT_EQ(18, queryForTest.getBestProfit(8, {{1, 1}, {2, 5}, {3, 8}, {4, 9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}}));
}

}  // namespace alba
