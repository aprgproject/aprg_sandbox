#include <Matrix/Matrix.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreatedByDefaultConstructor)
{
    Matrix<unsigned int> inputMatrix;

    EXPECT_EQ(0u, inputMatrix.getColumns());
    EXPECT_EQ(0u, inputMatrix.getRows());
}

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreated)
{
    Matrix<unsigned int> inputMatrix(2,3);

    EXPECT_EQ(2u, inputMatrix.getColumns());
    EXPECT_EQ(3u, inputMatrix.getRows());
}

TEST(AlbaMatrixTest, ValueCanBeFetchedFromEmptyVector)
{
    Matrix<unsigned int> inputMatrix(2,3);

    EXPECT_EQ(0u, inputMatrix.get(0,0));
    EXPECT_EQ(0u, inputMatrix.get(1,0));
    EXPECT_EQ(0u, inputMatrix.get(0,1));
    EXPECT_EQ(0u, inputMatrix.get(1,1));
    EXPECT_EQ(0u, inputMatrix.get(0,2));
    EXPECT_EQ(0u, inputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, ValueCanSavedInTheMatrix)
{
    Matrix<unsigned int> inputMatrix(2,3);
    inputMatrix.set(0,0,1);
    inputMatrix.set(1,0,2);
    inputMatrix.set(0,1,3);
    inputMatrix.set(1,1,4);
    inputMatrix.set(0,2,5);
    inputMatrix.set(1,2,6);

    EXPECT_EQ(1u, inputMatrix.get(0,0));
    EXPECT_EQ(2u, inputMatrix.get(1,0));
    EXPECT_EQ(3u, inputMatrix.get(0,1));
    EXPECT_EQ(4u, inputMatrix.get(1,1));
    EXPECT_EQ(5u, inputMatrix.get(0,2));
    EXPECT_EQ(6u, inputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, ValuesCanSavedInTheMatrix)
{
    Matrix<unsigned int> inputMatrix(2,3);
    inputMatrix.set({1,2,
                     3,4,
                     5,6});

    EXPECT_EQ(1u, inputMatrix.get(0,0));
    EXPECT_EQ(2u, inputMatrix.get(1,0));
    EXPECT_EQ(3u, inputMatrix.get(0,1));
    EXPECT_EQ(4u, inputMatrix.get(1,1));
    EXPECT_EQ(5u, inputMatrix.get(0,2));
    EXPECT_EQ(6u, inputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeTraversedAndCopied)
{
    Matrix<unsigned int> inputMatrix(2,3);
    Matrix<unsigned int> outputMatrix(2,3);
    inputMatrix.set({1,2,
                     3,4,
                     5,6});
    outputMatrix = inputMatrix;

    EXPECT_EQ(1u, outputMatrix.get(0,0));
    EXPECT_EQ(2u, outputMatrix.get(1,0));
    EXPECT_EQ(3u, outputMatrix.get(0,1));
    EXPECT_EQ(4u, outputMatrix.get(1,1));
    EXPECT_EQ(5u, outputMatrix.get(0,2));
    EXPECT_EQ(6u, outputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeCheckedIfEqual)
{
    Matrix<unsigned int> inputMatrix(2,3);
    Matrix<unsigned int> outputMatrix(2,3);
    inputMatrix.set({1,2,
                     3,4,
                     5,6});
    outputMatrix = inputMatrix;

    EXPECT_EQ(outputMatrix, inputMatrix);
}

TEST(AlbaMatrixTest, MatrixCanBeResized)
{
    Matrix<unsigned int> inputMatrix(2,3);
    inputMatrix.clearAndResize(3,2);

    EXPECT_EQ(0u, inputMatrix.get(0,0));
    EXPECT_EQ(0u, inputMatrix.get(0,1));
    EXPECT_EQ(0u, inputMatrix.get(1,0));
    EXPECT_EQ(0u, inputMatrix.get(1,1));
    EXPECT_EQ(0u, inputMatrix.get(2,0));
    EXPECT_EQ(0u, inputMatrix.get(2,1));
}

TEST(AlbaMatrixTest, MatrixCanBeTransposed)
{
    Matrix<unsigned int> inputMatrix(2,3);
    inputMatrix.set({1,2,
                     3,4,
                     5,6});
    inputMatrix.transpose();

    EXPECT_EQ(1u, inputMatrix.get(0,0));
    EXPECT_EQ(3u, inputMatrix.get(1,0));
    EXPECT_EQ(5u, inputMatrix.get(2,0));
    EXPECT_EQ(2u, inputMatrix.get(0,1));
    EXPECT_EQ(4u, inputMatrix.get(1,1));
    EXPECT_EQ(6u, inputMatrix.get(2,1));
}

TEST(AlbaMatrixTest, MatrixCanBeAdded)
{
    Matrix<unsigned int> inputMatrix1(2,3);
    inputMatrix1.set({1,2,
                      3,4,
                      5,6});
    Matrix<unsigned int> outputMatrix(inputMatrix1+inputMatrix1);

    EXPECT_EQ(2u, outputMatrix.get(0,0));
    EXPECT_EQ(4u, outputMatrix.get(1,0));
    EXPECT_EQ(6u, outputMatrix.get(0,1));
    EXPECT_EQ(8u, outputMatrix.get(1,1));
    EXPECT_EQ(10u, outputMatrix.get(0,2));
    EXPECT_EQ(12u, outputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeSubtracted)
{
    Matrix<unsigned int> inputMatrix1(2,3);
    Matrix<unsigned int> inputMatrix2(2,3);
    inputMatrix1.set({100,200,
                      300,400,
                      500,600});
    inputMatrix2.set({1,2,
                      3,4,
                      5,6});
    Matrix<unsigned int> outputMatrix(inputMatrix1-inputMatrix2);

    EXPECT_EQ(99u, outputMatrix.get(0,0));
    EXPECT_EQ(198u, outputMatrix.get(1,0));
    EXPECT_EQ(297u, outputMatrix.get(0,1));
    EXPECT_EQ(396u, outputMatrix.get(1,1));
    EXPECT_EQ(495u, outputMatrix.get(0,2));
    EXPECT_EQ(594u, outputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeMultipliedWithConstantValue)
{
    Matrix<unsigned int> inputMatrix(2,3);
    inputMatrix.set({1,2,
                     3,4,
                     5,6});
    Matrix<unsigned int> outputMatrix(inputMatrix*2);

    EXPECT_EQ(2u, outputMatrix.get(0,0));
    EXPECT_EQ(4u, outputMatrix.get(1,0));
    EXPECT_EQ(6u, outputMatrix.get(0,1));
    EXPECT_EQ(8u, outputMatrix.get(1,1));
    EXPECT_EQ(10u, outputMatrix.get(0,2));
    EXPECT_EQ(12u, outputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeMultipliedWithAnotherMatrix)
{
    Matrix<unsigned int> inputMatrix1(2,3);
    Matrix<unsigned int> inputMatrix2(3,2);
    inputMatrix1.set({1,2,
                      3,4,
                      5,6});
    inputMatrix2.set({1,3,5,
                      2,4,6});
    Matrix<unsigned int> outputMatrix(inputMatrix1*inputMatrix2);

    EXPECT_EQ(1u, outputMatrix.get(0,0));
    EXPECT_EQ(4u, outputMatrix.get(1,0));
    EXPECT_EQ(9u, outputMatrix.get(0,1));
    EXPECT_EQ(16u, outputMatrix.get(1,1));
    EXPECT_EQ(25u, outputMatrix.get(0,2));
    EXPECT_EQ(36u, outputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeCheckedIfItsIdentityMatrix)
{
    Matrix<unsigned int> inputMatrix1(3,3);
    Matrix<unsigned int> inputMatrix2(3,3);
    Matrix<unsigned int> inputMatrix3(4,3);
    inputMatrix1.set({1,0,0,
                      0,1,0,
                      0,0,1});
    inputMatrix2.set({1,0,2,
                      0,1,1,
                      0,0,1});
    inputMatrix3.set({1,0,0,0,
                      0,1,0,0,
                      0,0,1,0});

    EXPECT_TRUE(inputMatrix1.isIdentityMatrix());
    EXPECT_FALSE(inputMatrix2.isIdentityMatrix());
    EXPECT_FALSE(inputMatrix3.isIdentityMatrix());
}

TEST(AlbaMatrixTest, MatrixCanBeCheckedIfItsInReducedRowEchelonForm)
{
    Matrix<unsigned int> inputMatrix1(4,3);
    Matrix<unsigned int> inputMatrix2(5,3);
    Matrix<unsigned int> inputMatrix3(5,5);
    inputMatrix1.set({1,0,0,4,
                      0,1,0,5,
                      0,0,1,2});
    inputMatrix2.set({1,2,0,0,2,
                      0,0,1,0,1,
                      0,0,0,1,0});
    inputMatrix3.set({1,0,0,3,0,
                      0,0,1,0,0,
                      0,0,0,0,1,
                      0,0,0,0,0,
                      0,0,0,0,0});

    EXPECT_TRUE(inputMatrix1.isReducedRowEchelonForm());
    EXPECT_TRUE(inputMatrix2.isReducedRowEchelonForm());
    EXPECT_TRUE(inputMatrix3.isReducedRowEchelonForm());
}

TEST(AlbaMatrixTest, MatrixCanBeCheckedIfItsNotInReducedRowEchelonForm)
{
    Matrix<int> inputMatrix1(4,3);
    Matrix<int> inputMatrix2(4,3);
    Matrix<int> inputMatrix3(4,4);
    Matrix<int> inputMatrix4(4,4);
    inputMatrix1.set({1,2,0,4,
                      0,0,0,0,
                      0,0,1,-3});
    inputMatrix2.set({1,0,3,4,
                      0,2,-2,5,
                      0,0,1,2});
    inputMatrix3.set({1,0,3,4,
                      0,1,-2,5,
                      0,1,2,2,
                      0,0,0,0});
    inputMatrix4.set({1,2,3,4,
                      0,1,-2,5,
                      0,0,1,2,
                      0,0,0,0});

    EXPECT_FALSE(inputMatrix1.isReducedRowEchelonForm());
    EXPECT_FALSE(inputMatrix2.isReducedRowEchelonForm());
    EXPECT_FALSE(inputMatrix3.isReducedRowEchelonForm());
    EXPECT_FALSE(inputMatrix4.isReducedRowEchelonForm());
}

TEST(AlbaMatrixTest, MatrixRowsCanBeInterchanged)
{
    Matrix<unsigned int> inputMatrix(2,3);
    inputMatrix.set({1,2,
                     3,4,
                     5,6});
    inputMatrix.interchangeRows(0,2);

    EXPECT_EQ(5u, inputMatrix.get(0,0));
    EXPECT_EQ(6u, inputMatrix.get(1,0));
    EXPECT_EQ(3u, inputMatrix.get(0,1));
    EXPECT_EQ(4u, inputMatrix.get(1,1));
    EXPECT_EQ(1u, inputMatrix.get(0,2));
    EXPECT_EQ(2u, inputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixRowsCanBeAdded)
{
    Matrix<unsigned int> inputMatrix(2,3);
    inputMatrix.set({1,2,
                     3,4,
                     5,6});
    inputMatrix.addRows(0,2,2);

    EXPECT_EQ(1u, inputMatrix.get(0,0));
    EXPECT_EQ(2u, inputMatrix.get(1,0));
    EXPECT_EQ(3u, inputMatrix.get(0,1));
    EXPECT_EQ(4u, inputMatrix.get(1,1));
    EXPECT_EQ(6u, inputMatrix.get(0,2));
    EXPECT_EQ(8u, inputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixRowsCanBeMultiplied)
{
    Matrix<unsigned int> inputMatrix(2,3);
    inputMatrix.set({1,2,
                     3,4,
                     5,6});
    inputMatrix.multiplyValueInRow(0,2,0);
    inputMatrix.multiplyValueInRow(1,3,1);
    inputMatrix.multiplyValueInRow(2,4,2);

    EXPECT_EQ(2u, inputMatrix.get(0,0));
    EXPECT_EQ(4u, inputMatrix.get(1,0));
    EXPECT_EQ(9u, inputMatrix.get(0,1));
    EXPECT_EQ(12u, inputMatrix.get(1,1));
    EXPECT_EQ(20u, inputMatrix.get(0,2));
    EXPECT_EQ(24u, inputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixRowsCanBeSubtractedWithMultiplier)
{
    Matrix<double> inputMatrix(2,3);
    inputMatrix.set({1.0,2.0,
                     3.0,4.0,
                     5.0,6.0});
    inputMatrix.subtractRowsWithMultiplier(1,0,3.0,1);
    inputMatrix.subtractRowsWithMultiplier(2,0,5.0,2);

    EXPECT_DOUBLE_EQ(1.0, inputMatrix.get(0,0));
    EXPECT_DOUBLE_EQ(2.0, inputMatrix.get(1,0));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(0,1));
    EXPECT_DOUBLE_EQ(-2.0, inputMatrix.get(1,1));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(0,2));
    EXPECT_DOUBLE_EQ(-4.0, inputMatrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixTransformToReducedEchelonForm)
{
    Matrix<double> inputMatrix(5,4);
    inputMatrix.set({0.0,2.0,3.0,-4.0,1,
                     0.0,0.0,2.0,3.0,4.0,
                     2.0,2.0,-5.0,2.0,4.0,
                     2.0,0.0,-6.0,9.0,7.0});
    inputMatrix.transformToReducedEchelonForm();

    EXPECT_DOUBLE_EQ(1.0, inputMatrix.get(0,0));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(1,0));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(2,0));
    EXPECT_DOUBLE_EQ(9.0, inputMatrix.get(3,0));
    EXPECT_DOUBLE_EQ(9.5, inputMatrix.get(4,0));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(0,1));
    EXPECT_DOUBLE_EQ(1.0, inputMatrix.get(1,1));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(2,1));
    EXPECT_DOUBLE_EQ(-4.25, inputMatrix.get(3,1));
    EXPECT_DOUBLE_EQ(-2.5, inputMatrix.get(4,1));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(0,2));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(1,2));
    EXPECT_DOUBLE_EQ(1.0, inputMatrix.get(2,2));
    EXPECT_DOUBLE_EQ(1.5, inputMatrix.get(3,2));
    EXPECT_DOUBLE_EQ(2.0, inputMatrix.get(4,2));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(0,3));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(1,3));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(2,3));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(3,3));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(4,3));
}

TEST(AlbaMatrixTest, InverseOfMatrixCanBeComputed)
{
    Matrix<double> inputMatrix(3,3);
    inputMatrix.set({1.0,1.0,1.0,
                     0.0,2.0,3.0,
                     5.0,5.0,1});
    Matrix<double> copiedMatrix(inputMatrix);
    inputMatrix.invert();
    Matrix<double> multipliedMatrix(copiedMatrix*inputMatrix);
    multipliedMatrix.transformToReducedEchelonForm();

    EXPECT_DOUBLE_EQ(1.625, inputMatrix.get(0,0));
    EXPECT_DOUBLE_EQ(-0.5, inputMatrix.get(1,0));
    EXPECT_DOUBLE_EQ(-0.125, inputMatrix.get(2,0));
    EXPECT_DOUBLE_EQ(-1.875, inputMatrix.get(0,1));
    EXPECT_DOUBLE_EQ(0.5, inputMatrix.get(1,1));
    EXPECT_DOUBLE_EQ(0.375, inputMatrix.get(2,1));
    EXPECT_DOUBLE_EQ(1.25, inputMatrix.get(0,2));
    EXPECT_DOUBLE_EQ(0.0, inputMatrix.get(1,2));
    EXPECT_DOUBLE_EQ(-0.25, inputMatrix.get(2,2));
    EXPECT_TRUE(multipliedMatrix.isIdentityMatrix());
}

}
