#include <Algorithm/UnionFind/WeightedQuickUnionWithArray.hpp>
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
using UnionFindForTest = WeightedQuickUnionWithArray<unsigned int, 13>;
}

TEST(WeightedQuickUnionWithArrayTest, IsConnectedWorks)
{
    UnionFindForTest unionFind;
    testIsConnectedWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithArrayTest, ConnectWorks)
{
    UnionFindForTest unionFind;
    testConnectWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithArrayTest, ConnectWorksWithExample1)
{
    UnionFindForTest unionFind;
    testConnectUsingExample1WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithArrayTest, ConnectWorksWithExample2)
{
    UnionFindForTest unionFind;
    testConnectUsingExample2WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithArrayTest, GetRootWorks)
{
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRoot(0));
    EXPECT_EQ(2U, unionFind.getRoot(1));
    EXPECT_EQ(2U, unionFind.getRoot(2));
    EXPECT_EQ(4U, unionFind.getRoot(3));
    EXPECT_EQ(4U, unionFind.getRoot(4));
    EXPECT_EQ(6U, unionFind.getRoot(5));
    EXPECT_EQ(6U, unionFind.getRoot(6));
    EXPECT_EQ(7U, unionFind.getRoot(7));
    EXPECT_EQ(4U, unionFind.getRoot(8));
    EXPECT_EQ(4U, unionFind.getRoot(9));
}

TEST(WeightedQuickUnionWithArrayTest, GetRootWithPathCompressionOnePassWorks)
{
    // Change test does not really check implementation
    UnionFindForTest unionFind;    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRootWithPathCompressionOnePass(0));
    EXPECT_EQ(2U, unionFind.getRootWithPathCompressionOnePass(1));
    EXPECT_EQ(2U, unionFind.getRootWithPathCompressionOnePass(2));
    EXPECT_EQ(4U, unionFind.getRootWithPathCompressionOnePass(3));
    EXPECT_EQ(4U, unionFind.getRootWithPathCompressionOnePass(4));
    EXPECT_EQ(6U, unionFind.getRootWithPathCompressionOnePass(5));
    EXPECT_EQ(6U, unionFind.getRootWithPathCompressionOnePass(6));
    EXPECT_EQ(7U, unionFind.getRootWithPathCompressionOnePass(7));
    EXPECT_EQ(4U, unionFind.getRootWithPathCompressionOnePass(8));
    EXPECT_EQ(4U, unionFind.getRootWithPathCompressionOnePass(9));
}

TEST(WeightedQuickUnionWithArrayTest, GetRootWithPathCompressionTwoPassWorks)
{
    // Change test does not really check implementation
    UnionFindForTest unionFind;    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRootWithPathCompressionTwoPass(0));
    EXPECT_EQ(2U, unionFind.getRootWithPathCompressionTwoPass(1));
    EXPECT_EQ(2U, unionFind.getRootWithPathCompressionTwoPass(2));
    EXPECT_EQ(4U, unionFind.getRootWithPathCompressionTwoPass(3));
    EXPECT_EQ(4U, unionFind.getRootWithPathCompressionTwoPass(4));
    EXPECT_EQ(6U, unionFind.getRootWithPathCompressionTwoPass(5));
    EXPECT_EQ(6U, unionFind.getRootWithPathCompressionTwoPass(6));
    EXPECT_EQ(7U, unionFind.getRootWithPathCompressionTwoPass(7));
    EXPECT_EQ(4U, unionFind.getRootWithPathCompressionTwoPass(8));
    EXPECT_EQ(4U, unionFind.getRootWithPathCompressionTwoPass(9));
}

TEST(WeightedQuickUnionWithArrayTest, GetRelativeRootArrayWorks)
{
    UnionFindForTest unionFind;

    UnionFindForTest::RootArray expectedInitialRelativeRootArray{0U, 1U, 2U, 3U, 4U, 5U, 6U, 7U, 8U, 9U, 10U, 11U, 12U};
    EXPECT_EQ(expectedInitialRelativeRootArray, unionFind.getRelativeRootArray());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootArray expectedRelativeRootArray{0U, 2U, 2U, 4U, 4U, 6U, 6U, 7U, 4U, 4U, 10U, 11U, 12U};
    EXPECT_EQ(expectedRelativeRootArray, unionFind.getRelativeRootArray());
}

}
}
