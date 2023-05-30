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
        5, 5, {3, 7, 9, 2, 7, 9, 8, 3, 5, 5, 1, 7, 9, 8, 5, 3, 8, 6, 4, 10, 6, 3, 9, 7, 8});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(32, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(32, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(32, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample2) {
    Grid inputGrid(3, 3, {1, 2, 3, 4, 8, 2, 1, 5, 3});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(8, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(8, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(8, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample1) {
    Grid inputGrid(
        5, 5, {3, 7, 9, 2, 7, 9, 8, 3, 5, 5, 1, 7, 9, 8, 5, 3, 8, 6, 4, 10, 6, 3, 9, 7, 8});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(67, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(67, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(67, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample2) {
    Grid inputGrid(3, 3, {1, 2, 3, 4, 8, 2, 1, 5, 3});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(21, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(21, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(21, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMinimumTypeWorksOnExample1) {
    Grid inputGrid(
        5, 5, {3, 7, 9, 2, 7, 9, 8, 3, 5, 5, 1, 7, 9, 8, 5, 3, 8, 6, 4, 10, 6, 3, 9, 7, 8});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{3, 8, 9, 4, 8}), queryForTest.getBestPathUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMaximumTypeWorksOnExample1) {
    Grid inputGrid(
        5, 5, {3, 7, 9, 2, 7, 9, 8, 3, 5, 5, 1, 7, 9, 8, 5, 3, 8, 6, 4, 10, 6, 3, 9, 7, 8});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{3, 9, 8, 7, 9, 8, 5, 10, 8}), queryForTest.getBestPathUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMinimumTypeWorksOnExample2) {
    Grid inputGrid(3, 3, {1, 2, 3, 4, 8, 2, 1, 5, 3});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{1, 2, 2, 3}), queryForTest.getBestPathUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMaximumTypeWorksOnExample2) {
    Grid inputGrid(3, 3, {1, 2, 3, 4, 8, 2, 1, 5, 3});
    PathSumInGridInRightOrDownWithDiagonalTraversal queryForTest(
        PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{1, 4, 8, 5, 3}), queryForTest.getBestPathUsingIterativeDP());
}

}  // namespace alba
