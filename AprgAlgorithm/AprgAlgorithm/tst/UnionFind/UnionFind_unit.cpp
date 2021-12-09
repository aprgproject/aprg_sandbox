#include <UnionFind/UnionFind.hpp>

#include <gtest/gtest.h>

#include <iostream>

using namespace std;

namespace alba
{

TEST(UnionFindTest, UnionFindCanBeCreated)
{
    UnionFindUsingMap<unsigned int> unionFind;
}

TEST(UnionFindTest, UnionFindUnsignedIntegerTest)
{
    UnionFindUsingMap<unsigned int> unionFind;
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

}
