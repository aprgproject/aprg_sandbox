#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUnionFind;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using UnionFindForTest = UnionFindUsingMap<int>;
}

TEST(UnionFindUsingMapTest, IsConnectedWorks) {
    UnionFindForTest unionFind;
    testIsConnectedWithInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindUsingMapTest, ConnectWorks) {
    UnionFindForTest unionFind;
    testConnectWithInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindUsingMapTest, ConnectWorksWithExample1) {
    UnionFindForTest unionFind;
    testConnectUsingExample1WithInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindUsingMapTest, ConnectWorksWithExample2) {
    UnionFindForTest unionFind;
    testConnectUsingExample2WithInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindUsingMapTest, GetRootWorks) {
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0, unionFind.getRoot(0));
    EXPECT_EQ(1, unionFind.getRoot(1));
    EXPECT_EQ(1, unionFind.getRoot(2));
    EXPECT_EQ(3, unionFind.getRoot(3));
    EXPECT_EQ(3, unionFind.getRoot(4));
    EXPECT_EQ(5, unionFind.getRoot(5));
    EXPECT_EQ(5, unionFind.getRoot(6));
    EXPECT_EQ(7, unionFind.getRoot(7));
    EXPECT_EQ(3, unionFind.getRoot(8));
    EXPECT_EQ(3, unionFind.getRoot(9));
}

TEST(UnionFindUsingMapTest, GetConnectionMapWorks) {
    UnionFindForTest unionFind;

    UnionFindForTest::ConnectionMap expectedInitialConnectionMap;
    EXPECT_EQ(expectedInitialConnectionMap, unionFind.getConnectionMap());

    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    UnionFindForTest::ConnectionMap expectedConnectionMap{{1, 1}, {2, 1}, {3, 3}, {4, 3},
                                                          {5, 5}, {6, 5}, {8, 3}, {9, 3}};
    EXPECT_EQ(expectedConnectionMap, unionFind.getConnectionMap());
}

}  // namespace algorithm

}  // namespace alba
