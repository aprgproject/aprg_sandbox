#include <Algorithm/UnionFind/QuickFind.hpp>
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
using QuickFindForTest = QuickFind<unsigned int, 13>;
}

TEST(QuickFindTest, IsConnectedWorks)
{
    testIsConnectedWithUnsignedInt<QuickFindForTest>();
}

TEST(QuickFindTest, ConnectWorks)
{
    testConnectWithUnsignedInt<QuickFindForTest>();
}

TEST(QuickFindTest, ConnectWorksWithExample1)
{
    testConnectUsingExample1WithUnsignedInt<QuickFindForTest>();
}

TEST(QuickFindTest, ConnectWorksWithExample2)
{
    testConnectUsingExample2WithUnsignedInt<QuickFindForTest>();
}

TEST(QuickFindTest, GetRootWorks)
{
    QuickFindForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

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

TEST(QuickFindTest, GetNumberOfUnconnectedWorks)
{
    QuickFindForTest unionFind;
    EXPECT_EQ(13U, unionFind.getNumberOfUnconnected());

    unionFind.connect(4, 3);    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);
    EXPECT_EQ(8U, unionFind.getNumberOfUnconnected());
}

}

}
