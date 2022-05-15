#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <CommonTests/Math/Matrix/AlbaMatrixInternalFunctions.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace matrix
{

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedByDefaultConstructor)
{
    AlbaMatrix<unsigned int> matrix;

    EXPECT_EQ(0U, matrix.getNumberOfColumns());
    EXPECT_EQ(0U, matrix.getNumberOfRows());
    AlbaMatrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_TRUE(matrixData.empty());
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithSize){
    AlbaMatrix<unsigned int> matrix(2, 3);

    EXPECT_EQ(2U, matrix.getNumberOfColumns());    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(0U, matrixData.at(0));
    EXPECT_EQ(0U, matrixData.at(1));
    EXPECT_EQ(0U, matrixData.at(2));
    EXPECT_EQ(0U, matrixData.at(3));
    EXPECT_EQ(0U, matrixData.at(4));
    EXPECT_EQ(0U, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithMatrixDataWithSameSize)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1U, matrixData.at(0));
    EXPECT_EQ(2U, matrixData.at(1));
    EXPECT_EQ(3U, matrixData.at(2));
    EXPECT_EQ(4U, matrixData.at(3));
    EXPECT_EQ(5U, matrixData.at(4));
    EXPECT_EQ(6U, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithMatrixDataWithLesserSize)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1U, matrixData.at(0));
    EXPECT_EQ(2U, matrixData.at(1));
    EXPECT_EQ(3U, matrixData.at(2));
    EXPECT_EQ(4U, matrixData.at(3));
    EXPECT_EQ(5U, matrixData.at(4));
    EXPECT_EQ(0U, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithMatrixDataWithGreaterSize)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6, 7});

    EXPECT_EQ(2U, matrix.getNumberOfColumns());
    EXPECT_EQ(3U, matrix.getNumberOfRows());
    AlbaMatrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1U, matrixData.at(0));
    EXPECT_EQ(2U, matrixData.at(1));
    EXPECT_EQ(3U, matrixData.at(2));
    EXPECT_EQ(4U, matrixData.at(3));
    EXPECT_EQ(5U, matrixData.at(4));
    EXPECT_EQ(6U, matrixData.at(5));
}

TEST(AlbaMatrixTest, MatrixCanBeCopyConstructed)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});
    AlbaMatrix<unsigned int> copyConstructedMatrix;

    copyConstructedMatrix = matrix;

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});
    EXPECT_EQ(expectedMatrix, copyConstructedMatrix);
}

TEST(AlbaMatrixTest, MatrixCanBeCopyAssigned)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});
    AlbaMatrix<unsigned int> copyAssignedMatrix;

    copyAssignedMatrix = matrix;

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});
    EXPECT_EQ(expectedMatrix, copyAssignedMatrix);
}

TEST(AlbaMatrixTest, OperatorEqualWorks)
{
    AlbaMatrix<unsigned int> matrix1(2,3,
    {1,2,
     3,4,
     5,6});
    AlbaMatrix<unsigned int> matrix2(2,3);
    AlbaMatrix<unsigned int> matrix3(3,3);
    AlbaMatrix<unsigned int> matrix4(2,4);
    AlbaMatrix<unsigned int> matrix5(2,3);
    matrix2 = matrix1;
    matrix5.setEntry(1, 1, 2);

    EXPECT_TRUE(matrix1==matrix1);
    EXPECT_TRUE(matrix1==matrix2);
    EXPECT_FALSE(matrix1==matrix3);
    EXPECT_FALSE(matrix1==matrix4);
    EXPECT_FALSE(matrix1==matrix5);
}

TEST(AlbaMatrixTest, OperatorPlusWorks)
{
    AlbaMatrix<unsigned int> matrix1(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int> matrixToVerify(matrix1+matrix1);

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    { 2,  4,
      6,  8,
     10, 12});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMinusWorks)
{
    AlbaMatrix<unsigned int> matrix1(2, 3,
    {100, 200,
     300, 400,
     500, 600});
    AlbaMatrix<unsigned int> matrix2(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int> matrixToVerify(matrix1-matrix2);

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    { 99, 198,
     297, 396,
     495, 594});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMultiplyWorks_MatrixCanBeMultipliedWithConstantValue)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int> matrixToVerify(matrix*2);

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    { 2,  4,
      6,  8,
     10, 12});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMultiplyWorks_MatrixCanBeMultipliedWithAnotherMatrix)
{
    AlbaMatrix<int> matrix1(3, 2,
    {1, 2, -1,
     3, 1,  4});
    AlbaMatrix<int> matrix2(2, 3,
    {-2, 5,
      4,-3,
      2, 1});

    AlbaMatrix<int> matrixToVerify(matrix1*matrix2);

    AlbaMatrix<int> expectedMatrix(2, 2,
    { 4, -2,
      6, 16});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, OperatorMultiplyWorksWithExample1)
{
    AlbaMatrix<unsigned int> matrix1(2, 2,
    {2, 3,
     4, 5});
    AlbaMatrix<unsigned int> matrix2(2, 2,
    {1, 2,
     7, 0});

    AlbaMatrix<unsigned int> matrixToVerify(matrix1*matrix2);

    AlbaMatrix<unsigned int> expectedMatrix(2, 2,
    {23,  4,
     39,  8});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixTest, GetColumnsWorks)
{
    AlbaMatrix<unsigned int> matrix(14, 6);

    EXPECT_EQ(14U, matrix.getNumberOfColumns());
}

TEST(AlbaMatrixTest, GetRowsWorks)
{
    AlbaMatrix<unsigned int> matrix(14, 6);

    EXPECT_EQ(6U, matrix.getNumberOfRows());
}

TEST(AlbaMatrixTest, GetMatrixIndexWorks)
{
    AlbaMatrix<unsigned int> matrix(14, 6);

    EXPECT_EQ(45U, matrix.getMatrixIndex(3, 3));
    EXPECT_EQ(73U, matrix.getMatrixIndex(3, 5));
    EXPECT_EQ(47U, matrix.getMatrixIndex(5, 3));
    EXPECT_EQ(75U, matrix.getMatrixIndex(5, 5));
}

TEST(AlbaMatrixTest, GetEntryWorks_ValueCanBeFetchedFromEmptyVector)
{
    AlbaMatrix<unsigned int> matrix(2, 3);

    EXPECT_EQ(0U, matrix.getEntry(0, 0));
    EXPECT_EQ(0U, matrix.getEntry(1, 0));
    EXPECT_EQ(0U, matrix.getEntry(0, 1));
    EXPECT_EQ(0U, matrix.getEntry(1, 1));
    EXPECT_EQ(0U, matrix.getEntry(0, 2));
    EXPECT_EQ(0U, matrix.getEntry(1, 2));
}

TEST(AlbaMatrixTest, GetEntryWorks_ValueCanBeFetchedFromNonEmptyVector)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    EXPECT_EQ(1U, matrix.getEntry(0, 0));
    EXPECT_EQ(2U, matrix.getEntry(1, 0));
    EXPECT_EQ(3U, matrix.getEntry(0, 1));
    EXPECT_EQ(4U, matrix.getEntry(1, 1));
    EXPECT_EQ(5U, matrix.getEntry(0, 2));
    EXPECT_EQ(6U, matrix.getEntry(1, 2));
}

TEST(AlbaMatrixTest, GetMatrixDataWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());

    ASSERT_EQ(6U, matrixData.size());
    EXPECT_EQ(1U, matrixData.at(0));
    EXPECT_EQ(2U, matrixData.at(1));
    EXPECT_EQ(3U, matrixData.at(2));
    EXPECT_EQ(4U, matrixData.at(3));
    EXPECT_EQ(5U, matrixData.at(4));
    EXPECT_EQ(6U, matrixData.at(5));
}

TEST(AlbaMatrixTest, GetStringWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    EXPECT_EQ("Matrix output:\n-----\n|1|2|\n-----\n|3|4|\n-----\n|5|6|\n-----\n", matrix.getString());
}

TEST(AlbaMatrixTest, RetrieveColumnWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int>::MatrixData secondColumn;
    matrix.retrieveColumn(secondColumn, 1);

    ASSERT_EQ(3U, secondColumn.size());
    EXPECT_EQ(2U, secondColumn.at(0));
    EXPECT_EQ(4U, secondColumn.at(1));
    EXPECT_EQ(6U, secondColumn.at(2));
}

TEST(AlbaMatrixTest, RetrieveRowWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int>::MatrixData secondRow;
    matrix.retrieveRow(secondRow, 1);

    ASSERT_EQ(2U, secondRow.size());
    EXPECT_EQ(3U, secondRow.at(0));
    EXPECT_EQ(4U, secondRow.at(1));
}

TEST(AlbaMatrixTest, RetrieveColumnsWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int>::ListOfMatrixData columns;
    matrix.retrieveColumns(columns);

    ASSERT_EQ(2U, columns.size());
    ASSERT_EQ(3U, columns.at(0).size());
    EXPECT_EQ(1U, columns.at(0).at(0));
    EXPECT_EQ(3U, columns.at(0).at(1));
    EXPECT_EQ(5U, columns.at(0).at(2));
    ASSERT_EQ(3U, columns.at(1).size());
    EXPECT_EQ(2U, columns.at(1).at(0));
    EXPECT_EQ(4U, columns.at(1).at(1));
    EXPECT_EQ(6U, columns.at(1).at(2));
}

TEST(AlbaMatrixTest, RetrieveRowsWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int>::ListOfMatrixData rows;
    matrix.retrieveRows(rows);

    ASSERT_EQ(3U, rows.size());
    ASSERT_EQ(2U, rows.at(0).size());
    EXPECT_EQ(1U, rows.at(0).at(0));
    EXPECT_EQ(2U, rows.at(0).at(1));
    ASSERT_EQ(2U, rows.at(1).size());
    EXPECT_EQ(3U, rows.at(1).at(0));
    EXPECT_EQ(4U, rows.at(1).at(1));
    ASSERT_EQ(2U, rows.at(2).size());
    EXPECT_EQ(5U, rows.at(2).at(0));
    EXPECT_EQ(6U, rows.at(2).at(1));
}

TEST(AlbaMatrixTest, SetEntryWorks_ValueCanSavedInTheMatrix)
{
    AlbaMatrix<unsigned int> matrix(2, 3);

    matrix.setEntry(0, 0, 1);
    matrix.setEntry(1, 0, 2);
    matrix.setEntry(0, 1, 3);
    matrix.setEntry(1, 1, 4);
    matrix.setEntry(0, 2, 5);
    matrix.setEntry(1, 2, 6);

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetEntriesWorks_MultipleValuesCanSavedInTheMatrix)
{
    AlbaMatrix<unsigned int> matrix(2, 3);

    matrix.setEntries(
    {1, 2,
     3, 4,
     5, 6});

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetEntriesWorks_OverwritesExistingValuesAndDoesNotChangeOtherValues)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    matrix.setEntries(
    {9, 8,
     7});

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {9, 8,
     7, 4,
     5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetColumnWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    matrix.setColumn(1, {9, 8, 7});

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {1, 9,
     3, 8,
     5, 7});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, SetRowWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    matrix.setRow(1, {9, 8});

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {1, 2,
     9, 8,
     5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, ClearAndResizeWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    matrix.clearAndResize(3,2);

    AlbaMatrix<unsigned int> expectedMatrix(3, 2,
    {0, 0, 0,
     0, 0, 0});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, NegateWorks)
{
    AlbaMatrix<int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    matrix.negate();

    AlbaMatrix<int> expectedMatrix(2, 3,
    {-1, -2,
     -3, -4,
     -5, -6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, TransposeWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    matrix.transpose();

    AlbaMatrix<unsigned int> expectedMatrix(3, 2,
    {1, 3, 5,
     2, 4, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, InvertWorks)
{
    AlbaMatrix<double> matrix(3, 3,
    {1.0, 1.0, 1.0,
     0.0, 2.0, 3.0,
     5.0, 5.0, 1.0});

    matrix.invert();

    AlbaMatrix<double> expectedMatrix(3, 3,
    { 1.625, -0.5, -0.125,
     -1.875,  0.5,  0.375,
       1.25,  0.0,  -0.25});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixTest, IterateAllThroughYAndThenXWorks)
{
    AlbaMatrix<unsigned int> matrix(3, 3,
    {1, 2, 3,
     4, 5, 6,
     7, 8, 9});

    using PairOfNumbers=pair<unsigned int, unsigned int>;
    vector<PairOfNumbers> xyPairsToVerify;
    matrix.iterateAllThroughYAndThenX([&](unsigned int const x, unsigned int const y)
    {
        xyPairsToVerify.emplace_back(x, y);
    });

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

TEST(AlbaMatrixTest, IterateThroughYAndThenXWithRangesWorks)
{
    AlbaMatrix<unsigned int> matrix(3, 3,
    {1, 2, 3,
     4, 5, 6,
     7, 8, 9});
    AlbaMatrix<unsigned int>::MatrixIndexRange xRange(0, 1, 1);
    AlbaMatrix<unsigned int>::MatrixIndexRange yRange(1, 2, 1);

    using PairOfNumbers=pair<unsigned int, unsigned int>;
    vector<PairOfNumbers> xyPairsToVerify;
    matrix.iterateThroughYAndThenXWithRanges(yRange, xRange, [&](unsigned int const x, unsigned int const y)
    {
        xyPairsToVerify.emplace_back(x, y);
    });

    ASSERT_EQ(4U, xyPairsToVerify.size());
    EXPECT_EQ(PairOfNumbers(0, 1), xyPairsToVerify.at(0));
    EXPECT_EQ(PairOfNumbers(1, 1), xyPairsToVerify.at(1));
    EXPECT_EQ(PairOfNumbers(0, 2), xyPairsToVerify.at(2));
    EXPECT_EQ(PairOfNumbers(1, 2), xyPairsToVerify.at(3));
}

TEST(AlbaMatrixTest, IterateThroughXAndThenYWithRangesWorks)
{
    AlbaMatrix<unsigned int> matrix(3, 3,
    {1, 2, 3,
     4, 5, 6,
     7, 8, 9});
    AlbaMatrix<unsigned int>::MatrixIndexRange xRange(0, 1, 1);
    AlbaMatrix<unsigned int>::MatrixIndexRange yRange(1, 2, 1);

    using PairOfNumbers=pair<unsigned int, unsigned int>;
    vector<PairOfNumbers> xyPairsToVerify;
    matrix.iterateThroughXAndThenYWithRanges(xRange, yRange, [&](unsigned int const x, unsigned int const y)
    {
        xyPairsToVerify.emplace_back(x, y);
    });

    ASSERT_EQ(4U, xyPairsToVerify.size());
    EXPECT_EQ(PairOfNumbers(0, 1), xyPairsToVerify.at(0));
    EXPECT_EQ(PairOfNumbers(0, 2), xyPairsToVerify.at(1));
    EXPECT_EQ(PairOfNumbers(1, 1), xyPairsToVerify.at(2));
    EXPECT_EQ(PairOfNumbers(1, 2), xyPairsToVerify.at(3));
}

}

}
