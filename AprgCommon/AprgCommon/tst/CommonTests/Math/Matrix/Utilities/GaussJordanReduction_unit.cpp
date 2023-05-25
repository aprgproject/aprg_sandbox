#include <Common/Math/Matrix/Utilities/GaussJordanReduction.hpp>
#include <CommonTests/Math/Matrix/AlbaMatrixInternalFunctions.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::matrix {

TEST(GaussJordanReductionTest, AreRowsWithAllZerosInTheBottomWorks) {
    AlbaMatrix<int> matrix1(3, 3, {1, 2, 3, 0, 0, 0, 0, 0, 0});
    AlbaMatrix<int> matrix2(3, 3, {1, 2, 3, 4, 5, 6, 0, 0, 0});
    AlbaMatrix<int> matrix3(3, 3, {1, 2, 3, 4, 5, 6, 0, 1, 0});
    AlbaMatrix<int> matrix4(3, 3, {0, 0, 0, 4, 5, 6, 0, 0, 0});
    AlbaMatrix<int> matrix5(3, 3, {0, 0, 0, 4, 5, 6, 0, 0, 0});

    EXPECT_TRUE(areRowsWithAllZerosInTheBottom(matrix1));
    EXPECT_TRUE(areRowsWithAllZerosInTheBottom(matrix2));
    EXPECT_TRUE(areRowsWithAllZerosInTheBottom(matrix3));
    EXPECT_FALSE(areRowsWithAllZerosInTheBottom(matrix4));
    EXPECT_FALSE(areRowsWithAllZerosInTheBottom(matrix5));
}

TEST(GaussJordanReductionTest, AreLeadingEntriesInReducedRowEchelonFormWorks) {
    AlbaMatrix<int> matrix1(3, 3, {1, 0, 0, 0, 1, 0, 0, 0, 1});
    // matrix2 does not satisfy rule #2
    AlbaMatrix<int> matrix2(3, 3, {1, 0, 0, 0, 2, 0, 0, 0, 1});
    // matrix3 does not satisfy rule #3
    AlbaMatrix<int> matrix3(3, 3, {0, 1, 0, 1, 0, 0, 0, 0, 1});
    // matrix4 does not satisfy rule #4
    AlbaMatrix<int> matrix4(3, 3, {1, 1, 0, 0, 1, 0, 0, 0, 1});

    EXPECT_TRUE(areLeadingEntriesInReducedRowEchelonForm(matrix1));
    EXPECT_FALSE(areLeadingEntriesInReducedRowEchelonForm(matrix2));
    EXPECT_FALSE(areLeadingEntriesInReducedRowEchelonForm(matrix3));
    EXPECT_FALSE(areLeadingEntriesInReducedRowEchelonForm(matrix4));
}

TEST(GaussJordanReductionTest, IsReducedRowEchelonFormWorks_MatrixCanBeCheckedIfItsInReducedRowEchelonForm) {
    AlbaMatrix<int> matrix1(4, 3, {1, 0, 0, 4, 0, 1, 0, 5, 0, 0, 1, 2});
    AlbaMatrix<int> matrix2(5, 3, {1, 2, 0, 0, 2, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0});
    AlbaMatrix<int> matrix3(5, 5, {1, 0, 0, 3, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

    EXPECT_TRUE(isReducedRowEchelonForm(matrix1));
    EXPECT_TRUE(isReducedRowEchelonForm(matrix2));
    EXPECT_TRUE(isReducedRowEchelonForm(matrix3));
}

TEST(GaussJordanReductionTest, IsReducedRowEchelonFormWorks_MatrixCanBeCheckedIfItsNotInReducedRowEchelonForm) {
    AlbaMatrix<int> matrix1(4, 3, {1, 2, 0, 4, 0, 0, 0, 0, 0, 0, 1, -3});
    AlbaMatrix<int> matrix2(4, 3, {1, 0, 3, 4, 0, 2, -2, 5, 0, 0, 1, 2});
    AlbaMatrix<int> matrix3(4, 4, {1, 0, 3, 4, 0, 1, -2, 5, 0, 1, 2, 2, 0, 0, 0, 0});
    AlbaMatrix<int> matrix4(4, 4, {1, 2, 3, 4, 0, 1, -2, 5, 0, 0, 1, 2, 0, 0, 0, 0});

    EXPECT_FALSE(isReducedRowEchelonForm(matrix1));
    EXPECT_FALSE(isReducedRowEchelonForm(matrix2));
    EXPECT_FALSE(isReducedRowEchelonForm(matrix3));
    EXPECT_FALSE(isReducedRowEchelonForm(matrix4));
}

TEST(GaussJordanReductionTest, TransformToReducedEchelonFormWorks) {
    AlbaMatrix<double> matrix(
        5, 4, {0.0, 2.0, 3.0, -4.0, 1.0, 0.0, 0.0, 2.0, 3.0, 4.0, 2.0, 2.0, -5.0, 2.0, 4.0, 2.0, 0.0, -6.0, 9.0, 7.0});

    transformToReducedEchelonFormUsingGaussJordanReduction(matrix);

    AlbaMatrix<double> expectedMatrix(
        5, 4, {1.0, 0.0, 0.0, 9.0, 9.5, 0.0, 1.0, 0.0, -4.25, -2.5, 0.0, 0.0, 1.0, 1.5, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(GaussJordanReductionTest, ProductOfMatrixAndItsInvertWithReducedEchelonFormResultsToIdentityMatrix) {
    AlbaMatrix<double> matrix(3, 3, {1.0, 1.0, 1.0, 0.0, 2.0, 3.0, 5.0, 5.0, 1.0});
    AlbaMatrix<double> invertedMatrix(matrix);

    invertedMatrix.invert();

    AlbaMatrix<double> product(invertedMatrix * matrix);
    transformToReducedEchelonFormUsingGaussJordanReduction(product);
    EXPECT_TRUE(isIdentityMatrix(product));
}

TEST(GaussJordanReductionTest, MultiplyValueInRowAndPutProductInAnotherRowWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    multiplyValueInRowAndPutProductInAnotherRow(matrix, 2, 0, 0);
    multiplyValueInRowAndPutProductInAnotherRow(matrix, 3, 1, 1);
    multiplyValueInRowAndPutProductInAnotherRow(matrix, 4, 2, 2);

    AlbaMatrix<int> expectedMatrix(2, 3, {2, 4, 9, 12, 20, 24});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(GaussJordanReductionTest, SubtractRowsWithMultiplierPutDifferenceInAnotherRowWorks) {
    AlbaMatrix<double> matrix(2, 3, {1.0, 2.0, 3.0, 4.0, 5.0, 6.0});

    subtractRowsWithMultiplierPutDifferenceInAnotherRow(matrix, 3.0, 1, 0, 1);
    subtractRowsWithMultiplierPutDifferenceInAnotherRow(matrix, 5.0, 2, 0, 2);

    AlbaMatrix<double> expectedMatrix(2, 3, {1.0, 2.0, 0.0, -2.0, 0.0, -4.0});
    EXPECT_EQ(expectedMatrix, matrix);
}

}  // namespace alba::matrix
