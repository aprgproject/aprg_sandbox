#include <Common/Math/Matrix/Utilities/Simplex.hpp>
#include <CommonTests/Math/Matrix/AlbaMatrixInternalFunctions.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::matrix {

TEST(SimplexTest, ConstructSimplexTableWorks) {
    AlbaMatrix<double> constraintsCoefficients(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
    AlbaMatrixData<double> constraintsValues{10, 20, 40};
    AlbaMatrixData<double> objectiveFunctionCoefficients{13, 14, 15, 16};

    AlbaMatrix<double> simplexTable(constructSimplexTableWithLessThanConstraints(
        constraintsCoefficients, constraintsValues, objectiveFunctionCoefficients));

    AlbaMatrix<double> expectedSimplexTable(8, 4, {1, 2,  3,  4,  1, 0, 0, 10, 5,  6,  7,  8,  0, 1, 0, 20,
                                                   9, 10, 11, 12, 0, 0, 1, 40, 13, 14, 15, 16, 0, 0, 0, 0});
    EXPECT_EQ(expectedSimplexTable, simplexTable);
}

TEST(SimplexTest, SolveSimplexTableWorks) {
    AlbaMatrix<double> simplexTable(8, 4, {1, 2,  3,  4,  1, 0, 0, 10, 5,  6,  7,  8,  0, 1, 0, 20,
                                           9, 10, 11, 12, 0, 0, 1, 40, 13, 14, 15, 16, 0, 0, 0, 0});

    solveSimplexTable(simplexTable);

    AlbaMatrix<double> expectedSimplexTable(
        8, 4, {0, 0.8,  1.6,  2.4,  1, -0.2, 0, 6, 1, 1.2,  1.4,  1.6,  0, 0.2,  0, 4,
               0, -0.8, -1.6, -2.4, 0, -1.8, 1, 4, 0, -1.6, -3.2, -4.8, 0, -2.6, 0, -52});
    EXPECT_EQ(expectedSimplexTable, simplexTable);
}

TEST(SimplexTest, SolveSimplexTableWorksOnBrewersProblem) {
    AlbaMatrix<double> simplexTable(
        6, 4, {5, 15, 1, 0, 0, 480, 4, 4, 0, 1, 0, 160, 35, 20, 0, 0, 1, 1190, 13, 23, 0, 0, 0, 0});

    solveSimplexTable(simplexTable);

    AlbaMatrix<double> expectedSimplexTable(
        6, 4, {0, 0, 1.5, -10.625, 1, 210, 0, 1, 0.1, -0.125, 0, 28, 1, 0, -0.1, 0.375, 0, 12, 0, 0, -1, -2, 0, -800});
    EXPECT_EQ(expectedSimplexTable, simplexTable);
}

TEST(SimplexTest, SolveSimplexTableWorksOnBrewersProblemWithZeroEquation) {
    AlbaMatrix<double> simplexTable(7, 5, {5, 15, 0, 1, 0, 0, 480, 0,  0,  1, 0, 0, 0, 0,  // zero equation
                                           4, 4,  0, 0, 1, 0, 160, 35, 20, 0, 0, 0, 1, 1190, 13, 23, 100, 0, 0, 0, 0});

    solveSimplexTable(simplexTable);

    AlbaMatrix<double> expectedSimplexTable(
        7, 5, {0,      0, 0,  1.5, -10.625, 1, 210,  0,     0, 1,  0, 0, 0, 0,  0,  1, 0,   0.1,
               -0.125, 0, 28, 1,   0,       0, -0.1, 0.375, 0, 12, 0, 0, 0, -1, -2, 0, -800});
    EXPECT_EQ(expectedSimplexTable, simplexTable);
}

TEST(SimplexTest, SolveSimplexTableWorksOnBrewersProblemWithEqualEquation) {
    AlbaMatrix<double> simplexTable(7, 5, {5, 15, 0, 1, 0, 0, 480, 0,  0,  1, 0, 0, 0, 200,  // equal equation
                                           4, 4,  0, 0, 1, 0, 160, 35, 20, 0, 0, 0, 1, 1190, 13, 23, 1, 0, 0, 0, 0});

    solveSimplexTable(simplexTable);

    AlbaMatrix<double> expectedSimplexTable(
        7, 5, {0,      0, 0,  1.5, -10.625, 1, 210,  0,     0, 1,  0, 0, 0, 200, 0,  1, 0,    0.1,
               -0.125, 0, 28, 1,   0,       0, -0.1, 0.375, 0, 12, 0, 0, 0, -1,  -2, 0, -1000});
    EXPECT_EQ(expectedSimplexTable, simplexTable);
}

TEST(SimplexTest, IsOptimalWorks) {
    AlbaMatrix<int> matrix1(3, 2, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(3, 2, {1, 2, 3, 4, -5, 6});
    AlbaMatrix<int> matrix3(3, 2, {1, 2, 3, -4, -5, -6});

    EXPECT_FALSE(isOptimal(matrix1));
    EXPECT_FALSE(isOptimal(matrix2));
    EXPECT_TRUE(isOptimal(matrix3));
}

TEST(SimplexTest, GetPivotingColumnUsingBlandsRuleWorks) {
    AlbaMatrix<int> matrix1(3, 2, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(3, 2, {1, 2, 3, -4, 5, 6});
    AlbaMatrix<int> matrix3(3, 2, {1, 2, 3, -4, -5, -6});

    EXPECT_EQ(0U, getPivotingColumnUsingBlandsRule(matrix1));
    EXPECT_EQ(1U, getPivotingColumnUsingBlandsRule(matrix2));
    EXPECT_EQ(3U, getPivotingColumnUsingBlandsRule(matrix3));
}

TEST(SimplexTest, GetPivotingRowUsingMinRatioRuleWorks) {
    AlbaMatrix<double> matrix1(3, 3, {1, 1, 1, 1, 2, 1, 1, 3, 1});
    AlbaMatrix<double> matrix2(3, 3, {1, 3, 1, 1, 2, 1, 1, 1, 1});
    AlbaMatrix<double> matrix3(3, 3, {1, -1, 1, 1, -2, 1, 1, -3, 1});

    EXPECT_EQ(1U, getPivotingRowUsingMinRatioRule(matrix1, 1U));
    EXPECT_EQ(0U, getPivotingRowUsingMinRatioRule(matrix2, 1U));
    EXPECT_EQ(3U, getPivotingRowUsingMinRatioRule(matrix3, 1U));
}

TEST(SimplexTest, PivotAtWorks) {
    AlbaMatrix<double> matrix(3, 3, {1, 2, 10, 3, 4, 20, 5, 6, 40});

    pivotAt(matrix, 2U, 2U);

    AlbaMatrix<double> expectedMatrix(3, 3, {-0.25, 0.5, 0, 0.5, 1, 0, 0.125, 0.15, 1});
    EXPECT_EQ(expectedMatrix, matrix);
}

}  // namespace alba::matrix
