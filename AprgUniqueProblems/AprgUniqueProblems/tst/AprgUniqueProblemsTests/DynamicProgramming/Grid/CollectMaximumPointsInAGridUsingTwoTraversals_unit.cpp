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

    EXPECT_EQ(0, queryForTest.getMaximumPointsUsingNaiveRecursion());
    EXPECT_EQ(0, queryForTest.getMaximumPointsUsingMemoizationDP());
    EXPECT_EQ(0, queryForTest.getMaximumPointsUsingIterativeDP());
}

TEST(CollectMaximumPointsInAGridUsingTwoTraversalsTest, GetMaximumPointsWorksOnOneElement) {
    Grid inputGrid(1, 1, {100});
    CollectMaximumPointsInAGridUsingTwoTraversals queryForTest(inputGrid);

    EXPECT_EQ(100, queryForTest.getMaximumPointsUsingNaiveRecursion());
    EXPECT_EQ(100, queryForTest.getMaximumPointsUsingMemoizationDP());
    EXPECT_EQ(100, queryForTest.getMaximumPointsUsingIterativeDP());
}

TEST(CollectMaximumPointsInAGridUsingTwoTraversalsTest, GetMaximumPointsWorksOnExample1) {
    Grid inputGrid(4, 5, {3, 6, 8, 2, 5, 2, 4, 3, 1, 1, 20, 10, 1, 1, 20, 10, 1, 1, 20, 10});
    CollectMaximumPointsInAGridUsingTwoTraversals queryForTest(inputGrid);

    // EXPECT_EQ(73, queryForTest.getMaximumPointsUsingNaiveRecursion());
    EXPECT_EQ(73, queryForTest.getMaximumPointsUsingMemoizationDP());
    EXPECT_EQ(73, queryForTest.getMaximumPointsUsingIterativeDP());
}

}  // namespace alba
