#include <Common/Math/Matrix/AlbaMatrixUtilities.hpp>
#include <CommonTests/Math/Matrix/AlbaMatrixInternalFunctions.hpp>

#include <gtest/gtest.h>
using namespace std;

namespace alba{

namespace matrix
{

TEST(AlbaMatrixUtilitiesTest, AreRowsWithAllZerosInTheBottomWorks)
{
    AlbaMatrix<unsigned int> matrix1(3, 3,
    {1, 2, 3,
     0, 0, 0,
     0, 0, 0});
    AlbaMatrix<unsigned int> matrix2(3, 3,
    {1, 2, 3,
     4, 5, 6,
     0, 0, 0});
    AlbaMatrix<unsigned int> matrix3(3, 3,
    {1, 2, 3,
     4, 5, 6,
     0, 1, 0});
    AlbaMatrix<unsigned int> matrix4(3, 3,
    {0, 0, 0,
     4, 5, 6,
     0, 0, 0});
    AlbaMatrix<unsigned int> matrix5(3, 3,
    {0, 0, 0,
     4, 5, 6,
     0, 0, 0});

    EXPECT_TRUE(areRowsWithAllZerosInTheBottom(matrix1));
    EXPECT_TRUE(areRowsWithAllZerosInTheBottom(matrix2));
    EXPECT_TRUE(areRowsWithAllZerosInTheBottom(matrix3));
    EXPECT_FALSE(areRowsWithAllZerosInTheBottom(matrix4));
    EXPECT_FALSE(areRowsWithAllZerosInTheBottom(matrix5));
}

TEST(AlbaMatrixUtilitiesTest, AreLeadingEntriesInReducedRowEchelonFormWorks)
{
    AlbaMatrix<unsigned int> matrix1(3, 3,
    {1, 0, 0,
     0, 1, 0,
     0, 0, 1});
    // matrix2 does not satisfy rule #2
    AlbaMatrix<unsigned int> matrix2(3, 3,
    {1, 0, 0,
     0, 2, 0,
     0, 0, 1});
    // matrix3 does not satisfy rule #3
    AlbaMatrix<unsigned int> matrix3(3, 3,
    {0, 1, 0,
     1, 0, 0,
     0, 0, 1});
    // matrix4 does not satisfy rule #4
    AlbaMatrix<unsigned int> matrix4(3, 3,
    {1, 1, 0,
     0, 1, 0,
     0, 0, 1});

    EXPECT_TRUE(areLeadingEntriesInReducedRowEchelonForm(matrix1));
    EXPECT_FALSE(areLeadingEntriesInReducedRowEchelonForm(matrix2));
    EXPECT_FALSE(areLeadingEntriesInReducedRowEchelonForm(matrix3));
    EXPECT_FALSE(areLeadingEntriesInReducedRowEchelonForm(matrix4));
}

TEST(AlbaMatrixUtilitiesTest, IsSquareWorks)
{
    AlbaMatrix<unsigned int> matrix1(3, 3,
    {0, 0, 0,
     0, 0, 0,
     0, 0, 0});
    AlbaMatrix<unsigned int> matrix2(3, 2,
    {0, 0, 0,
     0, 0, 0});

    EXPECT_TRUE(isSquare(matrix1));
    EXPECT_FALSE(isSquare(matrix2));
}

TEST(AlbaMatrixUtilitiesTest, IsZeroMatrixWorks)
{
    AlbaMatrix<unsigned int> matrix1(3, 3,
    {0, 0, 0,
     0, 0, 0,
     0, 0, 0});
    AlbaMatrix<unsigned int> matrix2(2, 2,
    {0, 0,
     0, 0});
    AlbaMatrix<unsigned int> matrix3(3, 3,
    {0, 0, 0,
     0, 1, 0,
     0, 0, 0});

    EXPECT_TRUE(isZeroMatrix(matrix1));
    EXPECT_TRUE(isZeroMatrix(matrix2));
    EXPECT_FALSE(isZeroMatrix(matrix3));
}

TEST(AlbaMatrixUtilitiesTest, IsIdentityMatrixWorks)
{
    AlbaMatrix<unsigned int> matrix1(3, 3,
    {1, 0, 0,
     0, 1, 0,
     0, 0, 1});
    AlbaMatrix<unsigned int> matrix2(3, 3,
    {1, 0, 2,
     0, 1, 1,
     0, 0, 1});
    AlbaMatrix<unsigned int> matrix3(4, 3,
    {1, 0, 0, 0,
     0, 1, 0, 0,
     0, 0, 1, 0});

    EXPECT_TRUE(isIdentityMatrix(matrix1));
    EXPECT_FALSE(isIdentityMatrix(matrix2));
    EXPECT_FALSE(isIdentityMatrix(matrix3));
}

TEST(AlbaMatrixUtilitiesTest, IsSingularWorks)
{
    AlbaMatrix<double> matrix1(3, 3,
    {1.0, 1.0, 1.0,
     0.0, 2.0, 3.0,
     5.0, 5.0, 1.0});
    AlbaMatrix<double> matrix2(3, 3,
    {1.0,  2.0, -3.0,
     1.0, -2.0,  1.0,
     5.0, -2.0, -3.0});

    EXPECT_FALSE(isSingular(matrix1));
    EXPECT_TRUE(isSingular(matrix2));
}

TEST(AlbaMatrixUtilitiesTest, IsReducedRowEchelonFormWorks_MatrixCanBeCheckedIfItsInReducedRowEchelonForm)
{
    AlbaMatrix<unsigned int> matrix1(4, 3,
    {1, 0, 0, 4,
     0, 1, 0, 5,
     0, 0, 1, 2});
    AlbaMatrix<unsigned int> matrix2(5, 3,
    {1, 2, 0, 0, 2,
     0, 0, 1, 0, 1,
     0, 0, 0, 1, 0});
    AlbaMatrix<unsigned int> matrix3(5, 5,
    {1, 0, 0, 3, 0,
     0, 0, 1, 0, 0,
     0, 0, 0, 0, 1,
     0, 0, 0, 0, 0,
     0, 0, 0, 0, 0});

    EXPECT_TRUE(isReducedRowEchelonForm(matrix1));
    EXPECT_TRUE(isReducedRowEchelonForm(matrix2));
    EXPECT_TRUE(isReducedRowEchelonForm(matrix3));
}

TEST(AlbaMatrixUtilitiesTest, IsReducedRowEchelonFormWorks_MatrixCanBeCheckedIfItsNotInReducedRowEchelonForm)
{
    AlbaMatrix<int> matrix1(4, 3,
    {1, 2, 0,  4,
     0, 0, 0,  0,
     0, 0, 1, -3});
    AlbaMatrix<int> matrix2(4, 3,
    {1, 0,  3, 4,
     0, 2, -2, 5,
     0, 0,  1, 2});
    AlbaMatrix<int> matrix3(4, 4,
    {1, 0,  3, 4,
     0, 1, -2, 5,
     0, 1,  2, 2,
     0, 0,  0, 0});
    AlbaMatrix<int> matrix4(4, 4,
    {1, 2,  3, 4,
     0, 1, -2, 5,
     0, 0,  1, 2,
     0, 0,  0, 0});

    EXPECT_FALSE(isReducedRowEchelonForm(matrix1));
    EXPECT_FALSE(isReducedRowEchelonForm(matrix2));
    EXPECT_FALSE(isReducedRowEchelonForm(matrix3));
    EXPECT_FALSE(isReducedRowEchelonForm(matrix4));
}

TEST(AlbaMatrixUtilitiesTest, GetBestIndexForCoFactorExpansionWorks)
{
    ListOfAlbaMatrixData<unsigned int> rowsAndColumns
    {{1, 2, 3}, {0, 5, 0}, {7, 0, 9}};

    EXPECT_EQ(1U, getBestIndexForCoFactorExpansion(rowsAndColumns));
}

TEST(AlbaMatrixUtilitiesTest, GetDeterminantWorks)
{
    AlbaMatrix<int> matrix1(1, 1, {5});
    AlbaMatrix<int> matrix2(2, 2,
    {2, -1,
     3,  2});
    AlbaMatrix<int> matrix3(3, 3,
    {1, 2, 3,
     2, 1, 3,
     3, 1, 2});
    AlbaMatrix<int> matrix4(4, 4,
    { 1, 2, -3,  4,
     -4, 2,  1,  3,
      3, 0,  0, -3,
      2, 0, -2,  3});
    AlbaMatrix<int> matrix5(4, 4,
    {4,  3,  2, 2,
     0,  1, -3, 3,
     0, -1,  3, 3,
     0,  3,  1, 1});
    AlbaMatrix<int> matrix6(4, 4,
    {1,  2,  3, 4,
     2,  5,  7, 3,
     4, 10, 14, 6,
     3,  4,  2, 7});

    EXPECT_EQ(5, getDeterminant(matrix1));
    EXPECT_EQ(7, getDeterminant(matrix2));
    EXPECT_EQ(6, getDeterminant(matrix3));
    EXPECT_EQ(48, getDeterminant(matrix4));
    EXPECT_EQ(-240, getDeterminant(matrix5));
    EXPECT_EQ(0, getDeterminant(matrix6));
}

TEST(AlbaMatrixUtilitiesTest, GetValueUsingCramerRuleWorks)
{
    AlbaMatrix<int> matrix(3, 3,
    { 3, 0, -1,
     -3, 1,  1,
     -5, 0,  2});
    AlbaMatrix<int>::MatrixData newColumn{3,2,4};

    EXPECT_EQ(10, getValueUsingCramerRule(matrix, 0, newColumn));
    EXPECT_EQ(5, getValueUsingCramerRule(matrix, 1, newColumn));
    EXPECT_EQ(27, getValueUsingCramerRule(matrix, 2, newColumn));
}

TEST(AlbaMatrixUtilitiesTest, GetValueFromCoFactorExpansionWorks)
{
    AlbaMatrix<int> matrix(4, 4,
    { 1, 2, -3,  4,
     -4, 2,  1,  3,
      3, 0,  0, -3,
      2, 0, -2,  3});

    EXPECT_EQ(-12, getValueFromCoFactorExpansion(matrix, 0, 0));
    EXPECT_EQ(30, getValueFromCoFactorExpansion(matrix, 1, 1));
    EXPECT_EQ(0, getValueFromCoFactorExpansion(matrix, 2, 2));
    EXPECT_EQ(72, getValueFromCoFactorExpansion(matrix, 3, 3));
}

TEST(AlbaMatrixUtilitiesTest, GetDeterminantWhenSideIsMoreThan2Works)
{
    AlbaMatrix<int> matrix(4, 4,
    { 1, 2, -3,  4,
     -4, 2,  1,  3,
      3, 0,  0, -3,
      2, 0, -2,  3});

    EXPECT_EQ(48, getDeterminantWhenSideIsMoreThan2(matrix));
}

TEST(AlbaMatrixUtilitiesTest, GetMatrixWithOneColumnAndOneRowRemovedWorks)
{
    AlbaMatrix<unsigned int> matrix(3, 3,
    {1, 2, 3,
     4, 5, 6,
     7, 8, 9});

    AlbaMatrix<unsigned int> resultMatrix(getMatrixWithOneColumnAndOneRowRemoved(matrix, 1, 2));

    AlbaMatrix<unsigned int> expectedMatrix(2, 2,
    {1, 3,
     4, 6});
    EXPECT_EQ(expectedMatrix, resultMatrix);
}

TEST(AlbaMatrixUtilitiesTest, DoUnaryOperationWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int> resultMatrix(
                doUnaryOperation(matrix, UnaryFunction<unsigned int>([](unsigned int const& value)
    {
        return (100+value)*value;
    })));

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {101, 204,
     309, 416,
     525, 636});
    EXPECT_EQ(expectedMatrix, resultMatrix);
}

TEST(AlbaMatrixUtilitiesTest, DoBinaryOperationWithSameDimensionsWorks)
{
    AlbaMatrix<unsigned int> matrix1(2, 3,
    {1, 2,
     3, 4,
     5, 6});
    AlbaMatrix<unsigned int> matrix2(2, 3,
    {11, 12,
     13, 14,
     15, 16});

    AlbaMatrix<unsigned int> resultMatrix(
                doBinaryOperationWithSameDimensions(matrix1, matrix2, BinaryFunction<unsigned int>([](unsigned int const& value1, unsigned int const& value2)
    {
        return (value1+value2)*value2;
    })));

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {132, 168,
     208, 252,
     300, 352});
    EXPECT_EQ(expectedMatrix, resultMatrix);
}

TEST(AlbaMatrixUtilitiesTest, TransformToReducedEchelonFormWorks)
{
    AlbaMatrix<double> matrix(5, 4,
    {0.0, 2.0,  3.0, -4.0, 1.0,
     0.0, 0.0,  2.0,  3.0, 4.0,
     2.0, 2.0, -5.0,  2.0, 4.0,
     2.0, 0.0, -6.0,  9.0, 7.0});

    transformToReducedEchelonFormUsingGaussJordanReduction(matrix);

    AlbaMatrix<double> expectedMatrix(5, 4,
    {1.0, 0.0, 0.0,   9.0,  9.5,
     0.0, 1.0, 0.0, -4.25, -2.5,
     0.0, 0.0, 1.0,   1.5,  2.0,
     0.0, 0.0, 0.0,   0.0,  0.0});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, ProductOfMatrixAndItsInvertWithReducedEchelonFormResultsToIdentityMatrix)
{
    AlbaMatrix<double> matrix(3, 3,
    {1.0, 1.0, 1.0,
     0.0, 2.0, 3.0,
     5.0, 5.0, 1.0});
    AlbaMatrix<double> invertedMatrix(matrix);

    invertedMatrix.invert();

    AlbaMatrix<double> product(invertedMatrix*matrix);
    transformToReducedEchelonFormUsingGaussJordanReduction(product);
    EXPECT_TRUE(isIdentityMatrix(product));
}

TEST(AlbaMatrixUtilitiesTest, InterchangeRowsWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    interchangeRows(matrix, 0, 2);

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {5, 6,
     3, 4,
     1, 2});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, AddTwoRowsAndPutSumInAnotherRowWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    addTwoRowsAndPutSumInAnotherRow(matrix, 0, 2, 2);

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {1, 2,
     3, 4,
     6, 8});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, MultiplyValueInRowAndPutProductInAnotherRowWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    multiplyValueInRowAndPutProductInAnotherRow(matrix, 2U, 0, 0);
    multiplyValueInRowAndPutProductInAnotherRow(matrix, 3U, 1, 1);
    multiplyValueInRowAndPutProductInAnotherRow(matrix, 4U, 2, 2);

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    { 2,  4,
      9, 12,
     20, 24});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, SubtractRowsWithMultiplierPutDifferenceInAnotherRowWorks)
{
    AlbaMatrix<double> matrix(2, 3,
    {1.0, 2.0,
     3.0, 4.0,
     5.0, 6.0});

    subtractRowsWithMultiplierPutDifferenceInAnotherRow(matrix, 3.0, 1, 0, 1);
    subtractRowsWithMultiplierPutDifferenceInAnotherRow(matrix, 5.0, 2, 0, 2);

    AlbaMatrix<double> expectedMatrix(2, 3,
    {1.0,  2.0,
     0.0, -2.0,
     0.0, -4.0});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, TraverseWithUnaryOperationForDifferentRowsWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    traverseWithUnaryOperationForDifferentRows(matrix, 0, 1, UnaryFunction<unsigned int>([](unsigned int const& value)
    {
        return (100+value)*value;
    }));

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {  1,   2,
     101, 204,
       5,   6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, TraverseWithBinaryOperationForDifferentRowsWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    traverseWithBinaryOperationForDifferentRows(matrix, 0, 1, 2, BinaryFunction<unsigned int>([](unsigned int const& value1, unsigned int const& value2)
    {
        return (value1+value2)*value2;
    }));

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    { 1,  2,
      3,  4,
     12, 24});
    EXPECT_EQ(expectedMatrix, matrix);
}

}

}
