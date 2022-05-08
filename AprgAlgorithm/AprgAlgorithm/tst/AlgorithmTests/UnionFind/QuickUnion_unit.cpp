#include <Algorithm/UnionFind/QuickUnion.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUnionFind;
using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using QuickUnionForTest = QuickUnion<unsigned int, 13>;
}

TEST(QuickUnionTest, IsConnectedWorks)
{
    testIsConnectedWithUnsignedInt<QuickUnionForTest>();
}

TEST(QuickUnionTest, ConnectWorks)
{
    testConnectWithUnsignedInt<QuickUnionForTest>();
}

TEST(QuickUnionTest, ConnectWorksWithExample1)
{
    testConnectUsingExample1WithUnsignedInt<QuickUnionForTest>();
}

TEST(QuickUnionTest, ConnectWorksWithExample2)
{
    testConnectUsingExample2WithUnsignedInt<QuickUnionForTest>();
}

TEST(QuickUnionTest, GetRootWorks)
{
    QuickUnionForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRoot(0));
    EXPECT_EQ(1U, unionFind.getRoot(1));
    EXPECT_EQ(1U, unionFind.getRoot(2));
    EXPECT_EQ(8U, unionFind.getRoot(3));
    EXPECT_EQ(8U, unionFind.getRoot(4));
    EXPECT_EQ(5U, unionFind.getRoot(5));
    EXPECT_EQ(5U, unionFind.getRoot(6));
    EXPECT_EQ(7U, unionFind.getRoot(7));
    EXPECT_EQ(8U, unionFind.getRoot(8));
    EXPECT_EQ(8U, unionFind.getRoot(9));
}

TEST(QuickUnionTest, GetNumberOfUnconnectedWorks)
{
    QuickUnionForTest unionFind;
    EXPECT_EQ(13U, unionFind.getNumberOfUnconnected());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);
    EXPECT_EQ(8U, unionFind.getNumberOfUnconnected());
}

}

}
