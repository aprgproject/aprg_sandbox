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
    PathSumInGridInRightOrDownTraversal searchToTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(49U, searchToTest.getBestPathSumUsingRecursion());
    EXPECT_EQ(49U, searchToTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(49U, searchToTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMinimumTypeWorksOnExample1)
{
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownTraversal searchToTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{3U, 9U, 1U, 3U, 6U, 3U, 9U, 7U, 8U}), searchToTest.getBestPathUsingTabularDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMinimumTypeWorksOnExample2)
{
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownTraversal searchToTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ(11U, searchToTest.getBestPathSumUsingRecursion());
    EXPECT_EQ(11U, searchToTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(11U, searchToTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMinimumTypeWorksOnExample2)
{
    Grid inputGrid(3U, 3U,
    {1U, 2U, 3U,
     4U, 8U, 2U,
     1U, 5U, 3U});
    PathSumInGridInRightOrDownTraversal searchToTest(PathSumInGridInRightOrDownTraversal::Type::MinimumSum, inputGrid);

    EXPECT_EQ((Path{1U, 2U, 3U, 2U, 3U}), searchToTest.getBestPathUsingTabularDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathSumWithMaximumTypeWorksOnExample1)
{
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownTraversal searchToTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ(67U, searchToTest.getBestPathSumUsingRecursion());
    EXPECT_EQ(67U, searchToTest.getBestPathSumUsingTabularDP());
    EXPECT_EQ(67U, searchToTest.getBestPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetBestPathWithMaximumTypeWorksOnExample1)
{
    Grid inputGrid(5U, 5U,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownTraversal searchToTest(PathSumInGridInRightOrDownTraversal::Type::MaximumSum, inputGrid);

    EXPECT_EQ((Path{3U, 9U, 8U, 7U, 9U, 8U, 5U, 10U, 8U}), searchToTest.getBestPathUsingTabularDP());
}

}
