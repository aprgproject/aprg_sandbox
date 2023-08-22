#include <UniqueProblems/GreedyAlgorithm/FractionalKnapsack.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(FractionalKnapsackTest, GetBestProfitWorksOnExample1) {
    FractionalKnapsack queryForTest;

    EXPECT_EQ(280, queryForTest.getBestProfit(50, {{10, 60}, {20, 100}, {30, 120}}));
}

TEST(FractionalKnapsackTest, GetBestProfitWorksOnExample2) {
    FractionalKnapsack queryForTest;

    EXPECT_EQ(87, queryForTest.getBestProfit(8, {{1, 1}, {2, 5}, {3, 8}, {4, 9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}}));
}

}  // namespace alba
