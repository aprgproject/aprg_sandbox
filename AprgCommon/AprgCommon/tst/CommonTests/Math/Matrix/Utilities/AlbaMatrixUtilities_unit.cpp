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
    AlbaMatrix<unsigned int> matrix(2, 3,    {1, 2,
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

TEST(AlbaMatrixUtilitiesTest, InterchangeRowsWorks)
{
    AlbaMatrix<unsigned int> matrix(2, 3,    {1, 2,
     3, 4,
     5, 6});

    interchangeRows(matrix, 0, 2);

    AlbaMatrix<unsigned int> expectedMatrix(2, 3,    {5, 6,
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
    AlbaMatrix<unsigned int> matrix(2, 3,    {1, 2,
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