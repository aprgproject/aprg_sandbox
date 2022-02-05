#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedByDefaultConstructor)
{
    AlbaMatrix<unsigned int> matrix;

    EXPECT_EQ(0U, matrix.getColumns());
    EXPECT_EQ(0U, matrix.getRows());
    AlbaMatrix<unsigned int>::MatrixData const& matrixData(
                matrix.getMatrixData());
    ASSERT_EQ(0U, matrixData.size());
}

TEST(AlbaMatrixTest, MatrixConstructor_AlbaMatrixCanBeCreatedWithSize)
{
    AlbaMatrix<unsigned int> matrix(2,3);

    EXPECT_EQ(2U, matrix.getColumns());
    EXPECT_EQ(3U, matrix.getRows());
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
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

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
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5});

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
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6,7});

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
    AlbaMatrix<unsigned int> matrix1(2,3,
    {1,2,
     3,4,
     5,6});

    AlbaMatrix<unsigned int> resultMatrix(matrix1+matrix1);

    EXPECT_EQ(2U, resultMatrix.getEntry(0,0));
    EXPECT_EQ(4U, resultMatrix.getEntry(1,0));
    EXPECT_EQ(6U, resultMatrix.getEntry(0,1));
    EXPECT_EQ(8U, resultMatrix.getEntry(1,1));
    EXPECT_EQ(10U, resultMatrix.getEntry(0,2));
    EXPECT_EQ(12U, resultMatrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, OperatorMinusWorks)
{
    AlbaMatrix<unsigned int> matrix1(2,3,
    {100,200,
     300,400,
     500,600});
    AlbaMatrix<unsigned int> matrix2(2,3,
    {1,2,
     3,4,
     5,6});

    AlbaMatrix<unsigned int> resultMatrix(matrix1-matrix2);

    EXPECT_EQ(99U, resultMatrix.getEntry(0,0));
    EXPECT_EQ(198U, resultMatrix.getEntry(1,0));
    EXPECT_EQ(297U, resultMatrix.getEntry(0,1));
    EXPECT_EQ(396U, resultMatrix.getEntry(1,1));
    EXPECT_EQ(495U, resultMatrix.getEntry(0,2));
    EXPECT_EQ(594U, resultMatrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, OperatorMultiplyWorks_MatrixCanBeMultipliedWithConstantValue)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    AlbaMatrix<unsigned int> resultMatrix(matrix*2);

    EXPECT_EQ(2U, resultMatrix.getEntry(0,0));
    EXPECT_EQ(4U, resultMatrix.getEntry(1,0));
    EXPECT_EQ(6U, resultMatrix.getEntry(0,1));
    EXPECT_EQ(8U, resultMatrix.getEntry(1,1));
    EXPECT_EQ(10U, resultMatrix.getEntry(0,2));
    EXPECT_EQ(12U, resultMatrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, OperatorMultiplyWorks_MatrixCanBeMultipliedWithAnotherMatrix)
{
    AlbaMatrix<int> matrix1(3,2,
    {1,2,-1,
     3,1,4});
    AlbaMatrix<int> matrix2(2,3,
    {-2,5,
     4,-3,
     2,1});

    AlbaMatrix<int> resultMatrix(matrix1*matrix2);

    EXPECT_EQ(2U, resultMatrix.getColumns());
    EXPECT_EQ(2U, resultMatrix.getRows());
    EXPECT_EQ(4, resultMatrix.getEntry(0,0));
    EXPECT_EQ(-2, resultMatrix.getEntry(1,0));
    EXPECT_EQ(6, resultMatrix.getEntry(0,1));
    EXPECT_EQ(16, resultMatrix.getEntry(1,1));
}

TEST(AlbaMatrixTest, OperatorMultiplyWorks_AnotherExample)
{
    AlbaMatrix<unsigned int> matrix1(2,2,
    {2,3,
     4,5});
    AlbaMatrix<unsigned int> matrix2(2,2,
    {1,2,
     7,0});

    AlbaMatrix<unsigned int> resultMatrix(matrix1*matrix2);

    EXPECT_EQ(2U, resultMatrix.getColumns());
    EXPECT_EQ(2U, resultMatrix.getRows());
    EXPECT_EQ(23U, resultMatrix.getEntry(0,0));
    EXPECT_EQ(4U, resultMatrix.getEntry(1,0));
    EXPECT_EQ(39U, resultMatrix.getEntry(0,1));
    EXPECT_EQ(8U, resultMatrix.getEntry(1,1));
}

TEST(AlbaMatrixTest, IsSquareWorks)
{
    AlbaMatrix<unsigned int> matrix1(3,3,
    {0,0,0,
     0,0,0,
     0,0,0});
    AlbaMatrix<unsigned int> matrix2(3,2,
    {0,0,0,
     0,0,0});

    EXPECT_TRUE(matrix1.isSquare());
    EXPECT_FALSE(matrix2.isSquare());
}

TEST(AlbaMatrixTest, IsZeroMatrixWorks)
{
    AlbaMatrix<unsigned int> matrix1(3,3,
    {0,0,0,
     0,0,0,
     0,0,0});
    AlbaMatrix<unsigned int> matrix2(2,2,
    {0,0,
     0,0});
    AlbaMatrix<unsigned int> matrix3(3,3,
    {0,0,0,
     0,1,0,
     0,0,0});

    EXPECT_TRUE(matrix1.isZeroMatrix());
    EXPECT_TRUE(matrix2.isZeroMatrix());
    EXPECT_FALSE(matrix3.isZeroMatrix());
}

TEST(AlbaMatrixTest, IsIdentityMatrixWorks)
{
    AlbaMatrix<unsigned int> matrix1(3,3,
    {1,0,0,
     0,1,0,
     0,0,1});
    AlbaMatrix<unsigned int> matrix2(3,3,
    {1,0,2,
     0,1,1,
     0,0,1});
    AlbaMatrix<unsigned int> matrix3(4,3,
    {1,0,0,0,
     0,1,0,0,
     0,0,1,0});

    EXPECT_TRUE(matrix1.isIdentityMatrix());
    EXPECT_FALSE(matrix2.isIdentityMatrix());
    EXPECT_FALSE(matrix3.isIdentityMatrix());
}

TEST(AlbaMatrixTest, IsSingularWorks)
{
    AlbaMatrix<double> matrix1(3,3,
    {1.0,1.0,1.0,
     0.0,2.0,3.0,
     5.0,5.0,1});
    AlbaMatrix<double> matrix2(3,3,
    {1.0,2.0,-3.0,
     1.0,-2.0,1.0,
     5.0,-2.0,-3.0});

    EXPECT_FALSE(matrix1.isSingular());
    EXPECT_TRUE(matrix2.isSingular());
}

TEST(AlbaMatrixTest, IsReducedRowEchelonFormWorks_MatrixCanBeCheckedIfItsInReducedRowEchelonForm)
{
    AlbaMatrix<unsigned int> matrix1(4,3,
    {1,0,0,4,
     0,1,0,5,
     0,0,1,2});
    AlbaMatrix<unsigned int> matrix2(5,3,
    {1,2,0,0,2,
     0,0,1,0,1,
     0,0,0,1,0});
    AlbaMatrix<unsigned int> matrix3(5,5,
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
    AlbaMatrix<int> matrix1(4,3,
    {1,2,0,4,
     0,0,0,0,
     0,0,1,-3});
    AlbaMatrix<int> matrix2(4,3,
    {1,0,3,4,
     0,2,-2,5,
     0,0,1,2});
    AlbaMatrix<int> matrix3(4,4,
    {1,0,3,4,
     0,1,-2,5,
     0,1,2,2,
     0,0,0,0});
    AlbaMatrix<int> matrix4(4,4,
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
    AlbaMatrix<unsigned int> matrix(14,6);

    EXPECT_EQ(14U, matrix.getColumns());
}

TEST(AlbaMatrixTest, GetRowsWorks)
{
    AlbaMatrix<unsigned int> matrix(14,6);

    EXPECT_EQ(6U, matrix.getRows());
}

TEST(AlbaMatrixTest, GetMatrixIndexWorks)
{
    AlbaMatrix<unsigned int> matrix(14,6);

    EXPECT_EQ(45U, matrix.getMatrixIndex(3, 3));
    EXPECT_EQ(73U, matrix.getMatrixIndex(3, 5));
    EXPECT_EQ(47U, matrix.getMatrixIndex(5, 3));
    EXPECT_EQ(75U, matrix.getMatrixIndex(5, 5));
}

TEST(AlbaMatrixTest, GetDeterminantWorks)
{
    AlbaMatrix<int> matrix1(1,1,{5});
    AlbaMatrix<int> matrix2(2,2,
    {2,-1,
     3,2});
    AlbaMatrix<int> matrix3(3,3,
    {1,2,3,
     2,1,3,
     3,1,2});
    AlbaMatrix<int> matrix4(4,4,
    {1,2,-3,4,
     -4,2,1,3,
     3,0,0,-3,
     2,0,-2,3});
    AlbaMatrix<int> matrix5(4,4,
    {4,3,2,2,
     0,1,-3,3,
     0,-1,3,3,
     0,3,1,1});
    AlbaMatrix<int> matrix6(4,4,
    {1,2,3,4,
     2,5,7,3,
     4,10,14,6,
     3,4,2,7});

    EXPECT_EQ(5, matrix1.getDeterminant());
    EXPECT_EQ(7, matrix2.getDeterminant());
    EXPECT_EQ(6, matrix3.getDeterminant());
    EXPECT_EQ(48, matrix4.getDeterminant());
    EXPECT_EQ(-240, matrix5.getDeterminant());
    EXPECT_EQ(0, matrix6.getDeterminant());
}

TEST(AlbaMatrixTest, GetValueUsingCramerRuleWorks)
{
    AlbaMatrix<int> matrix(3,3,
    {3,0,-1,
     -3,1,1,
     -5,0,2});
    AlbaMatrix<int>::MatrixData newColumn{3,2,4};

    EXPECT_EQ(10, matrix.getValueUsingCramerRule(0, newColumn));
    EXPECT_EQ(5, matrix.getValueUsingCramerRule(1, newColumn));
    EXPECT_EQ(27, matrix.getValueUsingCramerRule(2, newColumn));
}

TEST(AlbaMatrixTest, GetEntryWorks_ValueCanBeFetchedFromEmptyVector)
{
    AlbaMatrix<unsigned int> matrix(2,3);

    EXPECT_EQ(0U, matrix.getEntry(0,0));
    EXPECT_EQ(0U, matrix.getEntry(1,0));
    EXPECT_EQ(0U, matrix.getEntry(0,1));
    EXPECT_EQ(0U, matrix.getEntry(1,1));
    EXPECT_EQ(0U, matrix.getEntry(0,2));
    EXPECT_EQ(0U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, GetEntryWorks_ValueCanBeFetchedFromNonEmptyVector)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    EXPECT_EQ(1U, matrix.getEntry(0,0));
    EXPECT_EQ(2U, matrix.getEntry(1,0));
    EXPECT_EQ(3U, matrix.getEntry(0,1));
    EXPECT_EQ(4U, matrix.getEntry(1,1));
    EXPECT_EQ(5U, matrix.getEntry(0,2));
    EXPECT_EQ(6U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, GetMatrixDataWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

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

TEST(AlbaMatrixTest, GetMatrixWithOneColumnAndOneRowRemovedWorks)
{
    AlbaMatrix<unsigned int> matrix(3,3,
    {1,2,3,
     4,5,6,
     7,8,9});

    AlbaMatrix<unsigned int> resultMatrix(
                matrix.getMatrixWithOneColumnAndOneRowRemoved(1,2));

    EXPECT_EQ(2U, resultMatrix.getColumns());
    EXPECT_EQ(2U, resultMatrix.getRows());
    AlbaMatrix<unsigned int>::MatrixData const& resultMatrixData(
                resultMatrix.getMatrixData());
    ASSERT_EQ(4U, resultMatrixData.size());
    EXPECT_EQ(1U, resultMatrixData.at(0));
    EXPECT_EQ(3U, resultMatrixData.at(1));
    EXPECT_EQ(4U, resultMatrixData.at(2));
    EXPECT_EQ(6U, resultMatrixData.at(3));
}

TEST(AlbaMatrixTest, GetStringWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    EXPECT_EQ("-----\n|1|2|\n-----\n|3|4|\n-----\n|5|6|\n-----\n", matrix.getString());
}

TEST(AlbaMatrixTest, RetrieveColumnWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    AlbaMatrix<unsigned int>::MatrixData secondColumn;
    matrix.retrieveColumn(secondColumn, 1);

    ASSERT_EQ(3U, secondColumn.size());
    EXPECT_EQ(2U, secondColumn.at(0));
    EXPECT_EQ(4U, secondColumn.at(1));
    EXPECT_EQ(6U, secondColumn.at(2));
}

TEST(AlbaMatrixTest, RetrieveRowWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    AlbaMatrix<unsigned int>::MatrixData secondRow;
    matrix.retrieveRow(secondRow, 1);

    ASSERT_EQ(2U, secondRow.size());
    EXPECT_EQ(3U, secondRow.at(0));
    EXPECT_EQ(4U, secondRow.at(1));
}

TEST(AlbaMatrixTest, RetrieveColumnsWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

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
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

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
    AlbaMatrix<unsigned int> matrix(2,3);

    matrix.setEntry(0,0,1);
    matrix.setEntry(1,0,2);
    matrix.setEntry(0,1,3);
    matrix.setEntry(1,1,4);
    matrix.setEntry(0,2,5);
    matrix.setEntry(1,2,6);

    EXPECT_EQ(1U, matrix.getEntry(0,0));
    EXPECT_EQ(2U, matrix.getEntry(1,0));
    EXPECT_EQ(3U, matrix.getEntry(0,1));
    EXPECT_EQ(4U, matrix.getEntry(1,1));
    EXPECT_EQ(5U, matrix.getEntry(0,2));
    EXPECT_EQ(6U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, SetEntriesWorks_MultipleValuesCanSavedInTheMatrix)
{
    AlbaMatrix<unsigned int> matrix(2,3);

    matrix.setEntries(
    {1,2,
     3,4,
     5,6});

    EXPECT_EQ(1U, matrix.getEntry(0,0));
    EXPECT_EQ(2U, matrix.getEntry(1,0));
    EXPECT_EQ(3U, matrix.getEntry(0,1));
    EXPECT_EQ(4U, matrix.getEntry(1,1));
    EXPECT_EQ(5U, matrix.getEntry(0,2));
    EXPECT_EQ(6U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, SetEntriesWorks_OverwritesExistingValuesAndDoesNotChangeOtherValues)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.setEntries(
    {9,8,
     7});

    EXPECT_EQ(9U, matrix.getEntry(0,0));
    EXPECT_EQ(8U, matrix.getEntry(1,0));
    EXPECT_EQ(7U, matrix.getEntry(0,1));
    EXPECT_EQ(4U, matrix.getEntry(1,1));
    EXPECT_EQ(5U, matrix.getEntry(0,2));
    EXPECT_EQ(6U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, SetColumnWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.setColumn(1, {9, 8, 7});

    EXPECT_EQ(1U, matrix.getEntry(0,0));
    EXPECT_EQ(9U, matrix.getEntry(1,0));
    EXPECT_EQ(3U, matrix.getEntry(0,1));
    EXPECT_EQ(8U, matrix.getEntry(1,1));
    EXPECT_EQ(5U, matrix.getEntry(0,2));
    EXPECT_EQ(7U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, SetRowWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.setRow(1, {9, 8});

    EXPECT_EQ(1U, matrix.getEntry(0,0));
    EXPECT_EQ(2U, matrix.getEntry(1,0));
    EXPECT_EQ(9U, matrix.getEntry(0,1));
    EXPECT_EQ(8U, matrix.getEntry(1,1));
    EXPECT_EQ(5U, matrix.getEntry(0,2));
    EXPECT_EQ(6U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, ClearAndResizeWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.clearAndResize(3,2);

    EXPECT_EQ(0U, matrix.getEntry(0,0));
    EXPECT_EQ(0U, matrix.getEntry(0,1));
    EXPECT_EQ(0U, matrix.getEntry(1,0));
    EXPECT_EQ(0U, matrix.getEntry(1,1));
    EXPECT_EQ(0U, matrix.getEntry(2,0));
    EXPECT_EQ(0U, matrix.getEntry(2,1));
}

TEST(AlbaMatrixTest, NegateWorks)
{
    AlbaMatrix<int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.negate();

    EXPECT_EQ(-1, matrix.getEntry(0,0));
    EXPECT_EQ(-2, matrix.getEntry(1,0));
    EXPECT_EQ(-3, matrix.getEntry(0,1));
    EXPECT_EQ(-4, matrix.getEntry(1,1));
    EXPECT_EQ(-5, matrix.getEntry(0,2));
    EXPECT_EQ(-6, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, TransposeWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.transpose();

    EXPECT_EQ(1U, matrix.getEntry(0,0));
    EXPECT_EQ(3U, matrix.getEntry(1,0));
    EXPECT_EQ(5U, matrix.getEntry(2,0));
    EXPECT_EQ(2U, matrix.getEntry(0,1));
    EXPECT_EQ(4U, matrix.getEntry(1,1));
    EXPECT_EQ(6U, matrix.getEntry(2,1));
}

TEST(AlbaMatrixTest, InvertWorks)
{
    AlbaMatrix<double> matrix(3,3,
    {1.0,1.0,1.0,
     0.0,2.0,3.0,
     5.0,5.0,1});
    AlbaMatrix<double> copiedMatrix(matrix);

    matrix.invert();

    AlbaMatrix<double> multipliedMatrix(copiedMatrix*matrix);
    multipliedMatrix.transformToReducedEchelonFormUsingGaussJordanReduction();
    EXPECT_DOUBLE_EQ(1.625, matrix.getEntry(0,0));
    EXPECT_DOUBLE_EQ(-0.5, matrix.getEntry(1,0));
    EXPECT_DOUBLE_EQ(-0.125, matrix.getEntry(2,0));
    EXPECT_DOUBLE_EQ(-1.875, matrix.getEntry(0,1));
    EXPECT_DOUBLE_EQ(0.5, matrix.getEntry(1,1));
    EXPECT_DOUBLE_EQ(0.375, matrix.getEntry(2,1));
    EXPECT_DOUBLE_EQ(1.25, matrix.getEntry(0,2));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(1,2));
    EXPECT_DOUBLE_EQ(-0.25, matrix.getEntry(2,2));
    EXPECT_TRUE(multipliedMatrix.isIdentityMatrix());
}

TEST(AlbaMatrixTest, TransformToReducedEchelonFormWorks)
{
    AlbaMatrix<double> matrix(5,4,
    {0.0,2.0,3.0,-4.0,1,
     0.0,0.0,2.0,3.0,4.0,
     2.0,2.0,-5.0,2.0,4.0,
     2.0,0.0,-6.0,9.0,7.0});

    matrix.transformToReducedEchelonFormUsingGaussJordanReduction();

    EXPECT_DOUBLE_EQ(1.0, matrix.getEntry(0,0));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(1,0));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(2,0));
    EXPECT_DOUBLE_EQ(9.0, matrix.getEntry(3,0));
    EXPECT_DOUBLE_EQ(9.5, matrix.getEntry(4,0));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(0,1));
    EXPECT_DOUBLE_EQ(1.0, matrix.getEntry(1,1));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(2,1));
    EXPECT_DOUBLE_EQ(-4.25, matrix.getEntry(3,1));
    EXPECT_DOUBLE_EQ(-2.5, matrix.getEntry(4,1));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(0,2));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(1,2));
    EXPECT_DOUBLE_EQ(1.0, matrix.getEntry(2,2));
    EXPECT_DOUBLE_EQ(1.5, matrix.getEntry(3,2));
    EXPECT_DOUBLE_EQ(2.0, matrix.getEntry(4,2));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(0,3));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(1,3));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(2,3));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(3,3));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(4,3));
}

TEST(AlbaMatrixTest, InterchangeRowsWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.interchangeRows(0,2);

    EXPECT_EQ(5U, matrix.getEntry(0,0));
    EXPECT_EQ(6U, matrix.getEntry(1,0));
    EXPECT_EQ(3U, matrix.getEntry(0,1));
    EXPECT_EQ(4U, matrix.getEntry(1,1));
    EXPECT_EQ(1U, matrix.getEntry(0,2));
    EXPECT_EQ(2U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, AddTwoRowsAndPutSumInAnotherRowWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.addTwoRowsAndPutSumInAnotherRow(0,2,2);

    EXPECT_EQ(1U, matrix.getEntry(0,0));
    EXPECT_EQ(2U, matrix.getEntry(1,0));
    EXPECT_EQ(3U, matrix.getEntry(0,1));
    EXPECT_EQ(4U, matrix.getEntry(1,1));
    EXPECT_EQ(6U, matrix.getEntry(0,2));
    EXPECT_EQ(8U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, MultiplyValueInRowAndPutProductInAnotherRowWorks)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});

    matrix.multiplyValueInRowAndPutProductInAnotherRow(0,2,0);
    matrix.multiplyValueInRowAndPutProductInAnotherRow(1,3,1);
    matrix.multiplyValueInRowAndPutProductInAnotherRow(2,4,2);

    EXPECT_EQ(2U, matrix.getEntry(0,0));
    EXPECT_EQ(4U, matrix.getEntry(1,0));
    EXPECT_EQ(9U, matrix.getEntry(0,1));
    EXPECT_EQ(12U, matrix.getEntry(1,1));
    EXPECT_EQ(20U, matrix.getEntry(0,2));
    EXPECT_EQ(24U, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, SubtractRowsWithMultiplierPutDifferenceInAnotherRowWorks)
{
    AlbaMatrix<double> matrix(2,3,
    {1.0,2.0,
     3.0,4.0,
     5.0,6.0});

    matrix.subtractRowsWithMultiplierPutDifferenceInAnotherRow(1,0,3.0,1);
    matrix.subtractRowsWithMultiplierPutDifferenceInAnotherRow(2,0,5.0,2);

    EXPECT_DOUBLE_EQ(1.0, matrix.getEntry(0,0));
    EXPECT_DOUBLE_EQ(2.0, matrix.getEntry(1,0));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(0,1));
    EXPECT_DOUBLE_EQ(-2.0, matrix.getEntry(1,1));
    EXPECT_DOUBLE_EQ(0.0, matrix.getEntry(0,2));
    EXPECT_DOUBLE_EQ(-4.0, matrix.getEntry(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeCopied)
{
    AlbaMatrix<unsigned int> matrix(2,3,
    {1,2,
     3,4,
     5,6});
    AlbaMatrix<unsigned int> copiedMatrix;

    copiedMatrix = matrix;

    EXPECT_EQ(1U, copiedMatrix.getEntry(0,0));
    EXPECT_EQ(2U, copiedMatrix.getEntry(1,0));
    EXPECT_EQ(3U, copiedMatrix.getEntry(0,1));
    EXPECT_EQ(4U, copiedMatrix.getEntry(1,1));
    EXPECT_EQ(5U, copiedMatrix.getEntry(0,2));
    EXPECT_EQ(6U, copiedMatrix.getEntry(1,2));
}

}
