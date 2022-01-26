#include <UnionFind/UnionFindUsingMap.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba{

TEST(UnionFindUsingMapTest, UnionFindUsingMapCanBeCreated)
{    UnionFindUsingMap<unsigned int>();
}

TEST(UnionFindUsingMapTest, GetRootWorks)
{
    UnionFindUsingMap<unsigned int> unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRoot(0));
    EXPECT_EQ(1U, unionFind.getRoot(1));
    EXPECT_EQ(1U, unionFind.getRoot(2));
    EXPECT_EQ(3U, unionFind.getRoot(3));
    EXPECT_EQ(3U, unionFind.getRoot(4));
    EXPECT_EQ(5U, unionFind.getRoot(5));
    EXPECT_EQ(5U, unionFind.getRoot(6));
    EXPECT_EQ(7U, unionFind.getRoot(7));
    EXPECT_EQ(3U, unionFind.getRoot(8));
    EXPECT_EQ(3U, unionFind.getRoot(9));
}

TEST(UnionFindUsingMapTest, IsConnectedWorks)
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
