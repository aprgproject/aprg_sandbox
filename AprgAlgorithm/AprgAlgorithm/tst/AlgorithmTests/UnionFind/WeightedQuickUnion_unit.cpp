#include <Algorithm/UnionFind/WeightedQuickUnion.hpp>
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
using UnionFindForTest = WeightedQuickUnion<unsigned int, 13>;
}

TEST(WeightedQuickUnionTest, IsConnectedWorks)
{
    testIsConnectedWithUnsignedInt<UnionFindForTest>();
}

TEST(WeightedQuickUnionTest, ConnectWorks)
{
    testConnectWithUnsignedInt<UnionFindForTest>();
}

TEST(WeightedQuickUnionTest, ConnectWorksWithExample1)
{
    testConnectUsingExample1WithUnsignedInt<UnionFindForTest>();
}

TEST(WeightedQuickUnionTest, ConnectWorksWithExample2)
{
    testConnectUsingExample2WithUnsignedInt<UnionFindForTest>();
}

TEST(WeightedQuickUnionTest, GetRootWorks)
{
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
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

TEST(WeightedQuickUnionTest, GetRootWithPassCompressionOnePassWorks)
{
    // Change test does not really check implementation
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRootWithPassCompressionOnePass(0));
    EXPECT_EQ(2U, unionFind.getRootWithPassCompressionOnePass(1));
    EXPECT_EQ(2U, unionFind.getRootWithPassCompressionOnePass(2));
    EXPECT_EQ(4U, unionFind.getRootWithPassCompressionOnePass(3));
    EXPECT_EQ(4U, unionFind.getRootWithPassCompressionOnePass(4));
    EXPECT_EQ(6U, unionFind.getRootWithPassCompressionOnePass(5));
    EXPECT_EQ(6U, unionFind.getRootWithPassCompressionOnePass(6));
    EXPECT_EQ(7U, unionFind.getRootWithPassCompressionOnePass(7));
    EXPECT_EQ(4U, unionFind.getRootWithPassCompressionOnePass(8));
    EXPECT_EQ(4U, unionFind.getRootWithPassCompressionOnePass(9));
}

TEST(WeightedQuickUnionTest, GetRootWithPassCompressionTwoPassWorks)
{
    // Change test does not really check implementation
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRootWithPassCompressionTwoPass(0));
    EXPECT_EQ(2U, unionFind.getRootWithPassCompressionTwoPass(1));
    EXPECT_EQ(2U, unionFind.getRootWithPassCompressionTwoPass(2));
    EXPECT_EQ(4U, unionFind.getRootWithPassCompressionTwoPass(3));
    EXPECT_EQ(4U, unionFind.getRootWithPassCompressionTwoPass(4));
    EXPECT_EQ(6U, unionFind.getRootWithPassCompressionTwoPass(5));
    EXPECT_EQ(6U, unionFind.getRootWithPassCompressionTwoPass(6));
    EXPECT_EQ(7U, unionFind.getRootWithPassCompressionTwoPass(7));
    EXPECT_EQ(4U, unionFind.getRootWithPassCompressionTwoPass(8));
    EXPECT_EQ(4U, unionFind.getRootWithPassCompressionTwoPass(9));
}

TEST(WeightedQuickUnionTest, GetNumberOfUnconnectedWorks)
{
    UnionFindForTest unionFind;
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
