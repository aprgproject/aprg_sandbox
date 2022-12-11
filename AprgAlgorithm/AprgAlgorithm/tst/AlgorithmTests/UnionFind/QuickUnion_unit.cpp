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
using UnionFindForTest = QuickUnion<unsigned int, 13>;
}

TEST(QuickUnionTest, IsConnectedWorks)
{
    UnionFindForTest unionFind;
    testIsConnectedWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(QuickUnionTest, ConnectWorks)
{
    UnionFindForTest unionFind;
    testConnectWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(QuickUnionTest, ConnectWorksWithExample1)
{
    UnionFindForTest unionFind;
    testConnectUsingExample1WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(QuickUnionTest, ConnectWorksWithExample2)
{
    UnionFindForTest unionFind;
    testConnectUsingExample2WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(QuickUnionTest, GetRootWorks)
{
    UnionFindForTest unionFind;
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

TEST(QuickUnionTest, GetRelativeRootArrayWorks)
{
    UnionFindForTest unionFind;

    UnionFindForTest::RootArray expectedInitialRelativeRootArray{0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U, 11U, 12U};
    EXPECT_EQ(expectedInitialRelativeRootArray, unionFind.getRelativeRootArray());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootArray expectedRelativeRootArray{0U, 1U, 1U, 8U, 3U, 5U, 5U, 7U, 8U, 8U, 10U, 11U, 12U};
    EXPECT_EQ(expectedRelativeRootArray, unionFind.getRelativeRootArray());
}

}

}
