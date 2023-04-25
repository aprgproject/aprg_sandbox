#include <AprgUniqueProblems/DynamicProgramming/Grid/PathSumInGridInRightOrDownWithDiagonalTraversal.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Grid = PathSumInGridInRightOrDownWithDiagonalTraversal::Grid;
using Path = PathSumInGridInRightOrDownWithDiagonalTraversal::Path;
}  // namespace

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample1) {
    Grid inputGrid(
        5U, 5U, {3U, 7U, 9U, 2U, 7U, 9U, 8U, 3U, 5U, 5U, 1U, 7U, 9U, 8U, 5U, 3U, 8U, 6U, 4U, 10U, 6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(32U, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(32U, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(32U, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample2) {
    Grid inputGrid(3U, 3U, {1U, 2U, 3U, 4U, 8U, 2U, 1U, 5U, 3U});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(8U, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(8U, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(8U, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample1) {
    Grid inputGrid(
        5U, 5U, {3U, 7U, 9U, 2U, 7U, 9U, 8U, 3U, 5U, 5U, 1U, 7U, 9U, 8U, 5U, 3U, 8U, 6U, 4U, 10U, 6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(67U, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(67U, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(67U, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample2) {
    Grid inputGrid(3U, 3U, {1U, 2U, 3U, 4U, 8U, 2U, 1U, 5U, 3U});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(21U, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(21U, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(21U, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMinimumTypeWorksOnExample1) {
    Grid inputGrid(
        5U, 5U, {3U, 7U, 9U, 2U, 7U, 9U, 8U, 3U, 5U, 5U, 1U, 7U, 9U, 8U, 5U, 3U, 8U, 6U, 4U, 10U, 6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{3U, 8U, 9U, 4U, 8U}), queryForTest.getBestPathUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMaximumTypeWorksOnExample1) {
    Grid inputGrid(
        5U, 5U, {3U, 7U, 9U, 2U, 7U, 9U, 8U, 3U, 5U, 5U, 1U, 7U, 9U, 8U, 5U, 3U, 8U, 6U, 4U, 10U, 6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{3U, 9U, 8U, 7U, 9U, 8U, 5U, 10U, 8U}), queryForTest.getBestPathUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMinimumTypeWorksOnExample2) {
    Grid inputGrid(3U, 3U, {1U, 2U, 3U, 4U, 8U, 2U, 1U, 5U, 3U});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{1U, 2U, 2U, 3U}), queryForTest.getBestPathUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMaximumTypeWorksOnExample2) {
    Grid inputGrid(3U, 3U, {1U, 2U, 3U, 4U, 8U, 2U, 1U, 5U, 3U});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{1U, 4U, 8U, 5U, 3U}), queryForTest.getBestPathUsingIterativeDP());
}

}  // namespace alba
