#include <AprgUniqueProblems/DynamicProgramming/Grid/CollectMaximumPointsInAGridUsingTwoTraversals.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Grid = CollectMaximumPointsInAGridUsingTwoTraversals::ValueGrid;
}

TEST(CollectMaximumPointsInAGridUsingTwoTraversalsTest, GetMaximumPointsWorksOnEmptyInput) {
    Grid inputGrid;
    CollectMaximumPointsInAGridUsingTwoTraversals queryForTest(inputGrid);

    EXPECT_EQ(0U, queryForTest.getMaximumPointsUsingNaiveRecursion());
    EXPECT_EQ(0U, queryForTest.getMaximumPointsUsingMemoizationDP());
    EXPECT_EQ(0U, queryForTest.getMaximumPointsUsingIterativeDP());
}

TEST(CollectMaximumPointsInAGridUsingTwoTraversalsTest, GetMaximumPointsWorksOnOneElement) {
    Grid inputGrid(1U, 1U, {100});
    CollectMaximumPointsInAGridUsingTwoTraversals queryForTest(inputGrid);

    EXPECT_EQ(100U, queryForTest.getMaximumPointsUsingNaiveRecursion());
    EXPECT_EQ(100U, queryForTest.getMaximumPointsUsingMemoizationDP());
    EXPECT_EQ(100U, queryForTest.getMaximumPointsUsingIterativeDP());
}

TEST(CollectMaximumPointsInAGridUsingTwoTraversalsTest, GetMaximumPointsWorksOnExample1) {
    Grid inputGrid(4U, 5U, {3, 6, 8, 2, 5, 2, 4, 3, 1, 1, 20, 10, 1, 1, 20, 10, 1, 1, 20, 10});
    CollectMaximumPointsInAGridUsingTwoTraversals queryForTest(inputGrid);

    // EXPECT_EQ(73U, queryForTest.getMaximumPointsUsingNaiveRecursion());
    EXPECT_EQ(73U, queryForTest.getMaximumPointsUsingMemoizationDP());
    EXPECT_EQ(73U, queryForTest.getMaximumPointsUsingIterativeDP());
}

}  // namespace alba
