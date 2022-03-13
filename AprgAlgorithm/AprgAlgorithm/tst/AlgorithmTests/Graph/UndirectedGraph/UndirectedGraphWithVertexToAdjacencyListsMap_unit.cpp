#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithVertexToAdjacencyListsMap.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithBaseUndirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseUndirectedGraph;

namespace alba
{

namespace algorithm
{

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetNumberOfVerticesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetNumberOfVerticesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetNumberOfEdgesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetNumberOfEdgesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetAdjacentVerticesAtTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetAdjacentVerticesAtTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetVerticesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenNotEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetVerticesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetEdgesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenNotEmpty)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performGetEdgesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ConnectWorks)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performConnectTest(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, DisonnectWorks)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performDisconnectTest(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ComplicatedTestWorks)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;
    performComplicatedTest(graph);
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetDisplayableStringWorks)
{
    UndirectedGraphWithVertexToAdjacencyListsMap graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ("Adjacency Lists: \nAdjacent with vertex 0: {1, 2, } \nAdjacent with vertex 1: {0, } \nAdjacent with vertex 2: {0, } \n", graph.getDisplayableString());
}

}

}
