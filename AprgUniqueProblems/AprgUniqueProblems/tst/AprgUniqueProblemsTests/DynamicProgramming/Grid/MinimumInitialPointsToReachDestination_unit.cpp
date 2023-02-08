#include <AprgUniqueProblems/DynamicProgramming/Grid/MinimumInitialPointsToReachDestination.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace
{
using Grid=MinimumInitialPointsToReachDestination::Grid;
}

TEST(MinimumInitialPointsToReachDestinationTest, GetMinimalInitialPointsUsingTabularDPWorksOnExample1)
{
    Grid inputGrid(3U, 3U,
    {-2,  -3,  3,
     -5, -10,  1,
     10,  30, -5});
    MinimumInitialPointsToReachDestination queryForTest(inputGrid);

    EXPECT_EQ(7, queryForTest.getMinimalInitialPointsUsingTabularDP());
}

}
