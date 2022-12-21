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

TEST(PathSumInGridInRightOrDownTraversalTest, GetMaxPathSumOnExample1)
{
    Grid inputGrid(5, 5,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownTraversal searchToTest(inputGrid);

    EXPECT_EQ(67U, searchToTest.getMaxPathSumUsingRecursion());
    EXPECT_EQ(67U, searchToTest.getMaxPathSumUsingTabularDP());
    EXPECT_EQ(67U, searchToTest.getMaxPathSumUsingMemoizationDP());
}

TEST(PathSumInGridInRightOrDownTraversalTest, GetMaxPathWorksOnExample1)
{
    Grid inputGrid(5, 5,
    {3U, 7U, 9U, 2U, 7U,
     9U, 8U, 3U, 5U, 5U,
     1U, 7U, 9U, 8U, 5U,
     3U, 8U, 6U, 4U, 10U,
     6U, 3U, 9U, 7U, 8U});
    PathSumInGridInRightOrDownTraversal searchToTest(inputGrid);

    EXPECT_EQ((Path{3U, 9U, 8U, 7U, 9U, 8U, 5U, 10U, 8U}), searchToTest.getMaxPathUsingTabularDP());
}

}
