#include <Algorithm/UnionFind/QuickFind.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUnionFind;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using UnionFindForTest = QuickFind<int, 13>;
}

TEST(QuickFindTest, IsConnectedWorks) {
    UnionFindForTest unionFind;
    testIsConnectedWithInt<UnionFindForTest>(unionFind);
}

TEST(QuickFindTest, ConnectWorks) {
    UnionFindForTest unionFind;
    testConnectWithInt<UnionFindForTest>(unionFind);
}

TEST(QuickFindTest, ConnectWorksWithExample1) {
    UnionFindForTest unionFind;
    testConnectUsingExample1WithInt<UnionFindForTest>(unionFind);
}

TEST(QuickFindTest, ConnectWorksWithExample2) {
    UnionFindForTest unionFind;
    testConnectUsingExample2WithInt<UnionFindForTest>(unionFind);
}

TEST(QuickFindTest, GetRootWorks) {
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0, unionFind.getRoot(0));
    EXPECT_EQ(2, unionFind.getRoot(1));
    EXPECT_EQ(2, unionFind.getRoot(2));
    EXPECT_EQ(9, unionFind.getRoot(3));
    EXPECT_EQ(9, unionFind.getRoot(4));
    EXPECT_EQ(6, unionFind.getRoot(5));
    EXPECT_EQ(6, unionFind.getRoot(6));
    EXPECT_EQ(7, unionFind.getRoot(7));
    EXPECT_EQ(9, unionFind.getRoot(8));
    EXPECT_EQ(9, unionFind.getRoot(9));
}

TEST(QuickFindTest, GetRootArrayWorks) {
    UnionFindForTest unionFind;

    UnionFindForTest::RootArray expectedInitialRootArray{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    EXPECT_EQ(expectedInitialRootArray, unionFind.getRootArray());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::RootArray expectedRootArray{0, 2, 2, 9, 9, 6, 6, 7, 9, 9, 10, 11, 12};
    EXPECT_EQ(expectedRootArray, unionFind.getRootArray());
}

}  // namespace algorithm

}  // namespace alba
