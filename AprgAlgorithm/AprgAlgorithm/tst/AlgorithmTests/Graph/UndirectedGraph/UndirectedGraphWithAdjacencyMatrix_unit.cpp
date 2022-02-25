#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithAdjacencyMatrix.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithBaseUndirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseUndirectedGraph;

namespace alba
{

namespace algorithm
{

namespace
{
using UndirectedGraphWithAdjacencyMatrixWithMax13 = UndirectedGraphWithAdjacencyMatrix<13>;
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetNumberOfVerticesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetNumberOfVerticesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetNumberOfEdgesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetNumberOfEdgesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetAdjacentVerticesAtTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetAdjacentVerticesAtTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetVerticesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenNotEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetVerticesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetEdgesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenNotEmpty)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performGetEdgesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, ConnectWorks)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performConnectTest(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, DisonnectWorks)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performDisconnectTest(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, ComplicatedTestWorks)
{
    UndirectedGraphWithAdjacencyMatrixWithMax13 graph;
    performComplicatedTest(graph);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetDisplayableStringWorks)
{
    UndirectedGraphWithAdjacencyMatrix<3> graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ("Adjacency Matrix output:\n-----------------\n| X |[0]|[1]|[2]|\n-----------------\n|[0]| 0 | 1 | 1 |\n-----------------\n"
              "|[1]| 1 | 0 | 0 |\n-----------------\n|[2]| 1 | 0 | 0 |\n-----------------\n",
              graph.getDisplayableString());
}

}

}
