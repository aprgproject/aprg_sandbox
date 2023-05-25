#include <Common/Math/Matrix/AlbaSparseMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::matrix {

TEST(AlbaSparseMatrixTest, MatrixConstructor_AlbaSparseMatrixCanBeCreatedByDefaultConstructor) {
    AlbaSparseMatrix<int> matrix;

    EXPECT_EQ(0U, matrix.getNumberOfColumns());
    EXPECT_EQ(0U, matrix.getNumberOfRows());
    AlbaSparseMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_TRUE(matrixData.empty());
}

TEST(AlbaSparseMatrixTest, MatrixConstructor_AlbaSparseMatrixCanBeCreatedWithSize) {
    AlbaSparseMatrix<int> matrix(2, 3);

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaSparseMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_TRUE(matrixData.empty());
}

TEST(AlbaSparseMatrixTest, MatrixConstructor_AlbaSparseMatrixCanBeCreatedWithMatrixDataWithSameSize) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaSparseMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData.at(0));
    EXPECT_EQ(2, matrixData.at(1));
    EXPECT_EQ(3, matrixData.at(2));
    EXPECT_EQ(4, matrixData.at(3));
    EXPECT_EQ(5, matrixData.at(4));
    EXPECT_EQ(6, matrixData.at(5));
}

TEST(AlbaSparseMatrixTest, MatrixConstructor_AlbaSparseMatrixCanBeCreatedWithMatrixDataWithLesserSize) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaSparseMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(5U, matrixData.size());
    EXPECT_EQ(1, matrixData.at(0));
    EXPECT_EQ(2, matrixData.at(1));
    EXPECT_EQ(3, matrixData.at(2));
    EXPECT_EQ(4, matrixData.at(3));
    EXPECT_EQ(5, matrixData.at(4));
}

TEST(AlbaSparseMatrixTest, MatrixConstructor_AlbaSparseMatrixCanBeCreatedWithMatrixDataWithGreaterSize) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6, 7});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaSparseMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData.at(0));
    EXPECT_EQ(2, matrixData.at(1));
    EXPECT_EQ(3, matrixData.at(2));
    EXPECT_EQ(4, matrixData.at(3));
    EXPECT_EQ(5, matrixData.at(4));
    EXPECT_EQ(6, matrixData.at(5));
}

TEST(AlbaSparseMatrixTest, MatrixCanBeCopyConstructed) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaSparseMatrix<int> copyConstructedMatrix;

    copyConstructedMatrix = matrix;

    AlbaSparseMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, copyConstructedMatrix);
}

TEST(AlbaSparseMatrixTest, MatrixCanBeCopyAssigned) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaSparseMatrix<int> copyAssignedMatrix;

    copyAssignedMatrix = matrix;

    AlbaSparseMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, copyAssignedMatrix);
}

TEST(AlbaSparseMatrixTest, OperatorEqualWorks) {
    AlbaSparseMatrix<int> matrix1(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaSparseMatrix<int> matrix2(2, 3);
    AlbaSparseMatrix<int> matrix3(3, 3);
    AlbaSparseMatrix<int> matrix4(2, 4);
    AlbaSparseMatrix<int> matrix5(2, 3);
    matrix2 = matrix1;
    matrix5.setEntry(1, 1, 2);
    EXPECT_TRUE(matrix1 == matrix1);
    EXPECT_TRUE(matrix1 == matrix2);
    EXPECT_FALSE(matrix1 == matrix3);    EXPECT_FALSE(matrix1 == matrix4);
    EXPECT_FALSE(matrix1 == matrix5);
}

TEST(AlbaSparseMatrixTest, OperatorPlusWorks) {
    AlbaSparseMatrix<int> matrix1(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaSparseMatrix<int> matrixToVerify(matrix1 + matrix1);

    AlbaSparseMatrix<int> expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaSparseMatrixTest, OperatorMinusWorks) {
    AlbaSparseMatrix<int> matrix1(2, 3, {100, 200, 300, 400, 500, 600});
    AlbaSparseMatrix<int> matrix2(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaSparseMatrix<int> matrixToVerify(matrix1 - matrix2);

    AlbaSparseMatrix<int> expectedMatrix(2, 3, {99, 198, 297, 396, 495, 594});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaSparseMatrixTest, OperatorMultiplyWorks_MatrixCanBeMultipliedWithConstantValue) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaSparseMatrix<int> matrixToVerify(matrix * 2);

    AlbaSparseMatrix<int> expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}
TEST(AlbaSparseMatrixTest, OperatorMultiplyWorks_MatrixCanBeMultipliedWithAnotherMatrix) {
    AlbaSparseMatrix<int> matrix1(3, 2, {1, 2, -1, 3, 1, 4});
    AlbaSparseMatrix<int> matrix2(2, 3, {-2, 5, 4, -3, 2, 1});
    AlbaSparseMatrix<int> matrixToVerify(matrix1 * matrix2);

    AlbaSparseMatrix<int> expectedMatrix(2, 2, {4, -2, 6, 16});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaSparseMatrixTest, OperatorMultiplyWorksWithExample1) {
    AlbaSparseMatrix<int> matrix1(2, 2, {2, 3, 4, 5});
    AlbaSparseMatrix<int> matrix2(2, 2, {1, 2, 7, 0});

    AlbaSparseMatrix<int> matrixToVerify(matrix1 * matrix2);

    AlbaSparseMatrix<int> expectedMatrix(2, 2, {23, 4, 39, 8});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaSparseMatrixTest, GetColumnsWorks) {
    AlbaSparseMatrix<int> matrix(14, 6);

    EXPECT_EQ(14U, matrix.getNumberOfColumns());
}

TEST(AlbaSparseMatrixTest, GetRowsWorks) {
    AlbaSparseMatrix<int> matrix(14, 6);

    EXPECT_EQ(6U, matrix.getNumberOfRows());
}

TEST(AlbaSparseMatrixTest, GetMatrixIndexWorks) {
    AlbaSparseMatrix<int> matrix(14, 6);

    EXPECT_EQ(45U, matrix.getMatrixIndex(3, 3));
    EXPECT_EQ(73U, matrix.getMatrixIndex(3, 5));    EXPECT_EQ(47U, matrix.getMatrixIndex(5, 3));
    EXPECT_EQ(75U, matrix.getMatrixIndex(5, 5));
}

TEST(AlbaSparseMatrixTest, GetEntryWorks_ValueCanBeFetchedFromEmptyVector) {
    AlbaSparseMatrix<int> matrix(2, 3);

    EXPECT_EQ(0, matrix.getEntry(0, 0));
    EXPECT_EQ(0, matrix.getEntry(1, 0));
    EXPECT_EQ(0, matrix.getEntry(0, 1));
    EXPECT_EQ(0, matrix.getEntry(1, 1));
    EXPECT_EQ(0, matrix.getEntry(0, 2));
    EXPECT_EQ(0, matrix.getEntry(1, 2));
}

TEST(AlbaSparseMatrixTest, GetEntryWorks_ValueCanBeFetchedFromNonEmptyVector) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ(1, matrix.getEntry(0, 0));
    EXPECT_EQ(2, matrix.getEntry(1, 0));
    EXPECT_EQ(3, matrix.getEntry(0, 1));
    EXPECT_EQ(4, matrix.getEntry(1, 1));
    EXPECT_EQ(5, matrix.getEntry(0, 2));
    EXPECT_EQ(6, matrix.getEntry(1, 2));
}

TEST(AlbaSparseMatrixTest, GetMatrixDataWorks) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaSparseMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());

    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData.at(0));
    EXPECT_EQ(2, matrixData.at(1));
    EXPECT_EQ(3, matrixData.at(2));
    EXPECT_EQ(4, matrixData.at(3));
    EXPECT_EQ(5, matrixData.at(4));
    EXPECT_EQ(6, matrixData.at(5));
}

TEST(AlbaSparseMatrixTest, GetStringWorks) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ("Matrix output:\n-----\n|1|2|\n-----\n|3|4|\n-----\n|5|6|\n-----\n", convertToString(matrix));
}

TEST(AlbaSparseMatrixTest, SetEntryWorks_ValueCanSavedInTheMatrix) {
    AlbaSparseMatrix<int> matrix(2, 3);

    matrix.setEntry(0, 0, 1);
    matrix.setEntry(1, 0, 2);    matrix.setEntry(0, 1, 3);
    matrix.setEntry(1, 1, 4);
    matrix.setEntry(0, 2, 5);
    matrix.setEntry(1, 2, 6);

    AlbaSparseMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaSparseMatrixTest, SetEntriesWorks_MultipleValuesCanSavedInTheMatrix) {
    AlbaSparseMatrix<int> matrix(2, 3);

    matrix.setEntries({1, 2, 3, 4, 5, 6});

    AlbaSparseMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaSparseMatrixTest, SetEntriesWorks_OverwritesExistingValuesAndDoesNotChangeOtherValues) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.setEntries({9, 8, 7});

    AlbaSparseMatrix<int> expectedMatrix(2, 3, {9, 8, 7, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaSparseMatrixTest, ClearAndResizeWorks) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.clearAndResize(3, 2);

    AlbaSparseMatrix<int> expectedMatrix(3, 2, {0, 0, 0, 0, 0, 0});
    EXPECT_EQ(expectedMatrix, matrix);
}
TEST(AlbaSparseMatrixTest, NegateWorks) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});
    matrix.negate();

    AlbaSparseMatrix<int> expectedMatrix(2, 3, {-1, -2, -3, -4, -5, -6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaSparseMatrixTest, TransposeWorks) {
    AlbaSparseMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.transpose();

    AlbaSparseMatrix<int> expectedMatrix(3, 2, {1, 3, 5, 2, 4, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}
}  // namespace alba::matrix