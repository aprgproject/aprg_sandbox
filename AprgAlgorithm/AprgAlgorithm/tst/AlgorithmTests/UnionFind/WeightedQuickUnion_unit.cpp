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

TEST(WeightedQuickUnionTest, GetRootWithPathCompressionOnePassWorks)
{
    // Change test does not really check implementation
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
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

TEST(WeightedQuickUnionTest, GetRootWithPathCompressionTwoPassWorks)
{
    // Change test does not really check implementation
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
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
