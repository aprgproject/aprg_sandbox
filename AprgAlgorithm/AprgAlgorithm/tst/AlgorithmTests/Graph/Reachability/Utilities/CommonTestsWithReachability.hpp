#pragma once

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace CommonTestsWithReachability {

template <typename Reachability, typename Graph>
void testIsReachableWhenEmptyWithVertexAsInt() {
    Graph graph;
    Reachability reachabilityIn0(graph, 0);

    // Reachability in 0
    EXPECT_FALSE(reachabilityIn0.isReachable(1));
    EXPECT_FALSE(reachabilityIn0.isReachable(2));
    EXPECT_FALSE(reachabilityIn0.isReachable(3));
    EXPECT_FALSE(reachabilityIn0.isReachable(4));
    EXPECT_FALSE(reachabilityIn0.isReachable(5));
    EXPECT_FALSE(reachabilityIn0.isReachable(6));
    EXPECT_FALSE(reachabilityIn0.isReachable(7));
    EXPECT_FALSE(reachabilityIn0.isReachable(8));
    EXPECT_FALSE(reachabilityIn0.isReachable(9));
    EXPECT_FALSE(reachabilityIn0.isReachable(10));
    EXPECT_FALSE(reachabilityIn0.isReachable(11));
    EXPECT_FALSE(reachabilityIn0.isReachable(12));
}

template <typename Reachability, typename Graph>
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
    Reachability reachabilityIn0(graph, 0);
    Reachability reachabilityIn6(graph, 6);
    Reachability reachabilityIn9(graph, 9);

    // Reachability in 0
    EXPECT_TRUE(reachabilityIn0.isReachable(1));
    EXPECT_TRUE(reachabilityIn0.isReachable(2));
    EXPECT_TRUE(reachabilityIn0.isReachable(3));
    EXPECT_TRUE(reachabilityIn0.isReachable(4));
    EXPECT_TRUE(reachabilityIn0.isReachable(5));
    EXPECT_FALSE(reachabilityIn0.isReachable(6));
    EXPECT_FALSE(reachabilityIn0.isReachable(7));
    EXPECT_FALSE(reachabilityIn0.isReachable(8));
    EXPECT_FALSE(reachabilityIn0.isReachable(9));
    EXPECT_FALSE(reachabilityIn0.isReachable(10));
    EXPECT_FALSE(reachabilityIn0.isReachable(11));
    EXPECT_FALSE(reachabilityIn0.isReachable(12));

    // Reachability in 6
    EXPECT_TRUE(reachabilityIn6.isReachable(1));
    EXPECT_TRUE(reachabilityIn6.isReachable(2));
    EXPECT_TRUE(reachabilityIn6.isReachable(3));
    EXPECT_TRUE(reachabilityIn6.isReachable(4));
    EXPECT_TRUE(reachabilityIn6.isReachable(5));
    EXPECT_TRUE(reachabilityIn6.isReachable(6));
    EXPECT_FALSE(reachabilityIn6.isReachable(7));
    EXPECT_TRUE(reachabilityIn6.isReachable(8));
    EXPECT_TRUE(reachabilityIn6.isReachable(9));
    EXPECT_TRUE(reachabilityIn6.isReachable(10));
    EXPECT_TRUE(reachabilityIn6.isReachable(11));
    EXPECT_TRUE(reachabilityIn6.isReachable(12));

    // Reachability in 9
    EXPECT_TRUE(reachabilityIn9.isReachable(1));
    EXPECT_TRUE(reachabilityIn9.isReachable(2));
    EXPECT_TRUE(reachabilityIn9.isReachable(3));
    EXPECT_TRUE(reachabilityIn9.isReachable(4));
    EXPECT_TRUE(reachabilityIn9.isReachable(5));
    EXPECT_FALSE(reachabilityIn9.isReachable(6));
    EXPECT_FALSE(reachabilityIn9.isReachable(7));
    EXPECT_FALSE(reachabilityIn9.isReachable(8));
    EXPECT_TRUE(reachabilityIn9.isReachable(9));
    EXPECT_TRUE(reachabilityIn9.isReachable(10));
    EXPECT_TRUE(reachabilityIn9.isReachable(11));
    EXPECT_TRUE(reachabilityIn9.isReachable(12));
}

}  // namespace CommonTestsWithReachability

}  // namespace algorithm

}  // namespace alba
