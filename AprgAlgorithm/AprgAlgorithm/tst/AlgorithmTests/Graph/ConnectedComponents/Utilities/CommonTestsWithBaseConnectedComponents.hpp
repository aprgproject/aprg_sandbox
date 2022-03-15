#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithBaseConnectedComponents
{

template<typename ConnectedComponentType, typename GraphType>
void testIsConnectedWhenEmptyWithVertexAsUnsignedInt()
{
    GraphType graph;
    ConnectedComponentType connectedComponents(graph);

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

template<typename ConnectedComponentType, typename GraphType>
void testIsConnectedWhenNotEmptyWithVertexAsUnsignedInt()
{
    GraphType graph;
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
    ConnectedComponentType connectedComponents(graph);

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

}

}

}
