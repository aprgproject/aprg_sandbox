#pragma once

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithConnectedComponents
{

//UndirectedGraph

template <typename ConnectedComponent, typename Graph>
void testGetNumberOfComponentIdsWhenEmptyWithVertexAsUnsignedIntWithUndirectedGraph()
{
    Graph graph;
    ConnectedComponent connectedComponents(graph);

    EXPECT_EQ(0U, connectedComponents.getNumberOfComponentIds());
}

template <typename ConnectedComponent, typename Graph>
void testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsUnsignedIntWithUndirectedGraph()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    graph.connect(4U, 5U);
    graph.connect(6U, 7U);
    ConnectedComponent connectedComponents(graph);

    EXPECT_EQ(3U, connectedComponents.getNumberOfComponentIds());
}

template <typename ConnectedComponent, typename Graph>
void testIsConnectedWhenEmptyWithVertexAsUnsignedIntWithUndirectedGraph()
{
    Graph graph;
    ConnectedComponent connectedComponents(graph);

    EXPECT_FALSE(connectedComponents.isConnected(0U, 1U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 2U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 3U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 4U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 5U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 6U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 7U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 8U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 9U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 10U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 11U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 12U));
}

template <typename ConnectedComponent, typename Graph>
void testIsConnectedWhenNotEmptyWithVertexAsUnsignedIntWithUndirectedGraph()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(0U, 6U);
    graph.connect(3U, 5U);
    graph.connect(3U, 4U);
    graph.connect(4U, 5U);
    graph.connect(4U, 6U);
    graph.connect(7U, 8U);
    graph.connect(9U, 10U);
    graph.connect(9U, 11U);
    graph.connect(9U, 12U);
    graph.connect(11U, 12U);
    ConnectedComponent connectedComponents(graph);

    EXPECT_FALSE(connectedComponents.isConnected(0U, 7U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 9U));
    EXPECT_FALSE(connectedComponents.isConnected(7U, 9U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 1U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 2U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 3U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 4U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 5U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 6U));
    EXPECT_TRUE(connectedComponents.isConnected(7U, 8U));
    EXPECT_TRUE(connectedComponents.isConnected(9U, 10U));
    EXPECT_TRUE(connectedComponents.isConnected(9U, 11U));
    EXPECT_TRUE(connectedComponents.isConnected(9U, 12U));
}


//DirectedGraph

template <typename ConnectedComponent, typename Graph>
void testGetNumberOfComponentIdsWhenEmptyWithVertexAsUnsignedIntWithDirectedGraph()
{
    Graph graph;
    ConnectedComponent connectedComponents(graph);

    EXPECT_EQ(0U, connectedComponents.getNumberOfComponentIds());
}

template <typename ConnectedComponent, typename Graph>
void testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsUnsignedIntWithDirectedGraph()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(3U, 0U);
    graph.connect(4U, 5U);
    graph.connect(5U, 4U);
    graph.connect(6U, 7U);
    graph.connect(7U, 6U);
    ConnectedComponent connectedComponents(graph);

    EXPECT_EQ(3U, connectedComponents.getNumberOfComponentIds());
}

template <typename ConnectedComponent, typename Graph>
void testIsConnectedWhenEmptyWithVertexAsUnsignedIntWithDirectedGraph()
{
    Graph graph;
    ConnectedComponent connectedComponents(graph);

    EXPECT_FALSE(connectedComponents.isConnected(0U, 1U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 2U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 3U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 4U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 5U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 6U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 7U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 8U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 9U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 10U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 11U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 12U));
}

template <typename ConnectedComponent, typename Graph>
void testIsConnectedWhenNotEmptyWithVertexAsUnsignedIntWithDirectedGraph()
{
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
    ConnectedComponent connectedComponents(graph);

    EXPECT_FALSE(connectedComponents.isConnected(0U, 1U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 6U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 7U));
    EXPECT_FALSE(connectedComponents.isConnected(0U, 9U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 2U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 3U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 4U));
    EXPECT_TRUE(connectedComponents.isConnected(0U, 5U));
    EXPECT_TRUE(connectedComponents.isConnected(6U, 8U));
    EXPECT_TRUE(connectedComponents.isConnected(9U, 10U));
    EXPECT_TRUE(connectedComponents.isConnected(9U, 11U));
    EXPECT_TRUE(connectedComponents.isConnected(9U, 12U));
}

}

}

}
