#include <Algorithm/UnionFind/QuickUnion.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUnionFind;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using UnionFindForTest = QuickUnion<int, 13>;
}

TEST(QuickUnionTest, IsConnectedWorks) {
    UnionFindForTest unionFind;
    testIsConnectedWithInt<UnionFindForTest>(unionFind);
}

TEST(QuickUnionTest, ConnectWorks) {
    UnionFindForTest unionFind;
    testConnectWithInt<UnionFindForTest>(unionFind);
}

TEST(QuickUnionTest, ConnectWorksWithExample1) {
    UnionFindForTest unionFind;
    testConnectUsingExample1WithInt<UnionFindForTest>(unionFind);
}

TEST(QuickUnionTest, ConnectWorksWithExample2) {
    UnionFindForTest unionFind;
    testConnectUsingExample2WithInt<UnionFindForTest>(unionFind);
}

TEST(QuickUnionTest, GetRootWorks) {
    UnionFindForTest unionFind;
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

TEST(QuickUnionTest, GetRelativeRootArrayWorks) {
    UnionFindForTest unionFind;

    UnionFindForTest::RootArray expectedInitialRelativeRootArray{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    EXPECT_EQ(expectedInitialRelativeRootArray, unionFind.getRelativeRootArray());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootArray expectedRelativeRootArray{0, 1, 1, 8, 3, 5, 5, 7, 8, 8, 10, 11, 12};
    EXPECT_EQ(expectedRelativeRootArray, unionFind.getRelativeRootArray());
}

}  // namespace algorithm

}  // namespace alba
