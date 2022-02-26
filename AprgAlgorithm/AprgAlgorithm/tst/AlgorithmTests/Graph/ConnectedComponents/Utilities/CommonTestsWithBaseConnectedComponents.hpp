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
void performIsConnectedTestWhenEmpty()
{
    GraphType graph;
    BaseUndirectedGraph & baseGraph(graph);
    ConnectedComponentType connectedComponents(baseGraph);
    BaseConnectedComponents const& baseConnectedComponents(connectedComponents);

    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 1U));    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 2U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 3U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 4U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 5U));    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 6U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 7U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 8U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 9U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 10U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 11U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 12U));
}

template<typename ConnectedComponentType, typename GraphType>
void performIsConnectedTestWhenNotEmpty()
{
    GraphType graph;
    BaseUndirectedGraph & baseGraph(graph);
    baseGraph.connect(0U, 1U);
    baseGraph.connect(0U, 2U);
    baseGraph.connect(0U, 5U);
    baseGraph.connect(0U, 6U);
    baseGraph.connect(3U, 5U);
    baseGraph.connect(3U, 4U);
    baseGraph.connect(4U, 5U);
    baseGraph.connect(4U, 6U);
    baseGraph.connect(7U, 8U);
    baseGraph.connect(9U, 10U);
    baseGraph.connect(9U, 11U);
    baseGraph.connect(9U, 12U);
    baseGraph.connect(11U, 12U);
    ConnectedComponentType connectedComponents(baseGraph);
    BaseConnectedComponents const& baseConnectedComponents(connectedComponents);

    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 7U));    EXPECT_FALSE(baseConnectedComponents.isConnected(0U, 9U));
    EXPECT_FALSE(baseConnectedComponents.isConnected(7U, 9U));
    EXPECT_TRUE(baseConnectedComponents.isConnected(0U, 1U));
    EXPECT_TRUE(baseConnectedComponents.isConnected(0U, 2U));    EXPECT_TRUE(baseConnectedComponents.isConnected(0U, 3U));
    EXPECT_TRUE(baseConnectedComponents.isConnected(0U, 4U));
    EXPECT_TRUE(baseConnectedComponents.isConnected(0U, 5U));
    EXPECT_TRUE(baseConnectedComponents.isConnected(0U, 6U));
    EXPECT_TRUE(baseConnectedComponents.isConnected(7U, 8U));
    EXPECT_TRUE(baseConnectedComponents.isConnected(9U, 10U));
    EXPECT_TRUE(baseConnectedComponents.isConnected(9U, 11U));
    EXPECT_TRUE(baseConnectedComponents.isConnected(9U, 12U));
}

}

}

}
