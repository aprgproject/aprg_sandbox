#pragma once

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace CommonTestsWithTransitiveClosure {

template <typename TransitiveClosure, typename Graph>
void testIsReachableWhenEmptyWithVertexAsInt() {
    Graph graph;
    TransitiveClosure transitiveClosure(graph);

    // Reachability in 0
    EXPECT_FALSE(transitiveClosure.isReachable(0, 1));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 2));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 3));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 4));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 5));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 6));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 7));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 8));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 9));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 10));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 11));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 12));
}

template <typename TransitiveClosure, typename Graph>
void testIsReachableWhenNotEmptyWithVertexAsInt() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 5);
    graph.connect(2, 0);
    graph.connect(2, 3);
    graph.connect(3, 2);
    graph.connect(3, 5);
    graph.connect(4, 2);
    graph.connect(4, 3);
    graph.connect(5, 4);
    graph.connect(6, 0);
    graph.connect(6, 4);
    graph.connect(6, 8);
    graph.connect(6, 9);
    graph.connect(7, 6);
    graph.connect(7, 9);
    graph.connect(8, 6);
    graph.connect(9, 10);
    graph.connect(9, 11);
    graph.connect(10, 12);
    graph.connect(11, 4);
    graph.connect(11, 12);
    graph.connect(12, 9);
    TransitiveClosure transitiveClosure(graph);

    // Reachability in 0
    EXPECT_TRUE(transitiveClosure.isReachable(0, 1));
    EXPECT_TRUE(transitiveClosure.isReachable(0, 2));
    EXPECT_TRUE(transitiveClosure.isReachable(0, 3));
    EXPECT_TRUE(transitiveClosure.isReachable(0, 4));
    EXPECT_TRUE(transitiveClosure.isReachable(0, 5));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 6));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 7));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 8));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 9));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 10));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 11));
    EXPECT_FALSE(transitiveClosure.isReachable(0, 12));

    // Reachability in 6
    EXPECT_TRUE(transitiveClosure.isReachable(6, 1));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 2));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 3));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 4));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 5));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 6));
    EXPECT_FALSE(transitiveClosure.isReachable(6, 7));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 8));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 9));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 10));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 11));
    EXPECT_TRUE(transitiveClosure.isReachable(6, 12));

    // Reachability in 9
    EXPECT_TRUE(transitiveClosure.isReachable(9, 1));
    EXPECT_TRUE(transitiveClosure.isReachable(9, 2));
    EXPECT_TRUE(transitiveClosure.isReachable(9, 3));
    EXPECT_TRUE(transitiveClosure.isReachable(9, 4));
    EXPECT_TRUE(transitiveClosure.isReachable(9, 5));
    EXPECT_FALSE(transitiveClosure.isReachable(9, 6));
    EXPECT_FALSE(transitiveClosure.isReachable(9, 7));
    EXPECT_FALSE(transitiveClosure.isReachable(9, 8));
    EXPECT_TRUE(transitiveClosure.isReachable(9, 9));
    EXPECT_TRUE(transitiveClosure.isReachable(9, 10));
    EXPECT_TRUE(transitiveClosure.isReachable(9, 11));
    EXPECT_TRUE(transitiveClosure.isReachable(9, 12));
}

}  // namespace CommonTestsWithTransitiveClosure

}  // namespace algorithm

}  // namespace alba
