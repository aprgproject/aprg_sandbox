#pragma once

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace CommonTestsWithConnectedComponents {

// UndirectedGraph

template <typename ConnectedComponent, typename Graph>
void testGetNumberOfComponentIdsWhenEmptyWithVertexAsIntWithUndirectedGraph() {
    Graph graph;
    ConnectedComponent connectedComponents(graph);

    EXPECT_EQ(0, connectedComponents.getNumberOfComponentIds());
}

template <typename ConnectedComponent, typename Graph>
void testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsIntWithUndirectedGraph() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    graph.connect(4, 5);
    graph.connect(6, 7);
    ConnectedComponent connectedComponents(graph);

    EXPECT_EQ(3, connectedComponents.getNumberOfComponentIds());
}

template <typename ConnectedComponent, typename Graph>
void testIsConnectedWhenEmptyWithVertexAsIntWithUndirectedGraph() {
    Graph graph;
    ConnectedComponent connectedComponents(graph);

    EXPECT_FALSE(connectedComponents.isConnected(0, 1));
    EXPECT_FALSE(connectedComponents.isConnected(0, 2));
    EXPECT_FALSE(connectedComponents.isConnected(0, 3));
    EXPECT_FALSE(connectedComponents.isConnected(0, 4));
    EXPECT_FALSE(connectedComponents.isConnected(0, 5));
    EXPECT_FALSE(connectedComponents.isConnected(0, 6));
    EXPECT_FALSE(connectedComponents.isConnected(0, 7));
    EXPECT_FALSE(connectedComponents.isConnected(0, 8));
    EXPECT_FALSE(connectedComponents.isConnected(0, 9));
    EXPECT_FALSE(connectedComponents.isConnected(0, 10));
    EXPECT_FALSE(connectedComponents.isConnected(0, 11));
    EXPECT_FALSE(connectedComponents.isConnected(0, 12));
}

template <typename ConnectedComponent, typename Graph>
void testIsConnectedWhenNotEmptyWithVertexAsIntWithUndirectedGraph() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 5);
    graph.connect(0, 6);
    graph.connect(3, 5);
    graph.connect(3, 4);
    graph.connect(4, 5);
    graph.connect(4, 6);
    graph.connect(7, 8);
    graph.connect(9, 10);
    graph.connect(9, 11);
    graph.connect(9, 12);
    graph.connect(11, 12);
    ConnectedComponent connectedComponents(graph);

    EXPECT_FALSE(connectedComponents.isConnected(0, 7));
    EXPECT_FALSE(connectedComponents.isConnected(0, 9));
    EXPECT_FALSE(connectedComponents.isConnected(7, 9));
    EXPECT_TRUE(connectedComponents.isConnected(0, 1));
    EXPECT_TRUE(connectedComponents.isConnected(0, 2));
    EXPECT_TRUE(connectedComponents.isConnected(0, 3));
    EXPECT_TRUE(connectedComponents.isConnected(0, 4));
    EXPECT_TRUE(connectedComponents.isConnected(0, 5));
    EXPECT_TRUE(connectedComponents.isConnected(0, 6));
    EXPECT_TRUE(connectedComponents.isConnected(7, 8));
    EXPECT_TRUE(connectedComponents.isConnected(9, 10));
    EXPECT_TRUE(connectedComponents.isConnected(9, 11));
    EXPECT_TRUE(connectedComponents.isConnected(9, 12));
}

// DirectedGraph

template <typename ConnectedComponent, typename Graph>
void testGetNumberOfComponentIdsWhenEmptyWithVertexAsIntWithDirectedGraph() {
    Graph graph;
    ConnectedComponent connectedComponents(graph);

    EXPECT_EQ(0, connectedComponents.getNumberOfComponentIds());
}

template <typename ConnectedComponent, typename Graph>
void testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsIntWithDirectedGraph() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 0);
    graph.connect(4, 5);
    graph.connect(5, 4);
    graph.connect(6, 7);
    graph.connect(7, 6);
    ConnectedComponent connectedComponents(graph);

    EXPECT_EQ(3, connectedComponents.getNumberOfComponentIds());
}

template <typename ConnectedComponent, typename Graph>
void testIsConnectedWhenEmptyWithVertexAsIntWithDirectedGraph() {
    Graph graph;
    ConnectedComponent connectedComponents(graph);

    EXPECT_FALSE(connectedComponents.isConnected(0, 1));
    EXPECT_FALSE(connectedComponents.isConnected(0, 2));
    EXPECT_FALSE(connectedComponents.isConnected(0, 3));
    EXPECT_FALSE(connectedComponents.isConnected(0, 4));
    EXPECT_FALSE(connectedComponents.isConnected(0, 5));
    EXPECT_FALSE(connectedComponents.isConnected(0, 6));
    EXPECT_FALSE(connectedComponents.isConnected(0, 7));
    EXPECT_FALSE(connectedComponents.isConnected(0, 8));
    EXPECT_FALSE(connectedComponents.isConnected(0, 9));
    EXPECT_FALSE(connectedComponents.isConnected(0, 10));
    EXPECT_FALSE(connectedComponents.isConnected(0, 11));
    EXPECT_FALSE(connectedComponents.isConnected(0, 12));
}

template <typename ConnectedComponent, typename Graph>
void testIsConnectedWhenNotEmptyWithVertexAsIntWithDirectedGraph() {
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
    ConnectedComponent connectedComponents(graph);

    EXPECT_FALSE(connectedComponents.isConnected(0, 1));
    EXPECT_FALSE(connectedComponents.isConnected(0, 6));
    EXPECT_FALSE(connectedComponents.isConnected(0, 7));
    EXPECT_FALSE(connectedComponents.isConnected(0, 9));
    EXPECT_TRUE(connectedComponents.isConnected(0, 2));
    EXPECT_TRUE(connectedComponents.isConnected(0, 3));
    EXPECT_TRUE(connectedComponents.isConnected(0, 4));
    EXPECT_TRUE(connectedComponents.isConnected(0, 5));
    EXPECT_TRUE(connectedComponents.isConnected(6, 8));
    EXPECT_TRUE(connectedComponents.isConnected(9, 10));
    EXPECT_TRUE(connectedComponents.isConnected(9, 11));
    EXPECT_TRUE(connectedComponents.isConnected(9, 12));
}

}  // namespace CommonTestsWithConnectedComponents

}  // namespace algorithm

}  // namespace alba
