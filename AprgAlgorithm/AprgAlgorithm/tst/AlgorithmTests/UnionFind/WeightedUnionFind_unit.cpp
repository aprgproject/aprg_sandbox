#include <Algorithm/UnionFind/WeightedUnionFind.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>
using namespace alba::algorithm::CommonTestsWithBaseUnionFind;
using namespace std;
namespace alba
{

namespace algorithm
{

namespace
{
using UnionFindForTest = WeightedUnionFind<unsigned int, 13>;
}

TEST(WeightedUnionFindTest, IsConnectedWorks)
{
    performIsConnectedTest<UnionFindForTest>();
}

TEST(WeightedUnionFindTest, ConnectWorks)
{
    performConnectTest<UnionFindForTest>();
}

TEST(WeightedUnionFindTest, ConnectWorksWithExample1)
{
    performConnectTestWithExample1<UnionFindForTest>();
}

TEST(WeightedUnionFindTest, ConnectWorksWithExample2)
{
    performConnectTestWithExample2<UnionFindForTest>();
}

TEST(WeightedUnionFindTest, GetRootWorks)
{
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRoot(0));    EXPECT_EQ(2U, unionFind.getRoot(1));
    EXPECT_EQ(2U, unionFind.getRoot(2));
    EXPECT_EQ(4U, unionFind.getRoot(3));
    EXPECT_EQ(4U, unionFind.getRoot(4));
    EXPECT_EQ(6U, unionFind.getRoot(5));
    EXPECT_EQ(6U, unionFind.getRoot(6));
    EXPECT_EQ(7U, unionFind.getRoot(7));
    EXPECT_EQ(4U, unionFind.getRoot(8));
    EXPECT_EQ(4U, unionFind.getRoot(9));
}

TEST(WeightedUnionFindTest, GetNumberOfUnconnectedWorks)
{
    UnionFindForTest unionFind;
    EXPECT_EQ(13U, unionFind.getNumberOfUnconnected());

    unionFind.connect(4, 3);    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);    EXPECT_EQ(8U, unionFind.getNumberOfUnconnected());
}

}

}
