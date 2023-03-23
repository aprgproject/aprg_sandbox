#include <AprgUniqueProblems/DynamicProgramming/Other/MinimumCostPolygonTriangulation.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(MinimumCostPolygonTriangulationTest, GetMinimumNumberOfOperationsWorksOnExample1)
{
    MinimumCostPolygonTriangulation queryForTest({{0,2}, {1,2}, {2,1}, {1,0}, {0,0}});

    EXPECT_DOUBLE_EQ(15.300563079745769, queryForTest.getMinimumNumberOfOperationsUsingNaiveRecursion());
    EXPECT_DOUBLE_EQ(15.300563079745769, queryForTest.getMinimumNumberOfOperationsUsingMemoizationDP());
    EXPECT_DOUBLE_EQ(15.300563079745769, queryForTest.getMinimumNumberOfOperationsUsingIterativeDP());
}

}
