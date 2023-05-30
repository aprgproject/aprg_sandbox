#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Common/String/AlbaStringHelper.hpp>
#include <CommonTests/Math/Matrix/AlbaMatrixInternalFunctions.hpp>

#include <gtest/gtest.h>

using namespace alba::stringHelper;
using namespace std;

namespace alba::matrix {

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedByDefaultConstructor) {
    AlbaMatrix<int> matrix;

    EXPECT_EQ(0U, matrix.getNumberOfColumns());
    EXPECT_EQ(0U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_TRUE(matrixData.empty());
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithSize) {
    AlbaMatrix<int> matrix(2, 3);

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(0, matrixData.at(0));
    EXPECT_EQ(0, matrixData.at(1));
    EXPECT_EQ(0, matrixData.at(2));
    EXPECT_EQ(0, matrixData.at(3));
    EXPECT_EQ(0, matrixData.at(4));
    EXPECT_EQ(0, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithUniquePointers) {
    AlbaMatrix<unique_ptr<int>> matrix(2, 3);

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<unique_ptr<int>>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_FALSE(matrixData.at(0));
    EXPECT_FALSE(matrixData.at(1));
    EXPECT_FALSE(matrixData.at(2));
    EXPECT_FALSE(matrixData.at(3));
    EXPECT_FALSE(matrixData.at(4));
    EXPECT_FALSE(matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithSizeAndInitialValue) {
    AlbaMatrix<int> matrix(2, 3, 55);

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(55, matrixData.at(0));
    EXPECT_EQ(55, matrixData.at(1));
    EXPECT_EQ(55, matrixData.at(2));
    EXPECT_EQ(55, matrixData.at(3));
    EXPECT_EQ(55, matrixData.at(4));
    EXPECT_EQ(55, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithMatrixDataWithSameSize) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData.at(0));
    EXPECT_EQ(2, matrixData.at(1));
    EXPECT_EQ(3, matrixData.at(2));
    EXPECT_EQ(4, matrixData.at(3));
    EXPECT_EQ(5, matrixData.at(4));
    EXPECT_EQ(6, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithMatrixDataWithLesserSize) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData.at(0));
    EXPECT_EQ(2, matrixData.at(1));
    EXPECT_EQ(3, matrixData.at(2));
    EXPECT_EQ(4, matrixData.at(3));
    EXPECT_EQ(5, matrixData.at(4));
    EXPECT_EQ(0, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithMatrixDataWithGreaterSize) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6, 7});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData.at(0));
    EXPECT_EQ(2, matrixData.at(1));
    EXPECT_EQ(3, matrixData.at(2));
    EXPECT_EQ(4, matrixData.at(3));
    EXPECT_EQ(5, matrixData.at(4));
    EXPECT_EQ(6, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixCanBeCopyConstructed) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> copyConstructedMatrix;

    copyConstructedMatrix = matrix;

    AlbaMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, copyConstructedMatrix);
}

TEST(AlbaMatrixTest, MatrixCanBeCopyAssigned) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> copyAssignedMatrix;

    copyAssignedMatrix = matrix;

    AlbaMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, copyAssignedMatrix);
}

TEST(AlbaMatrixTest, OperatorEqualWorks) {
    AlbaMatrix<int> matrix1(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(2, 3);
    AlbaMatrix<int> matrix3(3, 3);
    AlbaMatrix<int> matrix4(2, 4);
    AlbaMatrix<int> matrix5(2, 3);
    matrix2 = matrix1;
    matrix5.setEntry(1, 1, 2);

    EXPECT_TRUE(matrix1 == matrix1);
    EXPECT_TRUE(matrix1 == matrix2);
    EXPECT_FALSE(matrix1 == matrix3);
    EXPECT_FALSE(matrix1 == matrix4);
    EXPECT_FALSE(matrix1 == matrix5);
}

TEST(AlbaMatrixTest, OperatorPlusWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> matrixToVerify(matrix + matrix);

    AlbaMatrix<int> expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMinusWorks) {
    AlbaMatrix<int> matrix1(2, 3, {100, 200, 300, 400, 500, 600});
    AlbaMatrix<int> matrix2(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> matrixToVerify(matrix1 - matrix2);

    AlbaMatrix<int> expectedMatrix(2, 3, {99, 198, 297, 396, 495, 594});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMultiplyWorks_WithMatrixAndConstant) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> matrixToVerify(matrix * 2);

    AlbaMatrix<int> expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMultiplyWorks_WithMatrixAndMatrix) {
    AlbaMatrix<int> matrix1(3, 2, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

    AlbaMatrix<int> matrixToVerify(matrix1 * matrix2);

    AlbaMatrix<int> expectedMatrix(4, 2, {38, 44, 50, 56, 83, 98, 113, 128});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorPlusAssignmentWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix += matrix;

    AlbaMatrix<int> expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, OperatorMinusAssignmentWorks) {
    AlbaMatrix<int> matrix1(2, 3, {100, 200, 300, 400, 500, 600});
    AlbaMatrix<int> matrix2(2, 3, {1, 2, 3, 4, 5, 6});

    matrix1 -= matrix2;

    AlbaMatrix<int> expectedMatrix(2, 3, {99, 198, 297, 396, 495, 594});
    EXPECT_EQ(expectedMatrix, matrix1);
}

TEST(AlbaMatrixTest, OperatorMultiplyAssignmentWorks_WithMatrixAndConstant) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix *= 2;

    AlbaMatrix<int> expectedMatrix(2, 3, {2, 4, 6, 8, 10, 12});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, OperatorMultiplyAssignmentWorks_WithMatrixAndMatrix) {
    AlbaMatrix<int> matrix1(3, 2, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

    matrix1 *= matrix2;

    AlbaMatrix<int> expectedMatrix(4, 2, {38, 44, 50, 56, 83, 98, 113, 128});
    EXPECT_EQ(expectedMatrix, matrix1);
}

TEST(AlbaMatrixTest, IsEmptyWorks) {
    AlbaMatrix<int> emptyMatrix;
    AlbaMatrix<int> nonEmptyMatrix(14, 6);

    EXPECT_TRUE(emptyMatrix.isEmpty());
    EXPECT_FALSE(nonEmptyMatrix.isEmpty());
}

TEST(AlbaMatrixTest, IsInsideTheMatrixWorks) {
    AlbaMatrix<int> matrix(14, 6);

    EXPECT_FALSE(matrix.isInside(14, 6));
    EXPECT_FALSE(matrix.isInside(14, 5));
    EXPECT_FALSE(matrix.isInside(13, 6));
    EXPECT_TRUE(matrix.isInside(13, 5));
}

TEST(AlbaMatrixTest, GetColumnsWorks) {
    AlbaMatrix<int> matrix(14, 6);

    EXPECT_EQ(14U, matrix.getNumberOfColumns());
}

TEST(AlbaMatrixTest, GetRowsWorks) {
    AlbaMatrix<int> matrix(14, 6);

    EXPECT_EQ(6U, matrix.getNumberOfRows());
}

TEST(AlbaMatrixTest, GetNumberOfCellsWorks) {
    AlbaMatrix<int> matrix(14, 6);

    EXPECT_EQ(84U, matrix.getNumberOfCells());
}

TEST(AlbaMatrixTest, GetMatrixIndexWorks) {
    AlbaMatrix<int> matrix(14, 6);

    EXPECT_EQ(45U, matrix.getMatrixIndex(3, 3));
    EXPECT_EQ(73U, matrix.getMatrixIndex(3, 5));
    EXPECT_EQ(47U, matrix.getMatrixIndex(5, 3));
    EXPECT_EQ(75U, matrix.getMatrixIndex(5, 5));
}

TEST(AlbaMatrixTest, GetEntryWorks_ValueCanBeFetchedFromEmptyVector) {
    AlbaMatrix<int> matrix(2, 3);

    EXPECT_EQ(0, matrix.getEntry(0, 0));
    EXPECT_EQ(0, matrix.getEntry(1, 0));
    EXPECT_EQ(0, matrix.getEntry(0, 1));
    EXPECT_EQ(0, matrix.getEntry(1, 1));
    EXPECT_EQ(0, matrix.getEntry(0, 2));
    EXPECT_EQ(0, matrix.getEntry(1, 2));
}

TEST(AlbaMatrixTest, GetEntryWorks_ValueCanBeFetchedFromNonEmptyVector) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ(1, matrix.getEntry(0, 0));
    EXPECT_EQ(2, matrix.getEntry(1, 0));
    EXPECT_EQ(3, matrix.getEntry(0, 1));
    EXPECT_EQ(4, matrix.getEntry(1, 1));
    EXPECT_EQ(5, matrix.getEntry(0, 2));
    EXPECT_EQ(6, matrix.getEntry(1, 2));
}

TEST(AlbaMatrixTest, GetMatrixDataWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::MatrixData const& matrixData(matrix.getMatrixData());

    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1, matrixData.at(0));
    EXPECT_EQ(2, matrixData.at(1));
    EXPECT_EQ(3, matrixData.at(2));
    EXPECT_EQ(4, matrixData.at(3));
    EXPECT_EQ(5, matrixData.at(4));
    EXPECT_EQ(6, matrixData.at(5));
}

TEST(AlbaMatrixTest, RetrieveColumnWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::MatrixData secondColumn;
    matrix.retrieveColumn(secondColumn, 1);

    ASSERT_EQ(3U, secondColumn.size());
    EXPECT_EQ(2, secondColumn.at(0));
    EXPECT_EQ(4, secondColumn.at(1));
    EXPECT_EQ(6, secondColumn.at(2));
}

TEST(AlbaMatrixTest, RetrieveRowWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::MatrixData secondRow;
    matrix.retrieveRow(secondRow, 1);

    ASSERT_EQ(2U, secondRow.size());
    EXPECT_EQ(3, secondRow.at(0));
    EXPECT_EQ(4, secondRow.at(1));
}

TEST(AlbaMatrixTest, RetrieveColumnsWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::ListOfMatrixData columns;
    matrix.retrieveColumns(columns);

    ASSERT_EQ(2U, columns.size());
    ASSERT_EQ(3U, columns.at(0).size());
    EXPECT_EQ(1, columns.at(0).at(0));
    EXPECT_EQ(3, columns.at(0).at(1));
    EXPECT_EQ(5, columns.at(0).at(2));
    ASSERT_EQ(3U, columns.at(1).size());
    EXPECT_EQ(2, columns.at(1).at(0));
    EXPECT_EQ(4, columns.at(1).at(1));
    EXPECT_EQ(6, columns.at(1).at(2));
}

TEST(AlbaMatrixTest, RetrieveRowsWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int>::ListOfMatrixData rows;
    matrix.retrieveRows(rows);

    ASSERT_EQ(3U, rows.size());
    ASSERT_EQ(2U, rows.at(0).size());
    EXPECT_EQ(1, rows.at(0).at(0));
    EXPECT_EQ(2, rows.at(0).at(1));
    ASSERT_EQ(2U, rows.at(1).size());
    EXPECT_EQ(3, rows.at(1).at(0));
    EXPECT_EQ(4, rows.at(1).at(1));
    ASSERT_EQ(2U, rows.at(2).size());
    EXPECT_EQ(5, rows.at(2).at(0));
    EXPECT_EQ(6, rows.at(2).at(1));
}

TEST(AlbaMatrixTest, RetrieveXAndYFromIndexWorks) {
    AlbaMatrix<int> matrix(14, 6);

    size_t x, y;
    matrix.retrieveXAndYFromIndex(x, y, 43);

    EXPECT_EQ(1U, x);
    EXPECT_EQ(3U, y);
}

TEST(AlbaMatrixTest, SetEntryWorks_ValueCanSavedInTheMatrix) {
    AlbaMatrix<int> matrix(2, 3);

    matrix.setEntry(0, 0, 1);
    matrix.setEntry(1, 0, 2);
    matrix.setEntry(0, 1, 3);
    matrix.setEntry(1, 1, 4);
    matrix.setEntry(0, 2, 5);
    matrix.setEntry(1, 2, 6);

    AlbaMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetEntriesWorks_MultipleValuesCanSavedInTheMatrix) {
    AlbaMatrix<int> matrix(2, 3);

    matrix.setEntries({1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetEntriesWorks_OverwritesExistingValuesAndDoesNotChangeOtherValues) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.setEntries({9, 8, 7});

    AlbaMatrix<int> expectedMatrix(2, 3, {9, 8, 7, 4, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetColumnWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.setColumn(1, {9, 8, 7});

    AlbaMatrix<int> expectedMatrix(2, 3, {1, 9, 3, 8, 5, 7});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetRowWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.setRow(1, {9, 8});

    AlbaMatrix<int> expectedMatrix(2, 3, {1, 2, 9, 8, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, ClearAndResizeWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.clearAndResize(3, 2);

    AlbaMatrix<int> expectedMatrix(3, 2, {0, 0, 0, 0, 0, 0});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, ClearAndResizeWorksWithInitialValue) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.clearAndResize(3, 2, 55);

    AlbaMatrix<int> expectedMatrix(3, 2, {55, 55, 55, 55, 55, 55});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, NegateWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.negate();

    AlbaMatrix<int> expectedMatrix(2, 3, {-1, -2, -3, -4, -5, -6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, TransposeWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    matrix.transpose();

    AlbaMatrix<int> expectedMatrix(3, 2, {1, 3, 5, 2, 4, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, InvertWorks) {
    AlbaMatrix<double> matrix(3, 3, {1.0, 1.0, 1.0, 0.0, 2.0, 3.0, 5.0, 5.0, 1.0});

    matrix.invert();

    AlbaMatrix<double> expectedMatrix(3, 3, {1.625, -0.5, -0.125, -1.875, 0.5, 0.375, 1.25, 0.0, -0.25});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, IterateAllThroughYAndThenXWorks) {
    AlbaMatrix<int> matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

    using PairOfNumbers = pair<int, int>;
    vector<PairOfNumbers> xyPairsToVerify;
    matrix.iterateAllThroughYAndThenX([&](int const x, int const y) { xyPairsToVerify.emplace_back(x, y); });

    ASSERT_EQ(9U, xyPairsToVerify.size());
    EXPECT_EQ(PairOfNumbers(0, 0), xyPairsToVerify.at(0));
    EXPECT_EQ(PairOfNumbers(1, 0), xyPairsToVerify.at(1));
    EXPECT_EQ(PairOfNumbers(2, 0), xyPairsToVerify.at(2));
    EXPECT_EQ(PairOfNumbers(0, 1), xyPairsToVerify.at(3));
    EXPECT_EQ(PairOfNumbers(1, 1), xyPairsToVerify.at(4));
    EXPECT_EQ(PairOfNumbers(2, 1), xyPairsToVerify.at(5));
    EXPECT_EQ(PairOfNumbers(0, 2), xyPairsToVerify.at(6));
    EXPECT_EQ(PairOfNumbers(1, 2), xyPairsToVerify.at(7));
    EXPECT_EQ(PairOfNumbers(2, 2), xyPairsToVerify.at(8));
}

TEST(AlbaMatrixTest, IterateThroughYAndThenXWithRangesWorks) {
    AlbaMatrix<int> matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    AlbaMatrix<int>::MatrixIndexRange xRange(0, 1, 1);
    AlbaMatrix<int>::MatrixIndexRange yRange(1, 2, 1);

    using PairOfNumbers = pair<int, int>;
    vector<PairOfNumbers> xyPairsToVerify;
    matrix.iterateThroughYAndThenXWithRanges(
        yRange, xRange, [&](int const x, int const y) { xyPairsToVerify.emplace_back(x, y); });

    ASSERT_EQ(4U, xyPairsToVerify.size());
    EXPECT_EQ(PairOfNumbers(0, 1), xyPairsToVerify.at(0));
    EXPECT_EQ(PairOfNumbers(1, 1), xyPairsToVerify.at(1));
    EXPECT_EQ(PairOfNumbers(0, 2), xyPairsToVerify.at(2));
    EXPECT_EQ(PairOfNumbers(1, 2), xyPairsToVerify.at(3));
}

TEST(AlbaMatrixTest, IterateThroughXAndThenYWithRangesWorks) {
    AlbaMatrix<int> matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    AlbaMatrix<int>::MatrixIndexRange xRange(0, 1, 1);
    AlbaMatrix<int>::MatrixIndexRange yRange(1, 2, 1);

    using PairOfNumbers = pair<int, int>;
    vector<PairOfNumbers> xyPairsToVerify;
    matrix.iterateThroughXAndThenYWithRanges(
        xRange, yRange, [&](int const x, int const y) { xyPairsToVerify.emplace_back(x, y); });

    ASSERT_EQ(4U, xyPairsToVerify.size());
    EXPECT_EQ(PairOfNumbers(0, 1), xyPairsToVerify.at(0));
    EXPECT_EQ(PairOfNumbers(0, 2), xyPairsToVerify.at(1));
    EXPECT_EQ(PairOfNumbers(1, 1), xyPairsToVerify.at(2));
    EXPECT_EQ(PairOfNumbers(1, 2), xyPairsToVerify.at(3));
}

TEST(AlbaMatrixTest, OutputStreamOperatorWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    EXPECT_EQ("Matrix output:\n-----\n|1|2|\n-----\n|3|4|\n-----\n|5|6|\n-----\n", convertToString(matrix));
}

}  // namespace alba::matrix
