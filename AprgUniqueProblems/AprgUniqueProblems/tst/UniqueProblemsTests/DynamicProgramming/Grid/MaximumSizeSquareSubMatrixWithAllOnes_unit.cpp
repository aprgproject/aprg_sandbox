#include <UniqueProblems/DynamicProgramming/Grid/MaximumSizeSquareSubMatrixWithAllOnes.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace {
using BooleanMatrix = MaximumSizeSquareSubMatrixWithAllOnes::BooleanMatrix;
}

TEST(MaximumSizeSquareSubMatrixWithAllOnesTest, GetMinimumPriceWorksOnExample1) {
    BooleanMatrix booleanMatrix(
        5, 6, {false, true, true, false, true,  true, true, false, true, false, false, true,  true,  true,  false,
                 true,  true, true, true,  false, true, true, true,  true, true,  false, false, false, false, false});
    MaximumSizeSquareSubMatrixWithAllOnes queryForTest(booleanMatrix);

    EXPECT_EQ(9, queryForTest.getMaximumSquareAreaUsingMemoizationDP());
    EXPECT_EQ(9, queryForTest.getMaximumSquareAreaUsingIterativeDP());
    EXPECT_EQ(9, queryForTest.getMaximumSquareAreaUsingIterativeDPAndTimeEfficient());
}

}  // namespace alba
