#include <AprgUniqueProblems/DynamicProgramming/Grid/MaximumSizeSquareSubMatrixWithAllOnes.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace
{
using BooleanMatrix=MaximumSizeSquareSubMatrixWithAllOnes::BooleanMatrix;
}

TEST(MaximumSizeSquareSubMatrixWithAllOnesTest, GetMinimumPriceWorksOnExample1)
{
    BooleanMatrix booleanMatrix(5U, 6U,
    {false, true , true , false, true ,
     true , true , false, true , false,
     false, true , true , true , false,
     true , true , true , true , false,
     true , true , true , true , true ,
     false, false, false, false, false});
    MaximumSizeSquareSubMatrixWithAllOnes queryForTest(booleanMatrix);

    EXPECT_EQ(9U, queryForTest.getMaximumSquareAreaUsingMemoizationDP());
    EXPECT_EQ(9U, queryForTest.getMaximumSquareAreaUsingIterativeDP());
    EXPECT_EQ(9U, queryForTest.getMaximumSquareAreaUsingIterativeDPAndTimeEfficient());
}

}
