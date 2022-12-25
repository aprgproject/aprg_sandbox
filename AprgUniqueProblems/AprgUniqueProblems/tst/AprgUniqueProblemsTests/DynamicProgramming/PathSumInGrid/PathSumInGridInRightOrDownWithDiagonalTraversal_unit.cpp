#include <AprgUniqueProblems/DynamicProgramming/PathSumInGrid/PathSumInGridInRightOrDownWithDiagonalTraversal.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using Grid=PathSumInGridInRightOrDownWithDiagonalTraversal::Grid;
using Path=PathSumInGridInRightOrDownWithDiagonalTraversal::Path;
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample1)
{
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownWithDiagonalTraversal searchToTest(PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(32U, searchToTest.getBestPathSumUsingRecursion());
    EXPECT_EQ(32U, searchToTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(32U, searchToTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample2)
{
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownWithDiagonalTraversal searchToTest(PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(8U, searchToTest.getBestPathSumUsingRecursion());
    EXPECT_EQ(8U, searchToTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(8U, searchToTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample1)
{
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownWithDiagonalTraversal searchToTest(PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(67U, searchToTest.getBestPathSumUsingRecursion());
    EXPECT_EQ(67U, searchToTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(67U, searchToTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample2)
{
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownWithDiagonalTraversal searchToTest(PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(21U, searchToTest.getBestPathSumUsingRecursion());
    EXPECT_EQ(21U, searchToTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(21U, searchToTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMinimumTypeWorksOnExample1)
{
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownWithDiagonalTraversal searchToTest(PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{3U, 8U, 9U, 4U, 8U}), searchToTest.getBestPathUsingTabularDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMaximumTypeWorksOnExample1)
{
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownWithDiagonalTraversal searchToTest(PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{3U, 9U, 8U, 7U, 9U, 8U, 5U, 10U, 8U}), searchToTest.getBestPathUsingTabularDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMinimumTypeWorksOnExample2)
{
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownWithDiagonalTraversal searchToTest(PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{1U, 2U, 2U, 3U}), searchToTest.getBestPathUsingTabularDP());
}

TEST(PathSumInGridInRightOrDownWithDiagonalTraversalTest, GetBestPathWithMaximumTypeWorksOnExample2)
{
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownWithDiagonalTraversal searchToTest(PathSumInGridInRightOrDownWithDiagonalTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{1U, 4U, 8U, 5U, 3U}), searchToTest.getBestPathUsingTabularDP());
}

}
