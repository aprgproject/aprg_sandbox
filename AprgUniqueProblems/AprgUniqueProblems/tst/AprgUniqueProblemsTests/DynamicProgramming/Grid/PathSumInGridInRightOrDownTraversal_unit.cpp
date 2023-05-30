#include <AprgUniqueProblems/DynamicProgramming/Grid/PathSumInGridInRightOrDownTraversal.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using Grid = PathSumInGridInRightOrDownTraversal::Grid;
using Path = PathSumInGridInRightOrDownTraversal::Path;
}  // namespace

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample1) {
    Grid inputGrid(
        5, 5, {3, 7, 9, 2, 7, 9, 8, 3, 5, 5, 1, 7, 9, 8, 5, 3, 8, 6, 4, 10, 6, 3, 9, 7, 8});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(49, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(49, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(49, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample2) {
    Grid inputGrid(3, 3, {1, 2, 3, 4, 8, 2, 1, 5, 3});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(11, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(11, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(11, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample1) {
    Grid inputGrid(
        5, 5, {3, 7, 9, 2, 7, 9, 8, 3, 5, 5, 1, 7, 9, 8, 5, 3, 8, 6, 4, 10, 6, 3, 9, 7, 8});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(67, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(67, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(67, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample2) {
    Grid inputGrid(3, 3, {1, 2, 3, 4, 8, 2, 1, 5, 3});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(21, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(21, queryForTest.getBestPathSumUsingMemoizationDP());
    EXPECT_EQ(21, queryForTest.getBestPathSumUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMinimumTypeWorksOnExample1) {
    Grid inputGrid(
        5, 5, {3, 7, 9, 2, 7, 9, 8, 3, 5, 5, 1, 7, 9, 8, 5, 3, 8, 6, 4, 10, 6, 3, 9, 7, 8});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{3, 9, 1, 3, 6, 3, 9, 7, 8}), queryForTest.getBestPathUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMaximumTypeWorksOnExample1) {
    Grid inputGrid(
        5, 5, {3, 7, 9, 2, 7, 9, 8, 3, 5, 5, 1, 7, 9, 8, 5, 3, 8, 6, 4, 10, 6, 3, 9, 7, 8});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{3, 9, 8, 7, 9, 8, 5, 10, 8}), queryForTest.getBestPathUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMinimumTypeWorksOnExample2) {
    Grid inputGrid(3, 3, {1, 2, 3, 4, 8, 2, 1, 5, 3});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{1, 2, 3, 2, 3}), queryForTest.getBestPathUsingIterativeDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMaximumTypeWorksOnExample2) {
    Grid inputGrid(3, 3, {1, 2, 3, 4, 8, 2, 1, 5, 3});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{1, 4, 8, 5, 3}), queryForTest.getBestPathUsingIterativeDP());
}

}  // namespace alba
