#include <AprgUniqueProblems/DynamicProgramming/Other/CountNumberOfWaysToReachAGivenScoreInAGame.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(CountNumberOfWaysToReachAGivenScoreInAGameTest, GetMinimumCostWorksWithZero)
{
    CountNumberOfWaysToReachAGivenScoreInAGame queryForTest(0);

    // 1 because of nullsets
    EXPECT_EQ(1U, queryForTest.getMinimumCostUsingIterativeDP());
    EXPECT_EQ(1U, queryForTest.getMinimumCostUsingCoinProblemSolutions());
}

TEST(CountNumberOfWaysToReachAGivenScoreInAGameTest, GetMinimumCostWorksWithOne)
{
    CountNumberOfWaysToReachAGivenScoreInAGame queryForTest(1);

    EXPECT_EQ(0U, queryForTest.getMinimumCostUsingIterativeDP());
    EXPECT_EQ(0U, queryForTest.getMinimumCostUsingCoinProblemSolutions());
}

TEST(CountNumberOfWaysToReachAGivenScoreInAGameTest, GetMinimumCostWorksOnExample1)
{
    CountNumberOfWaysToReachAGivenScoreInAGame queryForTest(13);

    EXPECT_EQ(2U, queryForTest.getMinimumCostUsingIterativeDP());
    EXPECT_EQ(2U, queryForTest.getMinimumCostUsingCoinProblemSolutions());
}

TEST(CountNumberOfWaysToReachAGivenScoreInAGameTest, GetMinimumCostWorksOnExample2)
{
    CountNumberOfWaysToReachAGivenScoreInAGame queryForTest(20);

    EXPECT_EQ(4U, queryForTest.getMinimumCostUsingIterativeDP());
    EXPECT_EQ(4U, queryForTest.getMinimumCostUsingCoinProblemSolutions());
}

}
