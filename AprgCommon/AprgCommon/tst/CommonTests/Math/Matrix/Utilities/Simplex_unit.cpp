#include <Common/Math/Matrix/Utilities/Simplex.hpp>
#include <CommonTests/Math/Matrix/AlbaMatrixInternalFunctions.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace matrix
{

TEST(SimplexTest, ConstructSimplexTableWorks)
{
    AlbaMatrix<double> constraintsCoefficients(4, 3,
    {1.0, 2.0, 3.0, 4.0,
     5.0, 6.0, 7.0, 8.0,
     9.0, 10.0, 11.0, 12.0});
    AlbaMatrixData<double> constraintsValues{10.0, 20.0, 40.0};
    AlbaMatrixData<double> objectiveFunctionCoefficients{13.0, 14.0, 15.0, 16.0};

    AlbaMatrix<double> simplexTable(constructSimplexTable(constraintsCoefficients, constraintsValues, objectiveFunctionCoefficients));

    AlbaMatrix<double> expectedSimplexTable(8, 4,
    {1.0, 2.0, 3.0, 4.0, 1.0, 0.0, 0.0, 10.0,
     5.0, 6.0, 7.0, 8.0, 0.0, 1.0, 0.0, 20.0,
     9.0, 10.0, 11.0, 12.0, 0.0, 0.0, 1.0, 40.0,
     13.0, 14.0, 15.0, 16.0, 0.0, 0.0, 0.0, 0.0});
    EXPECT_EQ(expectedSimplexTable, simplexTable);
}

TEST(SimplexTest, SolveSimplexTableWorks)
{
    AlbaMatrix<double> simplexTable(8, 4,
    {1.0, 2.0, 3.0, 4.0, 1.0, 0.0, 0.0, 10.0,
     5.0, 6.0, 7.0, 8.0, 0.0, 1.0, 0.0, 20.0,
     9.0, 10.0, 11.0, 12.0, 0.0, 0.0, 1.0, 40.0,
     13.0, 14.0, 15.0, 16.0, 0.0, 0.0, 0.0, 0.0});

    solveSimplexTable(simplexTable);

    AlbaMatrix<double> expectedSimplexTable(8, 4,
    {0.0, 0.8, 1.6, 2.4, 1.0, -0.2, 0.0, 6.0,
     1.0, 1.2, 1.4, 1.6, 0.0, 0.2, 0.0, 4.0,
     0.0, -0.8, -1.6, -2.4, 0.0, -1.8, 1.0, 4.0,
     0.0, -1.6, -3.2, -4.8, 0.0, -2.6, 0.0, -52.0});
    EXPECT_EQ(expectedSimplexTable, simplexTable);
}

TEST(SimplexTest, SolveSimplexTableWorksOnBrewersProblem)
{
    AlbaMatrix<double> simplexTable(6, 4,
    {5.0, 15.0, 1.0, 0.0, 0.0, 480.0,
     4.0, 4.0, 0.0, 1.0, 0.0, 160.0,
     35.0, 20.0, 0.0, 0.0, 1.0, 1190.0,
     13.0, 23.0, 0.0, 0.0, 0.0, 0.0});

    solveSimplexTable(simplexTable);

    AlbaMatrix<double> expectedSimplexTable(6, 4,
    {0.0, 0.0, 1.5, -10.625, 1.0, 210.0,
     0.0, 1.0, 0.1, -0.125, 0.0, 28.0,
     1.0, 0.0, -0.1, 0.375, 0.0, 12.0,
     0.0, 0.0, -1.0, -2, 0.0, -800.0});
    EXPECT_EQ(expectedSimplexTable, simplexTable);
}

TEST(SimplexTest, IsOptimalWorks)
{
    AlbaMatrix<int> matrix1(3, 2,
    {1, 2, 3,
     4, 5, 6});
    AlbaMatrix<int> matrix2(3, 2,
    {1, 2, 3,
     4, -5, 6});
    AlbaMatrix<int> matrix3(3, 2,
    {1, 2, 3,
     -4, -5, -6});

    EXPECT_FALSE(isOptimal(matrix1));
    EXPECT_FALSE(isOptimal(matrix2));
    EXPECT_TRUE(isOptimal(matrix3));
}

TEST(SimplexTest, GetPivotingColumnUsingBlandsRuleWorks)
{
    AlbaMatrix<int> matrix1(3, 2,
    {1, 2, 3,
     4, 5, 6});
    AlbaMatrix<int> matrix2(3, 2,
    {1, 2, 3,
     -4, 5, 6});
    AlbaMatrix<int> matrix3(3, 2,
    {1, 2, 3,
     -4, -5, -6});

    EXPECT_EQ(0U, getPivotingColumnUsingBlandsRule(matrix1));
    EXPECT_EQ(1U, getPivotingColumnUsingBlandsRule(matrix2));
    EXPECT_EQ(3U, getPivotingColumnUsingBlandsRule(matrix3));
}

TEST(SimplexTest, GetPivotingRowUsingMinRatioRuleWorks)
{
    AlbaMatrix<double> matrix1(3, 3,
    {1.0, 1.0, 1.0,
     1.0, 2.0, 1.0,
     1.0, 3.0, 1.0});
    AlbaMatrix<double> matrix2(3, 3,
    {1.0, 3.0, 1.0,
     1.0, 2.0, 1.0,
     1.0, 1.0, 1.0});
    AlbaMatrix<double> matrix3(3, 3,
    {1.0, -1.0, 1.0,
     1.0, -2.0, 1.0,
     1.0, -3.0, 1.0});

    EXPECT_EQ(2U, getPivotingRowUsingMinRatioRule(matrix1, 1U));
    EXPECT_EQ(0U, getPivotingRowUsingMinRatioRule(matrix2, 1U));
    EXPECT_EQ(3U, getPivotingRowUsingMinRatioRule(matrix3, 1U));
}

TEST(SimplexTest, PivotAtWorks)
{
    AlbaMatrix<double> matrix(3, 3,
    {1.0, 2.0, 10.0,
     3.0, 4.0, 20.0,
     5.0, 6.0, 40.0});

    pivotAt(matrix, 2U, 2U);

    AlbaMatrix<double> expectedMatrix(3, 3,
    {-0.25, 0.5, 0.0,
     0.5, 1.0, 0.0,
     0.125, 0.15, 1});
    EXPECT_EQ(expectedMatrix, matrix);
}

}

}
