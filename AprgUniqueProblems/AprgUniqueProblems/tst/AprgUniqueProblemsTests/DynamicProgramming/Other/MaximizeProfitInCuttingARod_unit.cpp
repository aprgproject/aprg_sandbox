#include <AprgUniqueProblems/DynamicProgramming/Other/MaximizeProfitInCuttingARod.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(MaximizeProfitInCuttingARodTest, GetBestProfitWorksOnExample1)
{
    MaximizeProfitInCuttingARod queryForTest(8U,
    {{1U, 1U}, {2U, 5U}, {3U, 8U}, {4U, 9U}, {5U, 10U}, {6U, 17U}, {7U, 17U}, {8U, 20U}});

    EXPECT_EQ(22U, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(22U, queryForTest.getBestProfitUsingMemoizationDP());
    /*EXPECT_EQ(22U, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(22U, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());*/
}

TEST(MaximizeProfitInCuttingARodTest, GetBestProfitWorksOnExample2){
    MaximizeProfitInCuttingARod queryForTest(8U,
    {{1U, 3U}, {2U, 5U}, {3U, 8U}, {4U, 9U}, {5U, 10U}, {6U, 17U}, {7U, 17U}, {8U, 20U}});

    EXPECT_EQ(24U, queryForTest.getBestProfitUsingNaiveRecursion());
    EXPECT_EQ(24U, queryForTest.getBestProfitUsingMemoizationDP());
    /*EXPECT_EQ(24U, queryForTest.getBestProfitUsingIterativeDP());
    EXPECT_EQ(24U, queryForTest.getBestProfitUsingIterativeDPAndSpaceEfficient());*/
}

}