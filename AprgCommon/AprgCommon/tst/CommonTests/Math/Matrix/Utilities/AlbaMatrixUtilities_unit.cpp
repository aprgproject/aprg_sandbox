#include <Common/Math/Matrix/Utilities/AlbaMatrixUtilities.hpp>
#include <CommonTests/Math/Matrix/AlbaMatrixInternalFunctions.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace matrix
{

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
}

TEST(AlbaMatrixUtilitiesTest, GetIdentityMatrixWorks)
{
    AlbaMatrix<double> matrixToVerify(getIdentityMatrix<double>(5U));

    AlbaMatrix<double> matrixToExpect(5, 5,
    {1.0, 0.0, 0.0, 0.0, 0.0,
     0.0, 1.0, 0.0, 0.0, 0.0,
     0.0, 0.0, 1.0, 0.0, 0.0,
     0.0, 0.0, 0.0, 1.0, 0.0,
     0.0, 0.0, 0.0, 0.0, 1.0});
    EXPECT_EQ(matrixToExpect, matrixToVerify);
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

TEST(AlbaMatrixUtilitiesTest, DoUnaryAssignmentOperationWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,
    {1, 2,
     3, 4,
     5, 6});

    doUnaryAssignmentOperation(matrix, UnaryFunction<unsigned int>([](unsigned int const& value)
    {
        return (100+value)*value;
    }));

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {101, 204,
     309, 416,
     525, 636});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, DoBinaryAssignmentOperationWithSameDimensionsWorks)
{
    AlbaMatrix<unsigned int> matrix1(2, 3,
    {1, 2,
     3, 4,
     5, 6});
    AlbaMatrix<unsigned int> matrix2(2, 3,
    {11, 12,
     13, 14,
     15, 16});

    doBinaryAssignmentOperationWithSameDimensions(
                matrix1, matrix2, BinaryFunction<unsigned int>([](unsigned int const& value1, unsigned int const& value2)
    {
        return (value1+value2)*value2;
    }));

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {132, 168,
     208, 252,
     300, 352});
    EXPECT_EQ(expectedMatrix, matrix1);
}

TEST(AlbaMatrixUtilitiesTest, MultiplyMatricesWorks3By2And4By3)
{
    AlbaMatrix<unsigned int> matrix1(3, 2,
    {1, 2, 3,
     4, 5, 6});
    AlbaMatrix<unsigned int> matrix2(4, 3,
    {1, 2, 3, 4,
     5, 6, 7, 8,
     9, 10, 11, 12});

    AlbaMatrix<unsigned int> matrixToVerify = multiplyMatrices(matrix1, matrix2);

    AlbaMatrix<unsigned int> expectedMatrix(4, 2,
    {38, 44, 50, 56,
     83, 98, 113, 128});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixUtilitiesTest, MultiplyMatricesWorks3By2And2By3)
{
    AlbaMatrix<int> matrix1(3, 2,
    {1, 2, -1,
     3, 1,  4});    AlbaMatrix<int> matrix2(2, 3,
    {-2, 5,
      4,-3,
      2, 1});
    AlbaMatrix<int> matrixToVerify = multiplyMatrices(matrix1, matrix2);

    AlbaMatrix<int> expectedMatrix(2, 2,
    { 4, -2,
      6, 16});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixUtilitiesTest, MultiplyMatricesWorks2By3And2By2)
{
    AlbaMatrix<unsigned int> matrix1(2, 3,
    {1, 2,
     3, 4,
     5, 6});
    AlbaMatrix<unsigned int> matrix2(2, 2,
    {1, 2,
     3, 4});

    AlbaMatrix<unsigned int> matrixToVerify = multiplyMatrices(matrix1, matrix2);

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,
    {7, 10,
     15, 22,
     23, 34});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixUtilitiesTest, MultiplyMatricesWorks2By2And2By3)
{
    AlbaMatrix<unsigned int> matrix1(2, 2,
    {1, 2,
     3, 4});
    AlbaMatrix<unsigned int> matrix2(3, 2,
    {1, 2, 3,
     4, 5, 6});

    AlbaMatrix<unsigned int> matrixToVerify = multiplyMatrices(matrix1, matrix2);

    AlbaMatrix<unsigned int> expectedMatrix(3, 2,
    {9, 12, 15,
     19, 26, 33});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixUtilitiesTest, GetMatrixRaiseToScalarPowerWorks)
{
    AlbaMatrix<int> matrix(3, 3,    {1, 2, 3,
     4, 5, 6,
     7, 8, 9});
    AlbaMatrix<int> matrixToVerify = getMatrixRaiseToScalarPower(matrix, 3);

    AlbaMatrix<int> expectedMatrix(3, 3,
    {468, 576, 684,
     1062, 1305, 1548,
     1656, 2034, 2412});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
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

TEST(AlbaMatrixUtilitiesTest, MultiplyEachItemAndGetSumWorks)
{
    unsigned int value = multiplyEachItemAndGetSum(AlbaMatrixData<unsigned int>{1U, 2U, 3U}, AlbaMatrixData<unsigned int>{4U, 5U, 6U});
    EXPECT_EQ(32U, value);
}

TEST(AlbaMatrixUtilitiesTest, GetIndexWithHighestSatisfiedCountWorks)
{
    ListOfAlbaMatrixData<unsigned int> listOfMatrixData{{1U, 1U, 1U}, {2U, 2U, 2U}, {3U, 3U, 3U}, {1U, 2U, 3U}};
    BoolUnaryFunction<unsigned int> conditionFor1 = [](unsigned int const& entry){return entry == 1U;};
    BoolUnaryFunction<unsigned int> conditionFor2 = [](unsigned int const& entry){return entry == 2U;};
    BoolUnaryFunction<unsigned int> conditionFor3 = [](unsigned int const& entry){return entry == 3U;};

    unsigned int indexWithHighest1 = getIndexWithHighestSatisfiedCount(listOfMatrixData, conditionFor1);
    unsigned int indexWithHighest2 = getIndexWithHighestSatisfiedCount(listOfMatrixData, conditionFor2);
    unsigned int indexWithHighest3 = getIndexWithHighestSatisfiedCount(listOfMatrixData, conditionFor3);

    EXPECT_EQ(0U, indexWithHighest1);
    EXPECT_EQ(1U, indexWithHighest2);
    EXPECT_EQ(2U, indexWithHighest3);
}

TEST(AlbaMatrixUtilitiesTest, TraverseWithUnaryOperationForDifferentRowsWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,    {1, 2,
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
