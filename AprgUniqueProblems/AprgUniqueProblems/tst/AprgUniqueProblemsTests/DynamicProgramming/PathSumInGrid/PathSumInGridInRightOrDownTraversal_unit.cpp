#include <AprgUniqueProblems/DynamicProgramming/PathSumInGrid/PathSumInGridInRightOrDownTraversal.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Grid=PathSumInGridInRightOrDownTraversal::Grid;
using Path=PathSumInGridInRightOrDownTraversal::Path;
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample1)
{
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(49U, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(49U, queryForTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(49U, queryForTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample2){
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(11U, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(11U, queryForTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(11U, queryForTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample1){
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(67U, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(67U, queryForTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(67U, queryForTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample2){
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(21U, queryForTest.getBestPathSumUsingNaiveRecursion());
    EXPECT_EQ(21U, queryForTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(21U, queryForTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMinimumTypeWorksOnExample1){
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{3U, 9U, 1U, 3U, 6U, 3U, 9U, 7U, 8U}), queryForTest.getBestPathUsingTabularDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMaximumTypeWorksOnExample1){
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{3U, 9U, 8U, 7U, 9U, 8U, 5U, 10U, 8U}), queryForTest.getBestPathUsingTabularDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMinimumTypeWorksOnExample2){
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{1U, 2U, 3U, 2U, 3U}), queryForTest.getBestPathUsingTabularDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMaximumTypeWorksOnExample2){
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownTraversal queryForTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{1U, 4U, 8U, 5U, 3U}), queryForTest.getBestPathUsingTabularDP());
}

}