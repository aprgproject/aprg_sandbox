#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithBaseDirectedGraph
{

template<typename Graph>
void testGetGraphDirectionTypeWithVertexAsUnsignedInt()
{
    Graph graph;

    EXPECT_EQ(GraphDirectionType::Directed, graph.getGraphDirectionType());
}

template<typename Graph>
void testIsConnectedWhenEmptyWithVertexAsUnsignedInt()
{
    Graph graph;

    EXPECT_FALSE(graph.isConnected(0U, 1U));
    EXPECT_FALSE(graph.isConnected(0U, 2U));
    EXPECT_FALSE(graph.isConnected(1U, 2U));
    EXPECT_FALSE(graph.isConnected(0U, 3U));
}

template<typename Graph>
void testIsConnectedWhenNotEmptyWithVertexAsUnsignedInt()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    EXPECT_TRUE(graph.isConnected(0U, 1U));
    EXPECT_TRUE(graph.isConnected(2U, 0U));
    EXPECT_FALSE(graph.isConnected(1U, 0U));
    EXPECT_FALSE(graph.isConnected(0U, 2U));
    EXPECT_FALSE(graph.isConnected(1U, 2U));
    EXPECT_FALSE(graph.isConnected(0U, 3U));
}

template<typename Graph>
void testGetNumberOfVerticesWhenEmptyWithVertexAsUnsignedInt()
{
    Graph graph;

    EXPECT_EQ(0U, graph.getNumberOfVertices());
}

template<typename Graph>
void testGetNumberOfVerticesWhenNotEmptyWithVertexAsUnsignedInt()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    EXPECT_EQ(3U, graph.getNumberOfVertices());
}

template<typename Graph>
void testGetNumberOfEdgesWhenEmptyWithVertexAsUnsignedInt()
{
    Graph graph;

    EXPECT_EQ(0U, graph.getNumberOfEdges());
}

template<typename Graph>
void testGetNumberOfEdgesWhenNotEmptyWithVertexAsUnsignedInt()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    EXPECT_EQ(2U, graph.getNumberOfEdges());
}

template<typename Graph>
void testGetAdjacentVerticesAtWhenEmptyWithVertexAsUnsignedInt()
{
    using Vertices = typename Graph::Vertices;
    Graph graph;

    Vertices adjacentVerticesToVerify(graph.getAdjacentVerticesAt(0));

    EXPECT_TRUE(adjacentVerticesToVerify.empty());
}

template<typename Graph>
void testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsUnsignedInt()
{
    using Vertices = typename Graph::Vertices;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    Vertices adjacentVerticesAt0ToVerify(graph.getAdjacentVerticesAt(0));
    Vertices adjacentVerticesAt1ToVerify(graph.getAdjacentVerticesAt(1));
    Vertices adjacentVerticesAt2ToVerify(graph.getAdjacentVerticesAt(2));

    Vertices adjacentVerticesAt0ToExpect{1U};
    Vertices adjacentVerticesAt2ToExpect{0U};
    EXPECT_EQ(adjacentVerticesAt0ToExpect, adjacentVerticesAt0ToVerify);
    EXPECT_TRUE(adjacentVerticesAt1ToVerify.empty());
    EXPECT_EQ(adjacentVerticesAt2ToExpect, adjacentVerticesAt2ToVerify);
}

template<typename Graph>
void testGetVerticesWhenEmptyWithVertexAsUnsignedInt()
{
    using Vertices = typename Graph::Vertices;
    Graph graph;

    Vertices verticesToVerify(graph.getVertices());

    EXPECT_TRUE(verticesToVerify.empty());
}

template<typename Graph>
void testGetVerticesWhenNotEmptyWithVertexAsUnsignedInt()
{
    using Vertices = typename Graph::Vertices;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    Vertices verticesToVerify(graph.getVertices());

    Vertices verticesToExpect{0U, 1U, 2U};
    EXPECT_EQ(verticesToExpect, verticesToVerify);
}

template<typename Graph>
void testGetEdgesWhenEmptyWithVertexAsUnsignedInt()
{
    using Edges = typename Graph::Edges;
    Graph graph;

    Edges edgesToVerify(graph.getEdges());

    EXPECT_TRUE(edgesToVerify.empty());
}

template<typename Graph>
void testGetEdgesWhenNotEmptyWithVertexAsUnsignedInt()
{
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    Edges edgesToVerify(graph.getEdges());

    Edges edgesToExpect{{0U, 1U}, {2U, 0U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template<typename Graph>
void testConnectWithVertexAsUnsignedInt()
{
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    EXPECT_EQ(3U, graph.getNumberOfVertices());
    EXPECT_EQ(2U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{0U, 1U}, {2U, 0U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template<typename Graph>
void testDisconnectWithVertexAsUnsignedInt()
{
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    graph.disconnect(0U, 1U);

    EXPECT_EQ(2U, graph.getNumberOfVertices());
    EXPECT_EQ(1U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{2U, 0U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template<typename Graph>
void testClearWithVertexAsUnsignedInt()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    graph.clear();

    EXPECT_EQ(0U, graph.getNumberOfVertices());
    EXPECT_EQ(0U, graph.getNumberOfEdges());
    EXPECT_TRUE(graph.getEdges().empty());
}

template<typename Graph>
void testReverseDirectionsWithVertexAsUnsignedInt()
{
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    graph.reverseDirections();

    EXPECT_EQ(3U, graph.getNumberOfVertices());
    EXPECT_EQ(2U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{0U, 2U}, {1U, 0U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

template<typename Graph>
void testWithComplicatedExampleWithVertexAsUnsignedInt()
{
    using Edges = typename Graph::Edges;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 5U);
    graph.connect(2U, 0U);
    graph.connect(2U, 3U);
    graph.connect(3U, 2U);
    graph.connect(3U, 5U);
    graph.connect(4U, 2U);
    graph.connect(4U, 3U);
    graph.connect(5U, 4U);
    graph.connect(6U, 0U);
    graph.connect(6U, 4U);
    graph.connect(6U, 8U);
    graph.connect(6U, 9U);
    graph.connect(7U, 6U);
    graph.connect(7U, 9U);
    graph.connect(8U, 6U);
    graph.connect(9U, 10U);
    graph.connect(9U, 11U);
    graph.connect(10U, 12U);
    graph.connect(11U, 4U);
    graph.connect(11U, 12U);
    graph.connect(12U, 9U);

    EXPECT_EQ(13U, graph.getNumberOfVertices());
    EXPECT_EQ(22U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect
    {{0,1}, {0,5}, {2,0}, {2,3}, {3,2}, {3,5}, {4,2}, {4,3}, {5,4}, {6,0}, {6,4}, {6,8}, {6,9},
        {7,6}, {7,9}, {8,6}, {9,10}, {9,11}, {10,12}, {11,4}, {11,12}, {12,9}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

}

}

}
