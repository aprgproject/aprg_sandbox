#include <AprgUniqueProblems/DynamicProgramming/Other/MaximizeProfitInCuttingARod.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

TEST(MaximizeProfitInCuttingARodTest, GetBestProfitWorksOnExample1) {
    MaximizeProfitInCuttingARod queryForTest(
        8, {{1, 1}, {2, 5}, {3, 8}, {4, 9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}});

    EXPECT_EQ(22, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(22, queryForTest.getBestProfitUsingMemoizationDP());
    /*EXPECT_EQ(22, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(22, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());*/
}

TEST(MaximizeProfitInCuttingARodTest, GetBestProfitWorksOnExample2) {
    MaximizeProfitInCuttingARod queryForTest(
        8, {{1, 3}, {2, 5}, {3, 8}, {4, 9}, {5, 10}, {6, 17}, {7, 17}, {8, 20}});

    EXPECT_EQ(24, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(24, queryForTest.getBestProfitUsingMemoizationDP());
    /*EXPECT_EQ(24, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(24, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());*/
}

}  // namespace alba