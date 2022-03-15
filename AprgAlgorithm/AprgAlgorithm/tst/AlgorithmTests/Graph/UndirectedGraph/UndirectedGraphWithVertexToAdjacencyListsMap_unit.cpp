#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithVertexToAdjacencyListsMap.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithBaseUndirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseUndirectedGraph;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = UndirectedGraphWithVertexToAdjacencyListsMap<unsigned int>;
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, HasAnyConnectionWorksWhenEmpty)
{
    performHasAnyConnectionOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, HasAnyConnectionWorksWhenNotEmpty)
{
    performHasAnyConnectionOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenEmpty)
{
    performIsConnectedOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenNotEmpty)
{
    performIsConnectedOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenEmpty)
{
    performGetNumberOfVerticesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    performGetNumberOfVerticesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenEmpty)
{
    performGetNumberOfEdgesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    performGetNumberOfEdgesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenEmpty)
{
    performGetVerticesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenNotEmpty)
{
    performGetVerticesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenEmpty)
{
    performGetEdgesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenNotEmpty)
{
    performGetEdgesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ConnectWorks)
{
    performConnectOnUnsignedIntVertexTest<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, DisonnectWorks)
{
    performDisconnectOnUnsignedIntVertexTest<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ComplicatedTestWorks)
{
    performUnsignedIntVertexComplicatedTest<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetDisplayableStringWorks)
{
    GraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    EXPECT_EQ("Adjacency Lists: \nAdjacent with vertex 0: {1, 2, } \nAdjacent with vertex 1: {0, } \nAdjacent with vertex 2: {0, } \n", graph.getDisplayableString());
}
}

}
