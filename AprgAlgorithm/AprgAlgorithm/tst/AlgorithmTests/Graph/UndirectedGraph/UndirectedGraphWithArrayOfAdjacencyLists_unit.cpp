#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithArrayOfAdjacencyLists.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithBaseUndirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseUndirectedGraph;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = UndirectedGraphWithArrayOfAdjacencyLists<unsigned int, 13>;
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, HasAnyConnectionWorksWhenEmpty)
{
    performHasAnyConnectionOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, HasAnyConnectionWorksWhenNotEmpty)
{
    performHasAnyConnectionOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, IsConnectedWorksWhenEmpty)
{
    performIsConnectedOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, IsConnectedWorksWhenNotEmpty)
{
    performIsConnectedOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenEmpty)
{
    performGetNumberOfVerticesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    performGetNumberOfVerticesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenEmpty)
{
    performGetNumberOfEdgesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    performGetNumberOfEdgesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenEmpty)
{
    performGetVerticesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenNotEmpty)
{
    performGetVerticesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenEmpty)
{
    performGetEdgesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenNotEmpty)
{
    performGetEdgesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, ConnectWorks)
{
    performConnectOnUnsignedIntVertexTest<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, DisonnectWorks)
{
    performDisconnectOnUnsignedIntVertexTest<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, ComplicatedTestWorks)
{
    performUnsignedIntVertexComplicatedTest<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetDisplayableStringWorks)
{
    GraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    EXPECT_EQ("Adjacency Lists: \nAdjacent with vertex 0: {1, 2, } \nAdjacent with vertex 1: {0, } \nAdjacent with vertex 2: {0, } \n", graph.getDisplayableString());
}
}

}
