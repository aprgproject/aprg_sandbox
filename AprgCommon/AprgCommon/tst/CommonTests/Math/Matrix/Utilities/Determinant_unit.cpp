#include <Common/Math/Matrix/Utilities/Determinant.hpp>
#include <CommonTests/Math/Matrix/AlbaMatrixInternalFunctions.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace matrix
{

TEST(DeterminantTest, GetBestIndexForCoFactorExpansionWorks)
{
    ListOfAlbaMatrixData<unsigned int> rowsAndColumns
    {{1, 2, 3}, {0, 5, 0}, {7, 0, 9}};

    EXPECT_EQ(1U, getBestIndexForCoFactorExpansion(rowsAndColumns));
}

TEST(DeterminantTest, GetDeterminantWorks)
{
    AlbaMatrix<int> matrix1(1, 1, {5});
    AlbaMatrix<int> matrix2(2, 2,
    {2, -1,
     3,  2});
    AlbaMatrix<int> matrix3(3, 3,
    {1, 2, 3,
     2, 1, 3,
     3, 1, 2});
    AlbaMatrix<int> matrix4(4, 4,
    { 1, 2, -3,  4,
     -4, 2,  1,  3,
      3, 0,  0, -3,
      2, 0, -2,  3});
    AlbaMatrix<int> matrix5(4, 4,
    {4,  3,  2, 2,
     0,  1, -3, 3,
     0, -1,  3, 3,
     0,  3,  1, 1});
    AlbaMatrix<int> matrix6(4, 4,
    {1,  2,  3, 4,
     2,  5,  7, 3,
     4, 10, 14, 6,
     3,  4,  2, 7});

    EXPECT_EQ(5, getDeterminant(matrix1));
    EXPECT_EQ(7, getDeterminant(matrix2));
    EXPECT_EQ(6, getDeterminant(matrix3));
    EXPECT_EQ(48, getDeterminant(matrix4));
    EXPECT_EQ(-240, getDeterminant(matrix5));
    EXPECT_EQ(0, getDeterminant(matrix6));
}

TEST(DeterminantTest, GetValueUsingCramerRuleWorks)
{
    AlbaMatrix<int> matrix(3, 3,
    { 3, 0, -1,
     -3, 1,  1,
     -5, 0,  2});
    AlbaMatrix<int>::MatrixData newColumn{3,2,4};

    EXPECT_EQ(10, getValueUsingCramerRule(matrix, 0, newColumn));
    EXPECT_EQ(5, getValueUsingCramerRule(matrix, 1, newColumn));
    EXPECT_EQ(27, getValueUsingCramerRule(matrix, 2, newColumn));
}

TEST(DeterminantTest, GetValueFromCoFactorExpansionWorks)
{
    AlbaMatrix<int> matrix(4, 4,
    { 1, 2, -3,  4,
     -4, 2,  1,  3,
      3, 0,  0, -3,
      2, 0, -2,  3});

    EXPECT_EQ(-12, getValueFromCoFactorExpansion(matrix, 0, 0));
    EXPECT_EQ(30, getValueFromCoFactorExpansion(matrix, 1, 1));
    EXPECT_EQ(0, getValueFromCoFactorExpansion(matrix, 2, 2));
    EXPECT_EQ(72, getValueFromCoFactorExpansion(matrix, 3, 3));
}

TEST(DeterminantTest, GetDeterminantWhenSideIsMoreThan2Works)
{
    AlbaMatrix<int> matrix(4, 4,
    { 1, 2, -3,  4,
     -4, 2,  1,  3,
      3, 0,  0, -3,
      2, 0, -2,  3});

    EXPECT_EQ(48, getDeterminantWhenSideIsMoreThan2(matrix));
}

}

}
