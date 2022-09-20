#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithArrayOfAdjacencyLists.hpp>
#include <AlgorithmTests/Graph/DirectedGraph/Utilities/CommonTestsWithDirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithDirectedGraph;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = DirectedGraphWithArrayOfAdjacencyLists<unsigned int, 13>;
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetGraphDirectionTypeWorks)
{
    testGetGraphDirectionTypeWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, IsEmptyWorks)
{
    testIsEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, IsConnectedWorksWhenEmpty)
{
    testIsConnectedWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, IsConnectedWorksWhenNotEmpty)
{
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenEmpty)
{
    testGetNumberOfVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenEmpty)
{
    testGetNumberOfEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenEmpty)
{
    testGetVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenNotEmpty)
{
    testGetVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenEmpty)
{
    testGetEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenNotEmpty)
{
    testGetEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, ConnectWorks)
{
    testConnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, DisconnectWorks)
{
    testDisconnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, ClearWorks)
{
    testClearWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GraphWorksAfterClear)
{
    testGraphWorksAfterClearWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, ReverseDirectionsWorks)
{
    testReverseDirectionsWithVertexAsUnsignedInt<GraphForTest>();}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, ComplicatedTestWorks)
{
    testWithComplicatedExampleWithVertexAsUnsignedInt<GraphForTest>();}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetDisplayableStringWorks)
{
    GraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    EXPECT_EQ("Adjacency Lists: \nAdjacent with vertex 0: {1, } \nAdjacent with vertex 2: {0, } \n", graph.getDisplayableString());
}

}

}
