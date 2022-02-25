#include <Algorithm/UnionFind/UnionFind.hpp>
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
using UnionFindForUnsignedInt = UnionFind<unsigned int, 13>;
}

TEST(UnionFindTest, IsConnectedWorks){
    UnionFindForUnsignedInt unionFind;
    performIsConnectedTest(unionFind);
}
TEST(UnionFindTest, ConnectWorks)
{
    UnionFindForUnsignedInt unionFind;
    performConnectTest(unionFind);
}

TEST(UnionFindTest, ConnectWorksWithExample1)
{
    UnionFindForUnsignedInt unionFind;
    performConnectTestWithExample1(unionFind);
}

TEST(UnionFindTest, ConnectWorksWithExample2)
{
    UnionFindForUnsignedInt unionFind;
    performConnectTestWithExample2(unionFind);
}

TEST(UnionFindTest, GetRootWorks)
{
    UnionFindForUnsignedInt unionFind;    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRoot(0));
    EXPECT_EQ(2U, unionFind.getRoot(1));
    EXPECT_EQ(2U, unionFind.getRoot(2));
    EXPECT_EQ(9U, unionFind.getRoot(3));
    EXPECT_EQ(9U, unionFind.getRoot(4));
    EXPECT_EQ(6U, unionFind.getRoot(5));
    EXPECT_EQ(6U, unionFind.getRoot(6));
    EXPECT_EQ(7U, unionFind.getRoot(7));
    EXPECT_EQ(9U, unionFind.getRoot(8));
    EXPECT_EQ(9U, unionFind.getRoot(9));
}

TEST(UnionFindTest, GetNumberOfUnconnectedWorks)
{
    UnionFindForUnsignedInt unionFind;
    EXPECT_EQ(13U, unionFind.getNumberOfUnconnected());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);
    EXPECT_EQ(8U, unionFind.getNumberOfUnconnected());
}

}
}