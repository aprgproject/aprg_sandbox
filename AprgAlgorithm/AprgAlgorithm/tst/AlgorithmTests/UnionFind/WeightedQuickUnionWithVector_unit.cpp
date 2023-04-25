#include <Algorithm/UnionFind/WeightedQuickUnionWithVector.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUnionFind;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using UnionFindForTest = WeightedQuickUnionWithVector<unsigned int>;
}

TEST(WeightedQuickUnionWithVectorTest, IsConnectedWorks) {
    UnionFindForTest unionFind(13U);
    testIsConnectedWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithVectorTest, ConnectWorks) {
    UnionFindForTest unionFind(13U);
    testConnectWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithVectorTest, ConnectWorksWithExample1) {
    UnionFindForTest unionFind(13U);
    testConnectUsingExample1WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithVectorTest, ConnectWorksWithExample2) {
    UnionFindForTest unionFind(13U);
    testConnectUsingExample2WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithVectorTest, GetRootWorks) {
    UnionFindForTest unionFind(13U);
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

TEST(WeightedQuickUnionWithVectorTest, GetRootWithPathCompressionOnePassWorks) {
    // Change test does not really check implementation
    UnionFindForTest unionFind(13U);
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

TEST(WeightedQuickUnionWithVectorTest, GetRootWithPathCompressionTwoPassWorks) {
    // Change test does not really check implementation
    UnionFindForTest unionFind(13U);
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

TEST(WeightedQuickUnionWithVectorTest, GetRelativeRootVectorWorks) {
    UnionFindForTest unionFind(13U);

    UnionFindForTest::RootVector expectedInitialRelativeRootVector{0U, 1U, 2U, 3U,  4U,  5U, 6U,
                                                                   7U, 8U, 9U, 10U, 11U, 12U};
    EXPECT_EQ(expectedInitialRelativeRootVector, unionFind.getRelativeRootVector());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootVector expectedRelativeRootVector{0U, 2U, 2U, 4U, 4U, 6U, 6U, 7U, 4U, 4U, 10U, 11U, 12U};
    EXPECT_EQ(expectedRelativeRootVector, unionFind.getRelativeRootVector());
}

TEST(WeightedQuickUnionWithVectorTest, GetSizesOfRootsVectorWorks) {
    UnionFindForTest unionFind(13U);

    UnionFindForTest::SizeVector expectedInitialRelativeRootVector{1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U, 1U};
    EXPECT_EQ(expectedInitialRelativeRootVector, unionFind.getSizesOfRootsVector());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::SizeVector expectedRelativeRootVector{1U, 1U, 2U, 1U, 4U, 1U, 2U, 1U, 1U, 1U, 1U, 1U, 1U};
    EXPECT_EQ(expectedRelativeRootVector, unionFind.getSizesOfRootsVector());
}

}  // namespace algorithm

}  // namespace alba
