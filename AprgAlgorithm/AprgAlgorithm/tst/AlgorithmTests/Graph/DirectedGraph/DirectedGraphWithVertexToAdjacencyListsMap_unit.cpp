#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithVertexToAdjacencyListsMap.hpp>
#include <AlgorithmTests/Graph/DirectedGraph/Utilities/CommonTestsWithDirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithDirectedGraph;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = DirectedGraphWithVertexToAdjacencyListsMap<unsigned int>;
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetGraphDirectionTypeWorks)
{
    testGetGraphDirectionTypeWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, IsEmptyWorks)
{
    testIsEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenEmpty)
{
    testIsConnectedWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenNotEmpty)
{
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenEmpty)
{
    testGetNumberOfVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenEmpty)
{
    testGetNumberOfEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenEmpty)
{
    testGetVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenNotEmpty)
{
    testGetVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenEmpty)
{
    testGetEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenNotEmpty)
{
    testGetEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, ConnectWorks)
{
    testConnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, DisconnectWorks)
{
    testDisconnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, ClearWorks)
{
    testClearWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GraphWorksAfterClear)
{
    testGraphWorksAfterClearWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, ReverseDirectionsWorks)
{
    testReverseDirectionsWithVertexAsUnsignedInt<GraphForTest>();}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, ComplicatedTestWorks)
{
    testWithComplicatedExampleWithVertexAsUnsignedInt<GraphForTest>();}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetDisplayableStringWorks)
{
    GraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    EXPECT_EQ("Adjacency Lists: \nAdjacent with vertex 0: {1, } \nAdjacent with vertex 2: {0, } \n", graph.getDisplayableString());
}

}

}
