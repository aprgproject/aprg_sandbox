#include <Algorithm/UnionFind/WeightedQuickUnionWithVector.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUnionFind;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using UnionFindForTest = WeightedQuickUnionWithVector<int>;
}

TEST(WeightedQuickUnionWithVectorTest, IsConnectedWorks) {
    UnionFindForTest unionFind(13);
    testIsConnectedWithInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithVectorTest, ConnectWorks) {
    UnionFindForTest unionFind(13);
    testConnectWithInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithVectorTest, ConnectWorksWithExample1) {
    UnionFindForTest unionFind(13);
    testConnectUsingExample1WithInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithVectorTest, ConnectWorksWithExample2) {
    UnionFindForTest unionFind(13);
    testConnectUsingExample2WithInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithVectorTest, GetRootWorks) {
    UnionFindForTest unionFind(13);
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0, unionFind.getRoot(0));
    EXPECT_EQ(2, unionFind.getRoot(1));
    EXPECT_EQ(2, unionFind.getRoot(2));
    EXPECT_EQ(4, unionFind.getRoot(3));
    EXPECT_EQ(4, unionFind.getRoot(4));
    EXPECT_EQ(6, unionFind.getRoot(5));
    EXPECT_EQ(6, unionFind.getRoot(6));
    EXPECT_EQ(7, unionFind.getRoot(7));
    EXPECT_EQ(4, unionFind.getRoot(8));
    EXPECT_EQ(4, unionFind.getRoot(9));
}

TEST(WeightedQuickUnionWithVectorTest, GetRootWithPathCompressionOnePassWorks) {
    // Change test does not really check implementation
    UnionFindForTest unionFind(13);
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0, unionFind.getRootWithPathCompressionOnePass(0));
    EXPECT_EQ(2, unionFind.getRootWithPathCompressionOnePass(1));
    EXPECT_EQ(2, unionFind.getRootWithPathCompressionOnePass(2));
    EXPECT_EQ(4, unionFind.getRootWithPathCompressionOnePass(3));
    EXPECT_EQ(4, unionFind.getRootWithPathCompressionOnePass(4));
    EXPECT_EQ(6, unionFind.getRootWithPathCompressionOnePass(5));
    EXPECT_EQ(6, unionFind.getRootWithPathCompressionOnePass(6));
    EXPECT_EQ(7, unionFind.getRootWithPathCompressionOnePass(7));
    EXPECT_EQ(4, unionFind.getRootWithPathCompressionOnePass(8));
    EXPECT_EQ(4, unionFind.getRootWithPathCompressionOnePass(9));
}

TEST(WeightedQuickUnionWithVectorTest, GetRootWithPathCompressionTwoPassWorks) {
    // Change test does not really check implementation
    UnionFindForTest unionFind(13);
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0, unionFind.getRootWithPathCompressionTwoPass(0));
    EXPECT_EQ(2, unionFind.getRootWithPathCompressionTwoPass(1));
    EXPECT_EQ(2, unionFind.getRootWithPathCompressionTwoPass(2));
    EXPECT_EQ(4, unionFind.getRootWithPathCompressionTwoPass(3));
    EXPECT_EQ(4, unionFind.getRootWithPathCompressionTwoPass(4));
    EXPECT_EQ(6, unionFind.getRootWithPathCompressionTwoPass(5));
    EXPECT_EQ(6, unionFind.getRootWithPathCompressionTwoPass(6));
    EXPECT_EQ(7, unionFind.getRootWithPathCompressionTwoPass(7));
    EXPECT_EQ(4, unionFind.getRootWithPathCompressionTwoPass(8));
    EXPECT_EQ(4, unionFind.getRootWithPathCompressionTwoPass(9));
}

TEST(WeightedQuickUnionWithVectorTest, GetRelativeRootVectorWorks) {
    UnionFindForTest unionFind(13);

    UnionFindForTest::RootVector expectedInitialRelativeRootVector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    EXPECT_EQ(expectedInitialRelativeRootVector, unionFind.getRelativeRootVector());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootVector expectedRelativeRootVector{0, 2, 2, 4, 4, 6, 6, 7, 4, 4, 10, 11, 12};
    EXPECT_EQ(expectedRelativeRootVector, unionFind.getRelativeRootVector());
}

TEST(WeightedQuickUnionWithVectorTest, GetSizesOfRootsVectorWorks) {
    UnionFindForTest unionFind(13);

    UnionFindForTest::SizeVector expectedInitialRelativeRootVector{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(expectedInitialRelativeRootVector, unionFind.getSizesOfRootsVector());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::SizeVector expectedRelativeRootVector{1, 1, 2, 1, 4, 1, 2, 1, 1, 1, 1, 1, 1};
    EXPECT_EQ(expectedRelativeRootVector, unionFind.getSizesOfRootsVector());
}

}  // namespace algorithm

}  // namespace alba
