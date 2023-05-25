#include <Algorithm/UnionFind/UnionFindForFreeIndex.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUnionFind;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using UnionFindForTest = UnionFindForFreeIndex<int>;
}

TEST(UnionFindForFreeIndexTest, IsConnectedWorks) {
    UnionFindForTest unionFind(13);
    testIsConnectedWithInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindForFreeIndexTest, ConnectWorks) {
    UnionFindForTest unionFind(13);
    testConnectWithInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindForFreeIndexTest, ConnectWorksWithExample1) {
    UnionFindForTest unionFind(13);
    testConnectUsingExample1WithInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindForFreeIndexTest, ConnectWorksWithExample2) {
    UnionFindForTest unionFind(13);
    testConnectUsingExample2WithInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindForFreeIndexTest, GetRootWorks) {
    UnionFindForTest unionFind(13);
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0, unionFind.getRoot(0));
    EXPECT_EQ(1, unionFind.getRoot(1));
    EXPECT_EQ(1, unionFind.getRoot(2));
    EXPECT_EQ(8, unionFind.getRoot(3));
    EXPECT_EQ(8, unionFind.getRoot(4));
    EXPECT_EQ(5, unionFind.getRoot(5));
    EXPECT_EQ(5, unionFind.getRoot(6));
    EXPECT_EQ(7, unionFind.getRoot(7));
    EXPECT_EQ(8, unionFind.getRoot(8));
    EXPECT_EQ(8, unionFind.getRoot(9));
}

TEST(UnionFindForFreeIndexTest, GetRootWithPathCompressionWorks) {
    UnionFindForTest unionFind(13);
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0, unionFind.getRootWithPathCompression(0));
    EXPECT_EQ(1, unionFind.getRootWithPathCompression(1));
    EXPECT_EQ(1, unionFind.getRootWithPathCompression(2));
    EXPECT_EQ(8, unionFind.getRootWithPathCompression(3));
    EXPECT_EQ(8, unionFind.getRootWithPathCompression(4));
    EXPECT_EQ(5, unionFind.getRootWithPathCompression(5));
    EXPECT_EQ(5, unionFind.getRootWithPathCompression(6));
    EXPECT_EQ(7, unionFind.getRootWithPathCompression(7));
    EXPECT_EQ(8, unionFind.getRootWithPathCompression(8));
    EXPECT_EQ(8, unionFind.getRootWithPathCompression(9));
}

TEST(UnionFindForFreeIndexTest, GetRelativeRootVectorWorks) {
    UnionFindForTest unionFind(13);

    UnionFindForTest::RootVector expectedInitialRelativeRootVector{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    EXPECT_EQ(expectedInitialRelativeRootVector, unionFind.getRelativeRootVector());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootVector expectedRelativeRootVector{0, 1, 1, 8, 8, 5, 5, 7, 8, 8, 10, 11, 12};
    EXPECT_EQ(expectedRelativeRootVector, unionFind.getRelativeRootVector());
}

}  // namespace algorithm

}  // namespace alba
