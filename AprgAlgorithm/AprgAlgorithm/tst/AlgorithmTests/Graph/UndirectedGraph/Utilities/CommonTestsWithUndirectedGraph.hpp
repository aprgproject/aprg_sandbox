#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace CommonTestsWithUndirectedGraph {

template <typename Graph>
void testGetGraphDirectionTypeWithVertexAsInt() {
    Graph graph;

    EXPECT_EQ(GraphDirectionType::Undirected, graph.getGraphDirectionType());
}

template <typename Graph>
void testIsEmptyWithVertexAsInt() {
    Graph emptyGraph;
    Graph nonEmptyGraph;
    nonEmptyGraph.connect(0, 1);
    nonEmptyGraph.connect(0, 2);

    EXPECT_TRUE(emptyGraph.isEmpty());
    EXPECT_FALSE(nonEmptyGraph.isEmpty());
}

template <typename Graph>
void testHasAnyConnectionWhenEmptyWithVertexAsInt() {
    Graph graph;

    EXPECT_FALSE(graph.hasAnyConnection(0));
    EXPECT_FALSE(graph.hasAnyConnection(1));
    EXPECT_FALSE(graph.hasAnyConnection(2));
    EXPECT_FALSE(graph.hasAnyConnection(3));
}

template <typename Graph>
void testHasAnyConnectionWhenNotEmptyWithVertexAsInt() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_TRUE(graph.hasAnyConnection(0));
    EXPECT_TRUE(graph.hasAnyConnection(1));
    EXPECT_TRUE(graph.hasAnyConnection(2));
    EXPECT_FALSE(graph.hasAnyConnection(3));
}

template <typename Graph>
void testIsConnectedWhenEmptyWithVertexAsInt() {
    Graph graph;

    EXPECT_FALSE(graph.isDirectlyConnected(0, 1));
    EXPECT_FALSE(graph.isDirectlyConnected(0, 2));
    EXPECT_FALSE(graph.isDirectlyConnected(1, 2));
    EXPECT_FALSE(graph.isDirectlyConnected(0, 3));
}

template <typename Graph>
void testIsConnectedWhenNotEmptyWithVertexAsInt() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_TRUE(graph.isDirectlyConnected(0, 1));
    EXPECT_TRUE(graph.isDirectlyConnected(0, 2));
    EXPECT_FALSE(graph.isDirectlyConnected(1, 2));
    EXPECT_FALSE(graph.isDirectlyConnected(0, 3));
}

template <typename Graph>
void testGetNumberOfVerticesWhenEmptyWithVertexAsInt() {
    Graph graph;

    EXPECT_EQ(0, graph.getNumberOfVertices());
}

template <typename Graph>
void testGetNumberOfVerticesWhenNotEmptyWithVertexAsInt() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ(3, graph.getNumberOfVertices());
}

template <typename Graph>
void testGetNumberOfEdgesWhenEmptyWithVertexAsInt() {
    Graph graph;

    EXPECT_EQ(0, graph.getNumberOfEdges());
}

template <typename Graph>
void testGetNumberOfEdgesWhenNotEmptyWithVertexAsInt() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ(2, graph.getNumberOfEdges());
}

template <typename Graph>
void testGetAdjacentVerticesAtWhenEmptyWithVertexAsInt() {
    using Vertices = typename Graph::Vertices;
    Graph graph;

    Vertices adjacentVerticesToVerify(graph.getAdjacentVerticesAt(0));

    EXPECT_TRUE(adjacentVerticesToVerify.empty());
}

template <typename Graph>
void testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsInt() {
    using Vertices = typename Graph::Vertices;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    Vertices adjacentVerticesAt0ToVerify(graph.getAdjacentVerticesAt(0));
    Vertices adjacentVerticesAt1ToVerify(graph.getAdjacentVerticesAt(1));
    Vertices adjacentVerticesAt2ToVerify(graph.getAdjacentVerticesAt(2));

    Vertices adjacentVerticesAt0ToExpect{1, 2};
    Vertices adjacentVerticesAt1ToExpect{0};
    Vertices adjacentVerticesAt2ToExpect{0};
    EXPECT_EQ(adjacentVerticesAt0ToExpect, adjacentVerticesAt0ToVerify);
    EXPECT_EQ(adjacentVerticesAt1ToExpect, adjacentVerticesAt1ToVerify);
    EXPECT_EQ(adjacentVerticesAt2ToExpect, adjacentVerticesAt2ToVerify);
}

template <typename Graph>
void testGetVerticesWhenEmptyWithVertexAsInt() {
    using Vertices = typename Graph::Vertices;
    Graph graph;

    Vertices verticesToVerify(graph.getVertices());

    EXPECT_TRUE(verticesToVerify.empty());
}

template <typename Graph>
void testGetVerticesWhenNotEmptyWithVertexAsInt() {
    using Vertices = typename Graph::Vertices;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    Vertices verticesToVerify(graph.getVertices());

    Vertices verticesToExpect{0, 1, 2};
    EXPECT_EQ(verticesToExpect, verticesToVerify);
}

template <typename Graph>
void testGetEdgesWhenEmptyWithVertexAsInt() {
    using Edges = typename Graph::Edges;
    Graph graph;

    Edges edgesToVerify(graph.getEdges());

    EXPECT_TRUE(edgesToVerify.empty());
}

template <typename Graph>
void testGetEdgesWhenNotEmptyWithVertexAsInt() {
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    Edges edgesToVerify(graph.getEdges());

    Edges edgesToExpect{{0, 1}, {0, 2}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template <typename Graph>
void testConnectWithVertexAsInt() {
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ(3, graph.getNumberOfVertices());
    EXPECT_EQ(2, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{0, 1}, {0, 2}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template <typename Graph>
void testDisconnectWithVertexAsInt() {
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    graph.disconnect(0, 1);

    EXPECT_EQ(2, graph.getNumberOfVertices());
    EXPECT_EQ(1, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{0, 2}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template <typename Graph>
void testClearWithVertexAsInt() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    graph.clear();

    EXPECT_EQ(0, graph.getNumberOfVertices());
    EXPECT_EQ(0, graph.getNumberOfEdges());
    EXPECT_TRUE(graph.getEdges().empty());
}

template <typename Graph>
void testGraphWorksAfterClearWithVertexAsInt() {
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.clear();

    graph.connect(3, 4);
    graph.connect(4, 5);
    graph.connect(5, 6);

    EXPECT_EQ(4, graph.getNumberOfVertices());
    EXPECT_EQ(3, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{3, 4}, {4, 5}, {5, 6}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template <typename Graph>
void testWithComplicatedExampleWithVertexAsInt() {
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0, 5);
    graph.connect(4, 3);
    graph.connect(0, 1);
    graph.connect(9, 12);
    graph.connect(6, 4);
    graph.connect(5, 4);
    graph.connect(0, 2);
    graph.connect(11, 12);
    graph.connect(9, 10);
    graph.connect(0, 6);
    graph.connect(7, 8);
    graph.connect(9, 11);
    graph.connect(5, 3);

    EXPECT_EQ(13, graph.getNumberOfVertices());
    EXPECT_EQ(13, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{0, 1}, {0, 2}, {0, 5},  {0, 6},  {3, 4},  {3, 5},  {4, 5},
                        {4, 6}, {7, 8}, {9, 10}, {9, 11}, {9, 12}, {11, 12}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

}  // namespace CommonTestsWithUndirectedGraph

}  // namespace algorithm

}  // namespace alba
