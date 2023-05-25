#include <Algorithm/UnionFind/WeightedQuickUnionWithArray.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUnionFind;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using UnionFindForTest = WeightedQuickUnionWithArray<int, 13>;
}

TEST(WeightedQuickUnionWithArrayTest, IsConnectedWorks) {
    UnionFindForTest unionFind;
    testIsConnectedWithInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithArrayTest, ConnectWorks) {
    UnionFindForTest unionFind;
    testConnectWithInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithArrayTest, ConnectWorksWithExample1) {
    UnionFindForTest unionFind;
    testConnectUsingExample1WithInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithArrayTest, ConnectWorksWithExample2) {
    UnionFindForTest unionFind;
    testConnectUsingExample2WithInt<UnionFindForTest>(unionFind);
}

TEST(WeightedQuickUnionWithArrayTest, GetRootWorks) {
    UnionFindForTest unionFind;
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

TEST(WeightedQuickUnionWithArrayTest, GetRootWithPathCompressionOnePassWorks) {
    // Change test does not really check implementation
    UnionFindForTest unionFind;
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

TEST(WeightedQuickUnionWithArrayTest, GetRootWithPathCompressionTwoPassWorks) {
    // Change test does not really check implementation
    UnionFindForTest unionFind;
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

TEST(WeightedQuickUnionWithArrayTest, GetRelativeRootArrayWorks) {
    UnionFindForTest unionFind;

    UnionFindForTest::RootArray expectedInitialRelativeRootArray{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    EXPECT_EQ(expectedInitialRelativeRootArray, unionFind.getRelativeRootArray());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootArray expectedRelativeRootArray{0, 2, 2, 4, 4, 6, 6, 7, 4, 4, 10, 11, 12};
    EXPECT_EQ(expectedRelativeRootArray, unionFind.getRelativeRootArray());
}

}  // namespace algorithm

}  // namespace alba
