#include <Algorithm/LinearProgramming/SimplexAlgorithm.hpp>
#include <AlgorithmTests/Utilities/MatrixUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using SimplexForTest = SimplexAlgorithm<double>;
}

TEST(SimplexAlgorithmTest, SimplexWorksOnBrewersProblem) {
    SimplexForTest::Matrix constraintsCoefficients(
        2, 3,
        {
            5,
            15,
            4,
            4,
            35,
            20,
        });
    SimplexForTest::MatrixData constraintsValues{480, 160, 1190};
    SimplexForTest::MatrixData objectiveFunctionCoefficients{13, 23};
    SimplexForTest simplex(constraintsCoefficients, constraintsValues, objectiveFunctionCoefficients);

    SimplexForTest::Matrix expectedSolution(3, 3, {0.0, 0.0, 210.0, 0.0, 1.0, 28.0, 1.0, 0.0, 12.0});
    EXPECT_TRUE(simplex.isOptimized());
    EXPECT_DOUBLE_EQ(800, simplex.getOptimizedObjectiveValue());
    EXPECT_EQ(expectedSolution, simplex.getSolution());
}

}  // namespace algorithm

}  // namespace alba
