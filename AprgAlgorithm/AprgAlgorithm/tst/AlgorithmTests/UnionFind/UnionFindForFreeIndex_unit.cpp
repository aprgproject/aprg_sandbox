#include <Algorithm/UnionFind/UnionFindForFreeIndex.hpp>
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
using UnionFindForTest = UnionFindForFreeIndex<unsigned int>;
}

TEST(UnionFindForFreeIndexTest, IsConnectedWorks)
{
    UnionFindForTest unionFind(13U);
    testIsConnectedWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindForFreeIndexTest, ConnectWorks)
{
    UnionFindForTest unionFind(13U);
    testConnectWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindForFreeIndexTest, ConnectWorksWithExample1)
{
    UnionFindForTest unionFind(13U);
    testConnectUsingExample1WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindForFreeIndexTest, ConnectWorksWithExample2)
{
    UnionFindForTest unionFind(13U);
    testConnectUsingExample2WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindForFreeIndexTest, GetRootWorks)
{
    UnionFindForTest unionFind(13U);
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

TEST(UnionFindForFreeIndexTest, GetRootWithPathCompressionWorks)
{
    UnionFindForTest unionFind(13U);
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRootWithPathCompression(0));
    EXPECT_EQ(1U, unionFind.getRootWithPathCompression(1));
    EXPECT_EQ(1U, unionFind.getRootWithPathCompression(2));
    EXPECT_EQ(8U, unionFind.getRootWithPathCompression(3));
    EXPECT_EQ(8U, unionFind.getRootWithPathCompression(4));
    EXPECT_EQ(5U, unionFind.getRootWithPathCompression(5));
    EXPECT_EQ(5U, unionFind.getRootWithPathCompression(6));
    EXPECT_EQ(7U, unionFind.getRootWithPathCompression(7));
    EXPECT_EQ(8U, unionFind.getRootWithPathCompression(8));
    EXPECT_EQ(8U, unionFind.getRootWithPathCompression(9));
}

TEST(UnionFindForFreeIndexTest, GetRelativeRootVectorWorks)
{
    UnionFindForTest unionFind(13U);

    UnionFindForTest::RootVector expectedInitialRelativeRootVector{0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U, 11U, 12U};
    EXPECT_EQ(expectedInitialRelativeRootVector, unionFind.getRelativeRootVector());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootVector expectedRelativeRootVector{0U, 1U, 1U, 8U, 8U, 5U, 5U, 7U, 8U, 8U, 10U, 11U, 12U};
    EXPECT_EQ(expectedRelativeRootVector, unionFind.getRelativeRootVector());
}

}

}
