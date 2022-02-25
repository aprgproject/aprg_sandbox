#include "CommonTestsWithBaseUnionFind.hpp"

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithBaseUnionFind
{

void performIsConnectedTest(BaseUnionFindForUnsignedInt & unionFind)
{
    EXPECT_FALSE(unionFind.isConnected(1, 2));
    EXPECT_FALSE(unionFind.isConnected(3, 4));

    unionFind.connect(3, 4);

    EXPECT_FALSE(unionFind.isConnected(1, 2));
    EXPECT_FALSE(unionFind.isConnected(2, 1));
    EXPECT_TRUE(unionFind.isConnected(3, 4));
    EXPECT_TRUE(unionFind.isConnected(4, 3));
}

void performConnectTest(BaseUnionFindForUnsignedInt & unionFind)
{
    EXPECT_FALSE(unionFind.isConnected(3, 4));
    EXPECT_FALSE(unionFind.isConnected(4, 3));
    EXPECT_FALSE(unionFind.isConnected(3, 5));
    EXPECT_FALSE(unionFind.isConnected(5, 3));
    EXPECT_FALSE(unionFind.isConnected(4, 5));
    EXPECT_FALSE(unionFind.isConnected(5, 4));

    unionFind.connect(3, 4);
    unionFind.connect(4, 5);

    EXPECT_TRUE(unionFind.isConnected(3, 4));
    EXPECT_TRUE(unionFind.isConnected(4, 3));
    EXPECT_TRUE(unionFind.isConnected(3, 5));
    EXPECT_TRUE(unionFind.isConnected(5, 3));
    EXPECT_TRUE(unionFind.isConnected(4, 5));
    EXPECT_TRUE(unionFind.isConnected(5, 4));
}

void performConnectTestWithExample1(BaseUnionFindForUnsignedInt & unionFind)
{
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_TRUE(unionFind.isConnected(8,9));
    EXPECT_FALSE(unionFind.isConnected(5,4));
    EXPECT_TRUE(unionFind.isConnected(4,9));
    EXPECT_TRUE(unionFind.isConnected(4,3));
    EXPECT_FALSE(unionFind.isConnected(4,7));
    EXPECT_FALSE(unionFind.isConnected(4,5));
    EXPECT_FALSE(unionFind.isConnected(4,1));
    EXPECT_FALSE(unionFind.isConnected(4,0));
    EXPECT_TRUE(unionFind.isConnected(5,6));
}

void performConnectTestWithExample2(BaseUnionFindForUnsignedInt & unionFind)
{
    unionFind.connect(0, 1);
    unionFind.connect(0, 2);
    unionFind.connect(0, 5);
    unionFind.connect(0, 6);
    unionFind.connect(3, 4);
    unionFind.connect(3, 5);
    unionFind.connect(4, 5);
    unionFind.connect(4, 6);
    unionFind.connect(7, 8);
    unionFind.connect(9, 10);
    unionFind.connect(9, 11);
    unionFind.connect(9, 12);
    unionFind.connect(11, 12);

    EXPECT_TRUE(unionFind.isConnected(0, 1));
    EXPECT_TRUE(unionFind.isConnected(0, 2));
    EXPECT_TRUE(unionFind.isConnected(0, 3));
    EXPECT_TRUE(unionFind.isConnected(0, 4));
    EXPECT_TRUE(unionFind.isConnected(0, 5));
    EXPECT_TRUE(unionFind.isConnected(0, 6));
    EXPECT_TRUE(unionFind.isConnected(7, 8));
    EXPECT_TRUE(unionFind.isConnected(9, 10));
    EXPECT_TRUE(unionFind.isConnected(9, 11));
    EXPECT_TRUE(unionFind.isConnected(9, 12));
    EXPECT_FALSE(unionFind.isConnected(0, 7));
    EXPECT_FALSE(unionFind.isConnected(7, 9));
    EXPECT_FALSE(unionFind.isConnected(0, 9));
}

}

}

}
