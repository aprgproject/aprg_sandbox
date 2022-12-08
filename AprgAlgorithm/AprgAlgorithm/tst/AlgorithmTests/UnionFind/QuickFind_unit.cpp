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
using UnionFindForTest = QuickFind<unsigned int, 13>;
}

TEST(QuickFindTest, IsConnectedWorks)
{
    UnionFindForTest unionFind;
    testIsConnectedWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(QuickFindTest, ConnectWorks)
{
    UnionFindForTest unionFind;
    testConnectWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(QuickFindTest, ConnectWorksWithExample1)
{
    UnionFindForTest unionFind;
    testConnectUsingExample1WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(QuickFindTest, ConnectWorksWithExample2)
{
    UnionFindForTest unionFind;
    testConnectUsingExample2WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(QuickFindTest, GetRootWorks)
{
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRoot(0));    EXPECT_EQ(2U, unionFind.getRoot(1));
    EXPECT_EQ(2U, unionFind.getRoot(2));
    EXPECT_EQ(9U, unionFind.getRoot(3));
    EXPECT_EQ(9U, unionFind.getRoot(4));
    EXPECT_EQ(6U, unionFind.getRoot(5));
    EXPECT_EQ(6U, unionFind.getRoot(6));
    EXPECT_EQ(7U, unionFind.getRoot(7));
    EXPECT_EQ(9U, unionFind.getRoot(8));
    EXPECT_EQ(9U, unionFind.getRoot(9));
}

TEST(QuickFindTest, GetRootArrayWorks)
{
    UnionFindForTest unionFind;

    UnionFindForTest::RootArray expectedInitialRootArray{0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U, 11U, 12U};
    EXPECT_EQ(expectedInitialRootArray, unionFind.getRootArray());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootArray expectedRootArray{0U, 2U, 2U, 9U, 9U, 6U, 6U, 7U, 9U, 9U, 10U, 11U, 12U};
    EXPECT_EQ(expectedRootArray, unionFind.getRootArray());
}

}
}