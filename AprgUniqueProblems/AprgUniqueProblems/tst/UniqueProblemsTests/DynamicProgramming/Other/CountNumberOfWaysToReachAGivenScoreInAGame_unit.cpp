#include <UniqueProblems/DynamicProgramming/Other/CountNumberOfWaysToReachAGivenScoreInAGame.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba {
TEST(CountNumberOfWaysToReachAGivenScoreInAGameTest, GetMinimumCostWorksWithZero) {
    CountNumberOfWaysToReachAGivenScoreInAGame queryForTest(0);

    // 1 because of nullsets
    EXPECT_EQ(1, queryForTest.getMinimumCostUsingIterativeDP());
    EXPECT_EQ(1, queryForTest.getMinimumCostUsingCoinProblemSolutions());
}

TEST(CountNumberOfWaysToReachAGivenScoreInAGameTest, GetMinimumCostWorksWithOne) {
    CountNumberOfWaysToReachAGivenScoreInAGame queryForTest(1);

    EXPECT_EQ(0, queryForTest.getMinimumCostUsingIterativeDP());
    EXPECT_EQ(0, queryForTest.getMinimumCostUsingCoinProblemSolutions());
}

TEST(CountNumberOfWaysToReachAGivenScoreInAGameTest, GetMinimumCostWorksOnExample1) {
    CountNumberOfWaysToReachAGivenScoreInAGame queryForTest(13);

    EXPECT_EQ(2, queryForTest.getMinimumCostUsingIterativeDP());
    EXPECT_EQ(2, queryForTest.getMinimumCostUsingCoinProblemSolutions());
}

TEST(CountNumberOfWaysToReachAGivenScoreInAGameTest, GetMinimumCostWorksOnExample2) {
    CountNumberOfWaysToReachAGivenScoreInAGame queryForTest(20);

    EXPECT_EQ(4, queryForTest.getMinimumCostUsingIterativeDP());
    EXPECT_EQ(4, queryForTest.getMinimumCostUsingCoinProblemSolutions());
}

}  // namespace alba
