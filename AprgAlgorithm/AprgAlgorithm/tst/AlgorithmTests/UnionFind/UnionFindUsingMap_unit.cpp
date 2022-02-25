#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithBaseUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseUnionFind;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using UnionFindForUnsignedInt = UnionFindUsingMap<unsigned int>;
}

TEST(UnionFindUsingMapTest, IsConnectedWorks)
{
    UnionFindForUnsignedInt unionFind;
    performIsConnectedTest(unionFind);
}

TEST(UnionFindUsingMapTest, ConnectWorks)
{
    UnionFindForUnsignedInt unionFind;
    performConnectTest(unionFind);
}

TEST(UnionFindUsingMapTest, ConnectWorksWithExample1)
{
    UnionFindForUnsignedInt unionFind;
    performConnectTestWithExample1(unionFind);
}

TEST(UnionFindUsingMapTest, ConnectWorksWithExample2)
{
    UnionFindForUnsignedInt unionFind;
    performConnectTestWithExample2(unionFind);
}

TEST(UnionFindUsingMapTest, GetRootWorks)
{
    UnionFindForUnsignedInt unionFind;    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);    unionFind.connect(2, 1);

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

}

}
