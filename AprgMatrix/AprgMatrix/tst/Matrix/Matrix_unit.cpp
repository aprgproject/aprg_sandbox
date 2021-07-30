#include <Matrix/Matrix.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedByDefaultConstructor)
{
    Matrix<unsigned int> matrix;

    EXPECT_EQ(0u, matrix.getColumns());
    EXPECT_EQ(0u, matrix.getRows());
    Matrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(0u, matrixData.size());
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithSize)
{
    Matrix<unsigned int> matrix(2,3);

    EXPECT_EQ(2u, matrix.getColumns());
    EXPECT_EQ(3u, matrix.getRows());
    Matrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(6u, matrixData.size());
    EXPECT_EQ(0u, matrixData.at(0));
    EXPECT_EQ(0u, matrixData.at(1));
    EXPECT_EQ(0u, matrixData.at(2));
    EXPECT_EQ(0u, matrixData.at(3));
    EXPECT_EQ(0u, matrixData.at(4));
    EXPECT_EQ(0u, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithMatrixDataWithSameSize)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    Matrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(6u, matrixData.size());
    EXPECT_EQ(1u, matrixData.at(0));
    EXPECT_EQ(2u, matrixData.at(1));
    EXPECT_EQ(3u, matrixData.at(2));
    EXPECT_EQ(4u, matrixData.at(3));
    EXPECT_EQ(5u, matrixData.at(4));
    EXPECT_EQ(6u, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithMatrixDataWithLesserSize)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5});

    Matrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(6u, matrixData.size());
    EXPECT_EQ(1u, matrixData.at(0));
    EXPECT_EQ(2u, matrixData.at(1));
    EXPECT_EQ(3u, matrixData.at(2));
    EXPECT_EQ(4u, matrixData.at(3));
    EXPECT_EQ(5u, matrixData.at(4));
    EXPECT_EQ(0u, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithMatrixDataWithGreaterSize)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6,7});

    Matrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(6u, matrixData.size());
    EXPECT_EQ(1u, matrixData.at(0));
    EXPECT_EQ(2u, matrixData.at(1));
    EXPECT_EQ(3u, matrixData.at(2));
    EXPECT_EQ(4u, matrixData.at(3));
    EXPECT_EQ(5u, matrixData.at(4));
    EXPECT_EQ(6u, matrixData.at(5));
}

TEST(AlbaMatrixTest, OperatorEqualWorks_MatrixCanBeCheckedIfEqual)
{
    Matrix<unsigned int> matrix1(2,3,
    {1,2,
     3,4,
     5,6});
    Matrix<unsigned int> matrix2(2,3);
    Matrix<unsigned int> matrix3(3,3);
    Matrix<unsigned int> matrix4(2,4);
    Matrix<unsigned int> matrix5(2,3);
    matrix2 = matrix1;
    matrix5.set(1, 1, 2);

    EXPECT_TRUE(matrix1==matrix1);
    EXPECT_TRUE(matrix1==matrix2);
    EXPECT_FALSE(matrix1==matrix3);
    EXPECT_FALSE(matrix1==matrix4);
    EXPECT_FALSE(matrix1==matrix5);
}

TEST(AlbaMatrixTest, OperatorPlusWorks_MatrixCanBeAdded)
{
    Matrix<unsigned int> matrix1(2,3,
    {1,2,
     3,4,
     5,6});

    Matrix<unsigned int> resultMatrix(matrix1+matrix1);

    EXPECT_EQ(2u, resultMatrix.get(0,0));
    EXPECT_EQ(4u, resultMatrix.get(1,0));
    EXPECT_EQ(6u, resultMatrix.get(0,1));
    EXPECT_EQ(8u, resultMatrix.get(1,1));
    EXPECT_EQ(10u, resultMatrix.get(0,2));
    EXPECT_EQ(12u, resultMatrix.get(1,2));
}

TEST(AlbaMatrixTest, OperatorMinusWorks_MatrixCanBeSubtracted)
{
    Matrix<unsigned int> matrix1(2,3,
    {100,200,
     300,400,
     500,600});
    Matrix<unsigned int> matrix2(2,3,
    {1,2,
     3,4,
     5,6});

    Matrix<unsigned int> resultMatrix(matrix1-matrix2);

    EXPECT_EQ(99u, resultMatrix.get(0,0));
    EXPECT_EQ(198u, resultMatrix.get(1,0));
    EXPECT_EQ(297u, resultMatrix.get(0,1));
    EXPECT_EQ(396u, resultMatrix.get(1,1));
    EXPECT_EQ(495u, resultMatrix.get(0,2));
    EXPECT_EQ(594u, resultMatrix.get(1,2));
}

TEST(AlbaMatrixTest, OperatorMultiplyWorks_MatrixCanBeMultipliedWithConstantValue)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    Matrix<unsigned int> resultMatrix(matrix*2);

    EXPECT_EQ(2u, resultMatrix.get(0,0));
    EXPECT_EQ(4u, resultMatrix.get(1,0));
    EXPECT_EQ(6u, resultMatrix.get(0,1));
    EXPECT_EQ(8u, resultMatrix.get(1,1));
    EXPECT_EQ(10u, resultMatrix.get(0,2));
    EXPECT_EQ(12u, resultMatrix.get(1,2));
}

TEST(AlbaMatrixTest, OperatorMultiplyWorks_MatrixCanBeMultipliedWithAnotherMatrix)
{
    Matrix<unsigned int> matrix1(2,3,
    {1,2,
     3,4,
     5,6});
    Matrix<unsigned int> matrix2(3,2,
    {1,3,5,
     2,4,6});

    Matrix<unsigned int> resultMatrix(matrix1*matrix2);

    EXPECT_EQ(1u, resultMatrix.get(0,0));
    EXPECT_EQ(4u, resultMatrix.get(1,0));
    EXPECT_EQ(9u, resultMatrix.get(0,1));
    EXPECT_EQ(16u, resultMatrix.get(1,1));
    EXPECT_EQ(25u, resultMatrix.get(0,2));
    EXPECT_EQ(36u, resultMatrix.get(1,2));
}

TEST(AlbaMatrixTest, IsIdentityMatrixWorks_MatrixCanBeCheckedIfItsIdentityMatrix)
{
    Matrix<unsigned int> matrix1(3,3,
    {1,0,0,
     0,1,0,
     0,0,1});
    Matrix<unsigned int> matrix2(3,3,
    {1,0,2,
     0,1,1,
     0,0,1});
    Matrix<unsigned int> matrix3(4,3,
    {1,0,0,0,
     0,1,0,0,
     0,0,1,0});

    EXPECT_TRUE(matrix1.isIdentityMatrix());
    EXPECT_FALSE(matrix2.isIdentityMatrix());
    EXPECT_FALSE(matrix3.isIdentityMatrix());
}

TEST(AlbaMatrixTest, IsReducedRowEchelonFormWorks_MatrixCanBeCheckedIfItsInReducedRowEchelonForm)
{
    Matrix<unsigned int> matrix1(4,3,
    {1,0,0,4,
     0,1,0,5,
     0,0,1,2});
    Matrix<unsigned int> matrix2(5,3,
    {1,2,0,0,2,
     0,0,1,0,1,
     0,0,0,1,0});
    Matrix<unsigned int> matrix3(5,5,
    {1,0,0,3,0,
     0,0,1,0,0,
     0,0,0,0,1,
     0,0,0,0,0,
     0,0,0,0,0});

    EXPECT_TRUE(matrix1.isReducedRowEchelonForm());
    EXPECT_TRUE(matrix2.isReducedRowEchelonForm());
    EXPECT_TRUE(matrix3.isReducedRowEchelonForm());
}

TEST(AlbaMatrixTest, IsReducedRowEchelonFormWorks_MatrixCanBeCheckedIfItsNotInReducedRowEchelonForm)
{
    Matrix<int> matrix1(4,3,
    {1,2,0,4,
     0,0,0,0,
     0,0,1,-3});
    Matrix<int> matrix2(4,3,
    {1,0,3,4,
     0,2,-2,5,
     0,0,1,2});
    Matrix<int> matrix3(4,4,
    {1,0,3,4,
     0,1,-2,5,
     0,1,2,2,
     0,0,0,0});
    Matrix<int> matrix4(4,4,
    {1,2,3,4,
     0,1,-2,5,
     0,0,1,2,
     0,0,0,0});

    EXPECT_FALSE(matrix1.isReducedRowEchelonForm());
    EXPECT_FALSE(matrix2.isReducedRowEchelonForm());
    EXPECT_FALSE(matrix3.isReducedRowEchelonForm());
    EXPECT_FALSE(matrix4.isReducedRowEchelonForm());
}

TEST(AlbaMatrixTest, GetColumnsWorks)
{
    Matrix<unsigned int> matrix(14,6);

    EXPECT_EQ(14u, matrix.getColumns());
}

TEST(AlbaMatrixTest, GetRowsWorks)
{
    Matrix<unsigned int> matrix(14,6);

    EXPECT_EQ(6u, matrix.getRows());
}

TEST(AlbaMatrixTest, GetMatrixIndexWorks)
{
    Matrix<unsigned int> matrix(14,6);

    EXPECT_EQ(45u, matrix.getMatrixIndex(3, 3));
    EXPECT_EQ(73u, matrix.getMatrixIndex(3, 5));
    EXPECT_EQ(47u, matrix.getMatrixIndex(5, 3));
    EXPECT_EQ(75u, matrix.getMatrixIndex(5, 5));
}

TEST(AlbaMatrixTest, GetMatrixDataWorks)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    Matrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());

    ASSERT_EQ(6u, matrixData.size());
    EXPECT_EQ(1u, matrixData.at(0));
    EXPECT_EQ(2u, matrixData.at(1));
    EXPECT_EQ(3u, matrixData.at(2));
    EXPECT_EQ(4u, matrixData.at(3));
    EXPECT_EQ(5u, matrixData.at(4));
    EXPECT_EQ(6u, matrixData.at(5));
}

TEST(AlbaMatrixTest, GetWorks_ValueCanBeFetchedFromEmptyVector)
{
    Matrix<unsigned int> matrix(2,3);

    EXPECT_EQ(0u, matrix.get(0,0));
    EXPECT_EQ(0u, matrix.get(1,0));
    EXPECT_EQ(0u, matrix.get(0,1));
    EXPECT_EQ(0u, matrix.get(1,1));
    EXPECT_EQ(0u, matrix.get(0,2));
    EXPECT_EQ(0u, matrix.get(1,2));
}

TEST(AlbaMatrixTest, GetStringWorks)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    EXPECT_EQ("-----\n|1|2|\n-----\n|3|4|\n-----\n|5|6|\n-----\n", matrix.getString());
}

TEST(AlbaMatrixTest, SetWorks_ValueCanSavedInTheMatrix)
{
    Matrix<unsigned int> matrix(2,3);

    matrix.set(0,0,1);
    matrix.set(1,0,2);
    matrix.set(0,1,3);
    matrix.set(1,1,4);
    matrix.set(0,2,5);
    matrix.set(1,2,6);

    EXPECT_EQ(1u, matrix.get(0,0));
    EXPECT_EQ(2u, matrix.get(1,0));
    EXPECT_EQ(3u, matrix.get(0,1));
    EXPECT_EQ(4u, matrix.get(1,1));
    EXPECT_EQ(5u, matrix.get(0,2));
    EXPECT_EQ(6u, matrix.get(1,2));
}

TEST(AlbaMatrixTest, SetWorks_MultipleValuesCanSavedInTheMatrix)
{
    Matrix<unsigned int> matrix(2,3);

    matrix.set(
    {1,2,
     3,4,
     5,6});

    EXPECT_EQ(1u, matrix.get(0,0));
    EXPECT_EQ(2u, matrix.get(1,0));
    EXPECT_EQ(3u, matrix.get(0,1));
    EXPECT_EQ(4u, matrix.get(1,1));
    EXPECT_EQ(5u, matrix.get(0,2));
    EXPECT_EQ(6u, matrix.get(1,2));
}

TEST(AlbaMatrixTest, SetWorks_OverwritesExistingValuesAndDoesNotChangeOtherValues)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.set(
    {9,8,
     7});

    EXPECT_EQ(9u, matrix.get(0,0));
    EXPECT_EQ(8u, matrix.get(1,0));
    EXPECT_EQ(7u, matrix.get(0,1));
    EXPECT_EQ(4u, matrix.get(1,1));
    EXPECT_EQ(5u, matrix.get(0,2));
    EXPECT_EQ(6u, matrix.get(1,2));
}

TEST(AlbaMatrixTest, ClearAndResizeWorks_MatrixCanBeResized)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.clearAndResize(3,2);

    EXPECT_EQ(0u, matrix.get(0,0));
    EXPECT_EQ(0u, matrix.get(0,1));
    EXPECT_EQ(0u, matrix.get(1,0));
    EXPECT_EQ(0u, matrix.get(1,1));
    EXPECT_EQ(0u, matrix.get(2,0));
    EXPECT_EQ(0u, matrix.get(2,1));
}

TEST(AlbaMatrixTest, TransposeWorks_MatrixCanBeTransposed)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.transpose();

    EXPECT_EQ(1u, matrix.get(0,0));
    EXPECT_EQ(3u, matrix.get(1,0));
    EXPECT_EQ(5u, matrix.get(2,0));
    EXPECT_EQ(2u, matrix.get(0,1));
    EXPECT_EQ(4u, matrix.get(1,1));
    EXPECT_EQ(6u, matrix.get(2,1));
}

TEST(AlbaMatrixTest, InvertWorks_InverseOfMatrixCanBeComputed)
{
    Matrix<double> matrix(3,3,
    {1.0,1.0,1.0,
     0.0,2.0,3.0,
     5.0,5.0,1});
    Matrix<double> copiedMatrix(matrix);

    matrix.invert();

    Matrix<double> multipliedMatrix(copiedMatrix*matrix);
    multipliedMatrix.transformToReducedEchelonForm();
    EXPECT_DOUBLE_EQ(1.625, matrix.get(0,0));
    EXPECT_DOUBLE_EQ(-0.5, matrix.get(1,0));
    EXPECT_DOUBLE_EQ(-0.125, matrix.get(2,0));
    EXPECT_DOUBLE_EQ(-1.875, matrix.get(0,1));
    EXPECT_DOUBLE_EQ(0.5, matrix.get(1,1));
    EXPECT_DOUBLE_EQ(0.375, matrix.get(2,1));
    EXPECT_DOUBLE_EQ(1.25, matrix.get(0,2));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(1,2));
    EXPECT_DOUBLE_EQ(-0.25, matrix.get(2,2));
    EXPECT_TRUE(multipliedMatrix.isIdentityMatrix());
}

TEST(AlbaMatrixTest, TransformToReducedEchelonFormWorks_MatrixTransformToReducedEchelonForm)
{
    Matrix<double> matrix(5,4,
    {0.0,2.0,3.0,-4.0,1,
     0.0,0.0,2.0,3.0,4.0,
     2.0,2.0,-5.0,2.0,4.0,
     2.0,0.0,-6.0,9.0,7.0});

    matrix.transformToReducedEchelonForm();

    EXPECT_DOUBLE_EQ(1.0, matrix.get(0,0));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(1,0));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(2,0));
    EXPECT_DOUBLE_EQ(9.0, matrix.get(3,0));
    EXPECT_DOUBLE_EQ(9.5, matrix.get(4,0));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(0,1));
    EXPECT_DOUBLE_EQ(1.0, matrix.get(1,1));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(2,1));
    EXPECT_DOUBLE_EQ(-4.25, matrix.get(3,1));
    EXPECT_DOUBLE_EQ(-2.5, matrix.get(4,1));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(0,2));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(1,2));
    EXPECT_DOUBLE_EQ(1.0, matrix.get(2,2));
    EXPECT_DOUBLE_EQ(1.5, matrix.get(3,2));
    EXPECT_DOUBLE_EQ(2.0, matrix.get(4,2));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(0,3));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(1,3));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(2,3));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(3,3));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(4,3));
}

TEST(AlbaMatrixTest, InterchangeRowsWorks_MatrixRowsCanBeInterchanged)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.interchangeRows(0,2);

    EXPECT_EQ(5u, matrix.get(0,0));
    EXPECT_EQ(6u, matrix.get(1,0));
    EXPECT_EQ(3u, matrix.get(0,1));
    EXPECT_EQ(4u, matrix.get(1,1));
    EXPECT_EQ(1u, matrix.get(0,2));
    EXPECT_EQ(2u, matrix.get(1,2));
}

TEST(AlbaMatrixTest, AddTwoRowsAndPutSumInAnotherRowWorks_MatrixRowsCanBeAdded)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.addTwoRowsAndPutSumInAnotherRow(0,2,2);

    EXPECT_EQ(1u, matrix.get(0,0));
    EXPECT_EQ(2u, matrix.get(1,0));
    EXPECT_EQ(3u, matrix.get(0,1));
    EXPECT_EQ(4u, matrix.get(1,1));
    EXPECT_EQ(6u, matrix.get(0,2));
    EXPECT_EQ(8u, matrix.get(1,2));
}

TEST(AlbaMatrixTest, MultiplyValueInRowAndPutProductInAnotherRowWorks_MatrixRowsCanBeMultipliedWithAValue)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.multiplyValueInRowAndPutProductInAnotherRow(0,2,0);
    matrix.multiplyValueInRowAndPutProductInAnotherRow(1,3,1);
    matrix.multiplyValueInRowAndPutProductInAnotherRow(2,4,2);

    EXPECT_EQ(2u, matrix.get(0,0));
    EXPECT_EQ(4u, matrix.get(1,0));
    EXPECT_EQ(9u, matrix.get(0,1));
    EXPECT_EQ(12u, matrix.get(1,1));
    EXPECT_EQ(20u, matrix.get(0,2));
    EXPECT_EQ(24u, matrix.get(1,2));
}

TEST(AlbaMatrixTest, SubtractRowsWithMultiplierPutDifferenceInAnotherRowWorks_MatrixRowsCanBeSubtractedWithMultiplier)
{
    Matrix<double> matrix(2,3,
    {1.0,2.0,
     3.0,4.0,
     5.0,6.0});

    matrix.subtractRowsWithMultiplierPutDifferenceInAnotherRow(1,0,3.0,1);
    matrix.subtractRowsWithMultiplierPutDifferenceInAnotherRow(2,0,5.0,2);

    EXPECT_DOUBLE_EQ(1.0, matrix.get(0,0));
    EXPECT_DOUBLE_EQ(2.0, matrix.get(1,0));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(0,1));
    EXPECT_DOUBLE_EQ(-2.0, matrix.get(1,1));
    EXPECT_DOUBLE_EQ(0.0, matrix.get(0,2));
    EXPECT_DOUBLE_EQ(-4.0, matrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeCopied)
{
    Matrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});
    Matrix<unsigned int> copiedMatrix;

    copiedMatrix = matrix;

    EXPECT_EQ(1u, copiedMatrix.get(0,0));
    EXPECT_EQ(2u, copiedMatrix.get(1,0));
    EXPECT_EQ(3u, copiedMatrix.get(0,1));
    EXPECT_EQ(4u, copiedMatrix.get(1,1));
    EXPECT_EQ(5u, copiedMatrix.get(0,2));
    EXPECT_EQ(6u, copiedMatrix.get(1,2));
}

}