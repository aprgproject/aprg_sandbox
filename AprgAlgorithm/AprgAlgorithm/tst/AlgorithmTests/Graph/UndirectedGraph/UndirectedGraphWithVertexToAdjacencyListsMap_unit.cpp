#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithVertexToAdjacencyListsMap.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithUndirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUndirectedGraph;

namespace alba
{
namespace algorithm
{
namespace
{
using GraphForTest = UndirectedGraphWithVertexToAdjacencyListsMap<unsigned int>;
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetGraphDirectionTypeWorks)
{
    testGetGraphDirectionTypeWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, HasAnyConnectionWorksWhenEmpty)
{
    testHasAnyConnectionWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, HasAnyConnectionWorksWhenNotEmpty)
{
    testHasAnyConnectionWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenEmpty)
{
    testIsConnectedWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenNotEmpty)
{
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenEmpty)
{
    testGetNumberOfVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenEmpty)
{
    testGetNumberOfEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenEmpty)
{
    testGetVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenNotEmpty)
{
    testGetVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenEmpty)
{
    testGetEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenNotEmpty)
{
    testGetEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ConnectWorks)
{
    testConnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, DisconnectWorks)
{
    testDisconnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ClearWorks)
{
    testClearWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ComplicatedTestWorks)
{
    testWithComplicatedExampleWithVertexAsUnsignedInt<GraphForTest>();
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
