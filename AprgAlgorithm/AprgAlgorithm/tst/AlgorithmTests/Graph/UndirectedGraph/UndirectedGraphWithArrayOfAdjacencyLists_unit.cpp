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
using UndirectedGraphWithArrayOfAdjacencyListsWithMax13 = UndirectedGraphWithArrayOfAdjacencyLists<13>;
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetNumberOfVerticesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetNumberOfVerticesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetNumberOfEdgesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetNumberOfEdgesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetAdjacentVerticesAtTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetAdjacentVerticesAtTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetVerticesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenNotEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetVerticesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetEdgesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenNotEmpty)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performGetEdgesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, ConnectWorks)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performConnectTest(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, DisonnectWorks)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performDisconnectTest(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, ComplicatedTestWorks)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;
    performComplicatedTest(graph);
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetDisplayableStringWorks)
{
    UndirectedGraphWithArrayOfAdjacencyListsWithMax13 graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ("Adjacency Lists: \nAdjacent with vertex 0: {1, 2, } \nAdjacent with vertex 1: {0, } \nAdjacent with vertex 2: {0, } \n", graph.getDisplayableString());
}

}

}
