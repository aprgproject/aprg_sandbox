#include <UnionFind/UnionFind.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

TEST(UnionFindTest, UnionFindCanBeCreated)
{
    UnionFind<10>();
}

TEST(UnionFindTest, GetCountWorks)
{
    UnionFind<10> unionFind;
    EXPECT_EQ(10U, unionFind.getCount());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);
    EXPECT_EQ(5U, unionFind.getCount());
}

TEST(UnionFindTest, GetIdEquivalentWorks)
{
    UnionFind<10> unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getIdEquivalent(0));
    EXPECT_EQ(2U, unionFind.getIdEquivalent(1));
    EXPECT_EQ(2U, unionFind.getIdEquivalent(2));
    EXPECT_EQ(9U, unionFind.getIdEquivalent(3));
    EXPECT_EQ(9U, unionFind.getIdEquivalent(4));
    EXPECT_EQ(6U, unionFind.getIdEquivalent(5));
    EXPECT_EQ(6U, unionFind.getIdEquivalent(6));
    EXPECT_EQ(7U, unionFind.getIdEquivalent(7));
    EXPECT_EQ(9U, unionFind.getIdEquivalent(8));
    EXPECT_EQ(9U, unionFind.getIdEquivalent(9));
}

TEST(UnionFindTest, IsConnectedWorks)
{
    UnionFind<10> unionFind;
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
