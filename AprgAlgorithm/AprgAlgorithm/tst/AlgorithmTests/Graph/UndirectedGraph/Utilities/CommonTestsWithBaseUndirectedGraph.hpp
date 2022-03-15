#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <gtest/gtest.h>

namespace alba
{
namespace algorithm
{

namespace CommonTestsWithBaseUndirectedGraph
{

template<typename Graph>
void performHasAnyConnectionOnUnsignedIntVertexTestWhenEmpty()
{
    Graph graph;

    EXPECT_FALSE(graph.hasAnyConnection(0U));
    EXPECT_FALSE(graph.hasAnyConnection(1U));
    EXPECT_FALSE(graph.hasAnyConnection(2U));
    EXPECT_FALSE(graph.hasAnyConnection(3U));
}

template<typename Graph>
void performHasAnyConnectionOnUnsignedIntVertexTestWhenNotEmpty()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_TRUE(graph.hasAnyConnection(0U));
    EXPECT_TRUE(graph.hasAnyConnection(1U));
    EXPECT_TRUE(graph.hasAnyConnection(2U));
    EXPECT_FALSE(graph.hasAnyConnection(3U));
}

template<typename Graph>
void performIsConnectedOnUnsignedIntVertexTestWhenEmpty()
{
    Graph graph;

    EXPECT_FALSE(graph.isConnected(0U, 1U));
    EXPECT_FALSE(graph.isConnected(0U, 2U));
    EXPECT_FALSE(graph.isConnected(1U, 2U));
    EXPECT_FALSE(graph.isConnected(0U, 3U));
}

template<typename Graph>
void performIsConnectedOnUnsignedIntVertexTestWhenNotEmpty()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_TRUE(graph.isConnected(0U, 1U));
    EXPECT_TRUE(graph.isConnected(0U, 2U));
    EXPECT_FALSE(graph.isConnected(1U, 2U));
    EXPECT_FALSE(graph.isConnected(0U, 3U));
}

template<typename Graph>
void performGetNumberOfVerticesOnUnsignedIntVertexTestWhenEmpty()
{
    Graph graph;

    EXPECT_EQ(0U, graph.getNumberOfVertices());
}

template<typename Graph>
void performGetNumberOfVerticesOnUnsignedIntVertexTestWhenNotEmpty()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(3U, graph.getNumberOfVertices());
}

template<typename Graph>
void performGetNumberOfEdgesOnUnsignedIntVertexTestWhenEmpty()
{
    Graph graph;

    EXPECT_EQ(0U, graph.getNumberOfVertices());
}

template<typename Graph>
void performGetNumberOfEdgesOnUnsignedIntVertexTestWhenNotEmpty()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, graph.getNumberOfEdges());
}

template<typename Graph>
void performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenEmpty()
{
    using Vertices = typename Graph::Vertices;
    Graph graph;

    Vertices adjacentVerticesToVerify(graph.getAdjacentVerticesAt(0));

    EXPECT_TRUE(adjacentVerticesToVerify.empty());
}

template<typename Graph>
void performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenNotEmpty()
{
    using Vertices = typename Graph::Vertices;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    Vertices adjacentVerticesAt0ToVerify(graph.getAdjacentVerticesAt(0));
    Vertices adjacentVerticesAt1ToVerify(graph.getAdjacentVerticesAt(1));
    Vertices adjacentVerticesAt2ToVerify(graph.getAdjacentVerticesAt(2));

    Vertices adjacentVerticesAt0ToExpect{1U, 2U};
    Vertices adjacentVerticesAt1ToExpect{0U};
    Vertices adjacentVerticesAt2ToExpect{0U};
    EXPECT_EQ(adjacentVerticesAt0ToExpect, adjacentVerticesAt0ToVerify);
    EXPECT_EQ(adjacentVerticesAt1ToExpect, adjacentVerticesAt1ToVerify);
    EXPECT_EQ(adjacentVerticesAt2ToExpect, adjacentVerticesAt2ToVerify);
}

template<typename Graph>
void performGetVerticesOnUnsignedIntVertexTestWhenEmpty()
{
    using Vertices = typename Graph::Vertices;
    Graph graph;

    Vertices verticesToVerify(graph.getVertices());

    EXPECT_TRUE(verticesToVerify.empty());
}

template<typename Graph>
void performGetVerticesOnUnsignedIntVertexTestWhenNotEmpty()
{
    using Vertices = typename Graph::Vertices;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    Vertices verticesToVerify(graph.getVertices());

    Vertices verticesToExpect{0U, 1U, 2U};
    EXPECT_EQ(verticesToExpect, verticesToVerify);
}

template<typename Graph>
void performGetEdgesOnUnsignedIntVertexTestWhenEmpty()
{
    using Edges = typename Graph::Edges;
    Graph graph;

    Edges edgesToVerify(graph.getEdges());

    EXPECT_TRUE(edgesToVerify.empty());
}

template<typename Graph>
void performGetEdgesOnUnsignedIntVertexTestWhenNotEmpty()
{
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    Edges edgesToVerify(graph.getEdges());

    Edges edgesToExpect{{0U, 1U}, {0U, 2U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template<typename Graph>
void performConnectOnUnsignedIntVertexTest()
{
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(3U, graph.getNumberOfVertices());
    EXPECT_EQ(2U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{0U, 1U}, {0U, 2U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template<typename Graph>
void performDisconnectOnUnsignedIntVertexTest()
{
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    graph.disconnect(0U, 1U);

    EXPECT_EQ(2U, graph.getNumberOfVertices());
    EXPECT_EQ(1U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{0U, 2U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template<typename Graph>
void performUnsignedIntVertexComplicatedTest()
{
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0U, 5U);
    graph.connect(4U, 3U);
    graph.connect(0U, 1U);
    graph.connect(9U, 12U);
    graph.connect(6U, 4U);
    graph.connect(5U, 4U);
    graph.connect(0U, 2U);
    graph.connect(11U, 12U);
    graph.connect(9U, 10U);
    graph.connect(0U, 6U);
    graph.connect(7U, 8U);
    graph.connect(9U, 11U);
    graph.connect(5U, 3U);

    EXPECT_EQ(13U, graph.getNumberOfVertices());
    EXPECT_EQ(13U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect
    {{0U, 1U}, {0U, 2U}, {0U, 5U}, {0U, 6U}, {3U, 4U}, {3U, 5U}, {4U, 5U}, {4U, 6U}, {7U, 8U}, {9U, 10U}, {9U, 11U}, {9U, 12U}, {11U, 12U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

}

}

}