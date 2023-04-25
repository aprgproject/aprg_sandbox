#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>
#include <AlgorithmTests/UnionFind/Utilities/CommonTestsWithUnionFind.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUnionFind;
using namespace std;

namespace alba {

namespace algorithm {

namespace {
using UnionFindForTest = UnionFindUsingMap<unsigned int>;
}

TEST(UnionFindUsingMapTest, IsConnectedWorks) {
    UnionFindForTest unionFind;
    testIsConnectedWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindUsingMapTest, ConnectWorks) {
    UnionFindForTest unionFind;
    testConnectWithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindUsingMapTest, ConnectWorksWithExample1) {
    UnionFindForTest unionFind;
    testConnectUsingExample1WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindUsingMapTest, ConnectWorksWithExample2) {
    UnionFindForTest unionFind;
    testConnectUsingExample2WithUnsignedInt<UnionFindForTest>(unionFind);
}

TEST(UnionFindUsingMapTest, GetRootWorks) {
    UnionFindForTest unionFind;
    unionFind.connect(4, 3);
    unionFind.connect(3, 8);
    unionFind.connect(6, 5);
    unionFind.connect(9, 4);
    unionFind.connect(2, 1);

    EXPECT_EQ(0U, unionFind.getRoot(0));
    EXPECT_EQ(1U, unionFind.getRoot(1));
    EXPECT_EQ(1U, unionFind.getRoot(2));
    EXPECT_EQ(3U, unionFind.getRoot(3));
    EXPECT_EQ(3U, unionFind.getRoot(4));
    EXPECT_EQ(5U, unionFind.getRoot(5));
    EXPECT_EQ(5U, unionFind.getRoot(6));
    EXPECT_EQ(7U, unionFind.getRoot(7));
    EXPECT_EQ(3U, unionFind.getRoot(8));
    EXPECT_EQ(3U, unionFind.getRoot(9));
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

    UnionFindForTest::ConnectionMap expectedConnectionMap{{1U, 1U}, {2U, 1U}, {3U, 3U}, {4U, 3U},
                                                          {5U, 5U}, {6U, 5U}, {8U, 3U}, {9U, 3U}};
    EXPECT_EQ(expectedConnectionMap, unionFind.getConnectionMap());
}

}  // namespace algorithm

}  // namespace alba
