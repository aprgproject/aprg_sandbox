#include <Math/AlbaMatrix.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreatedByDefaultConstructor)
{
    AlbaMatrix<unsigned int> matrix;

    EXPECT_EQ(0u, matrix.getColumns());
    EXPECT_EQ(0u, matrix.getRows());
}

TEST(AlbaMatrixTest, AlbaMatrixCanBeCreated)
{
    AlbaMatrix<unsigned int> matrix(2,3);

    EXPECT_EQ(2u, matrix.getColumns());
    EXPECT_EQ(3u, matrix.getRows());
}

TEST(AlbaMatrixTest, ValueCanBeFetchedFromEmptyVector)
{
    AlbaMatrix<unsigned int> matrix(2,3);

    EXPECT_EQ(0u, matrix.get(0,0));
    EXPECT_EQ(0u, matrix.get(1,0));
    EXPECT_EQ(0u, matrix.get(0,1));
    EXPECT_EQ(0u, matrix.get(1,1));
    EXPECT_EQ(0u, matrix.get(0,2));
    EXPECT_EQ(0u, matrix.get(1,2));
}

TEST(AlbaMatrixTest, ValueCanBeFetchedFromVectorWithSavedValue)
{
    AlbaMatrix<unsigned int> matrix(2,3);
    matrix.set(0,0,1);
    matrix.set(1,0,2);
    matrix.set(0,1,3);
    matrix.set(1,1,4);
    matrix.set(0,2,5);
    matrix.set(1,2,6);

    EXPECT_EQ(1u, matrix.get(0,0));
    EXPECT_EQ(2u, matrix.get(1,0));
    EXPECT_EQ(3u, matrix.get(0,1));
    EXPECT_EQ(4u, matrix.get(1,1));
    EXPECT_EQ(5u, matrix.get(0,2));
    EXPECT_EQ(6u, matrix.get(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeTraversedAndCopied)
{
    AlbaMatrix<unsigned int> matrix(2,3);
    AlbaMatrix<unsigned int> result(2,3);
    matrix.set(0,0,1);
    matrix.set(1,0,2);
    matrix.set(0,1,3);
    matrix.set(1,1,4);
    matrix.set(0,2,5);
    matrix.set(1,2,6);
    matrix.traverse([&](unsigned int x, unsigned int y, unsigned int value)
    {
        result.set(x, y, value);
    });

    EXPECT_EQ(1u, result.get(0,0));
    EXPECT_EQ(2u, result.get(1,0));
    EXPECT_EQ(3u, result.get(0,1));
    EXPECT_EQ(4u, result.get(1,1));
    EXPECT_EQ(5u, result.get(0,2));
    EXPECT_EQ(6u, result.get(1,2));
}

TEST(AlbaMatrixTest, MatrixCanBeResized)
{
    AlbaMatrix<unsigned int> matrix(2,3);
    matrix.clearAndResize(3,2);

    EXPECT_EQ(0u, matrix.get(0,0));
    EXPECT_EQ(0u, matrix.get(0,1));
    EXPECT_EQ(0u, matrix.get(1,0));
    EXPECT_EQ(0u, matrix.get(1,1));
    EXPECT_EQ(0u, matrix.get(2,0));
    EXPECT_EQ(0u, matrix.get(2,1));
}

TEST(AlbaMatrixTest, MatrixCanBeTransposed)
{
    AlbaMatrix<unsigned int> matrix(2,3);
    matrix.set(0,0,1);
    matrix.set(1,0,2);
    matrix.set(0,1,3);
    matrix.set(1,1,4);
    matrix.set(0,2,5);
    matrix.set(1,2,6);
    matrix.transpose();

    EXPECT_EQ(1u, matrix.get(0,0));
    EXPECT_EQ(3u, matrix.get(1,0));
    EXPECT_EQ(5u, matrix.get(2,0));
    EXPECT_EQ(2u, matrix.get(0,1));
    EXPECT_EQ(4u, matrix.get(1,1));
    EXPECT_EQ(6u, matrix.get(2,1));
}

}
