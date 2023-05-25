#include <Common/Math/Matrix/Utilities/AlbaMatrixUtilities.hpp>
#include <CommonTests/Math/Matrix/AlbaMatrixInternalFunctions.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba::matrix {

TEST(AlbaMatrixUtilitiesTest, IsSquareWorks) {
    AlbaMatrix<int> matrix1(3, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0});
    AlbaMatrix<int> matrix2(3, 2, {0, 0, 0, 0, 0, 0});

    EXPECT_TRUE(isSquare(matrix1));
    EXPECT_FALSE(isSquare(matrix2));
}

TEST(AlbaMatrixUtilitiesTest, IsZeroMatrixWorks) {
    AlbaMatrix<int> matrix1(3, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0});
    AlbaMatrix<int> matrix2(2, 2, {0, 0, 0, 0});
    AlbaMatrix<int> matrix3(3, 3, {0, 0, 0, 0, 1, 0, 0, 0, 0});

    EXPECT_TRUE(isZeroMatrix(matrix1));
    EXPECT_TRUE(isZeroMatrix(matrix2));    EXPECT_FALSE(isZeroMatrix(matrix3));
}

TEST(AlbaMatrixUtilitiesTest, IsIdentityMatrixWorks) {
    AlbaMatrix<int> matrix1(3, 3, {1, 0, 0, 0, 1, 0, 0, 0, 1});
    AlbaMatrix<int> matrix2(3, 3, {1, 0, 2, 0, 1, 1, 0, 0, 1});
    AlbaMatrix<int> matrix3(4, 3, {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0});

    EXPECT_TRUE(isIdentityMatrix(matrix1));
    EXPECT_FALSE(isIdentityMatrix(matrix2));    EXPECT_FALSE(isIdentityMatrix(matrix3));
}

TEST(AlbaMatrixUtilitiesTest, IsSingularWorks) {    AlbaMatrix<double> matrix1(3, 3, {1.0, 1.0, 1.0, 0.0, 2.0, 3.0, 5.0, 5.0, 1.0});
    AlbaMatrix<double> matrix2(3, 3, {1.0, 2.0, -3.0, 1.0, -2.0, 1.0, 5.0, -2.0, -3.0});

    EXPECT_FALSE(isSingular(matrix1));
}

TEST(AlbaMatrixUtilitiesTest, GetIdentityMatrixWorks) {
    AlbaMatrix<double> matrixToVerify(getIdentityMatrix<double>(5));

    AlbaMatrix<double> matrixToExpect(5, 5, {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
                                             0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0});    EXPECT_EQ(matrixToExpect, matrixToVerify);
}

TEST(AlbaMatrixUtilitiesTest, DoUnaryOperationWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> resultMatrix(
        doUnaryOperation(matrix, UnaryFunction<int>([](int const& value) { return (100 + value) * value; })));

    AlbaMatrix<int> expectedMatrix(2, 3, {101, 204, 309, 416, 525, 636});
    EXPECT_EQ(expectedMatrix, resultMatrix);
}

TEST(AlbaMatrixUtilitiesTest, DoBinaryOperationWithSameDimensionsWorks) {
    AlbaMatrix<int> matrix1(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(2, 3, {11, 12, 13, 14, 15, 16});

    AlbaMatrix<int> resultMatrix(doBinaryOperationWithSameDimensions(
        matrix1, matrix2,
        BinaryFunction<int>([](int const& value1, int const& value2) { return (value1 + value2) * value2; })));

    AlbaMatrix<int> expectedMatrix(2, 3, {132, 168, 208, 252, 300, 352});
    EXPECT_EQ(expectedMatrix, resultMatrix);
}

TEST(AlbaMatrixUtilitiesTest, DoUnaryAssignmentOperationWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    doUnaryAssignmentOperation(matrix, UnaryFunction<int>([](int const& value) { return (100 + value) * value; }));

    AlbaMatrix<int> expectedMatrix(2, 3, {101, 204, 309, 416, 525, 636});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, DoBinaryAssignmentOperationWithSameDimensionsWorks) {
    AlbaMatrix<int> matrix1(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(2, 3, {11, 12, 13, 14, 15, 16});

    doBinaryAssignmentOperationWithSameDimensions(
        matrix1, matrix2,
        BinaryFunction<int>([](int const& value1, int const& value2) { return (value1 + value2) * value2; }));

    AlbaMatrix<int> expectedMatrix(2, 3, {132, 168, 208, 252, 300, 352});
    EXPECT_EQ(expectedMatrix, matrix1);
}

TEST(AlbaMatrixUtilitiesTest, MultiplyMatricesWorks3By2And4By3) {
    AlbaMatrix<int> matrix1(3, 2, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

    AlbaMatrix<int> matrixToVerify = multiplyMatrices(matrix1, matrix2);

    AlbaMatrix<int> expectedMatrix(4, 2, {38, 44, 50, 56, 83, 98, 113, 128});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}
TEST(AlbaMatrixUtilitiesTest, MultiplyMatricesWorks3By2And2By3) {
    AlbaMatrix<int> matrix1(3, 2, {1, 2, -1, 3, 1, 4});
    AlbaMatrix<int> matrix2(2, 3, {-2, 5, 4, -3, 2, 1});
    AlbaMatrix<int> matrixToVerify = multiplyMatrices(matrix1, matrix2);

    AlbaMatrix<int> expectedMatrix(2, 2, {4, -2, 6, 16});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixUtilitiesTest, MultiplyMatricesWorks2By3And2By2) {
    AlbaMatrix<int> matrix1(2, 3, {1, 2, 3, 4, 5, 6});
    AlbaMatrix<int> matrix2(2, 2, {1, 2, 3, 4});

    AlbaMatrix<int> matrixToVerify = multiplyMatrices(matrix1, matrix2);

    AlbaMatrix<int> expectedMatrix(2, 3, {7, 10, 15, 22, 23, 34});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixUtilitiesTest, MultiplyMatricesWorks2By2And2By3) {
    AlbaMatrix<int> matrix1(2, 2, {1, 2, 3, 4});
    AlbaMatrix<int> matrix2(3, 2, {1, 2, 3, 4, 5, 6});

    AlbaMatrix<int> matrixToVerify = multiplyMatrices(matrix1, matrix2);

    AlbaMatrix<int> expectedMatrix(3, 2, {9, 12, 15, 19, 26, 33});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}
TEST(AlbaMatrixUtilitiesTest, GetMatrixRaiseToScalarPowerWorks) {
    AlbaMatrix<int> matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    AlbaMatrix<int> matrixToVerify = getMatrixRaiseToScalarPower(matrix, 3);

    AlbaMatrix<int> expectedMatrix(3, 3, {468, 576, 684, 1062, 1305, 1548, 1656, 2034, 2412});
    EXPECT_EQ(expectedMatrix, matrixToVerify);
}

TEST(AlbaMatrixUtilitiesTest, InterchangeRowsWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    interchangeRows(matrix, 0, 2);

    AlbaMatrix<int> expectedMatrix(2, 3, {5, 6, 3, 4, 1, 2});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, AddTwoRowsAndPutSumInAnotherRowWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    addTwoRowsAndPutSumInAnotherRow(matrix, 0, 2, 2);

    AlbaMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 6, 8});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, MultiplyEachItemAndGetSumWorks) {
    int value = multiplyEachItemAndGetSum(AlbaMatrixData<int>{1, 2, 3}, AlbaMatrixData<int>{4, 5, 6});

    EXPECT_EQ(32, value);
}

TEST(AlbaMatrixUtilitiesTest, GetIndexWithHighestSatisfiedCountWorks) {
    ListOfAlbaMatrixData<int> listOfMatrixData{{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {1, 2, 3}};
    BoolUnaryFunction<int> conditionFor1 = [](int const& entry) { return entry == 1; };
    BoolUnaryFunction<int> conditionFor2 = [](int const& entry) { return entry == 2; };
    BoolUnaryFunction<int> conditionFor3 = [](int const& entry) { return entry == 3; };

    int indexWithHighest1 = getIndexWithHighestSatisfiedCount(listOfMatrixData, conditionFor1);
    int indexWithHighest2 = getIndexWithHighestSatisfiedCount(listOfMatrixData, conditionFor2);
    int indexWithHighest3 = getIndexWithHighestSatisfiedCount(listOfMatrixData, conditionFor3);

    EXPECT_EQ(0, indexWithHighest1);
    EXPECT_EQ(1, indexWithHighest2);
    EXPECT_EQ(2, indexWithHighest3);
}

TEST(AlbaMatrixUtilitiesTest, TraverseWithUnaryOperationForDifferentRowsWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    traverseWithUnaryOperationForDifferentRows(
        matrix, 0, 1, UnaryFunction<int>([](int const& value) { return (100 + value) * value; }));

    AlbaMatrix<int> expectedMatrix(2, 3, {1, 2, 101, 204, 5, 6});
    EXPECT_EQ(expectedMatrix, matrix);
}

TEST(AlbaMatrixUtilitiesTest, TraverseWithBinaryOperationForDifferentRowsWorks) {
    AlbaMatrix<int> matrix(2, 3, {1, 2, 3, 4, 5, 6});

    traverseWithBinaryOperationForDifferentRows(
        matrix, 0, 1, 2,
        BinaryFunction<int>([](int const& value1, int const& value2) { return (value1 + value2) * value2; }));

    AlbaMatrix<int> expectedMatrix(2, 3, {1, 2, 3, 4, 12, 24});
    EXPECT_EQ(expectedMatrix, matrix);
}
}  // namespace alba::matrix