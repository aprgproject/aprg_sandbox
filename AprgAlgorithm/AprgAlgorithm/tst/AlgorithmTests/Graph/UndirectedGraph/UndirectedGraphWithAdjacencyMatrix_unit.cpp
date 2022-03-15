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
using GraphForTest = UndirectedGraphWithAdjacencyMatrix<unsigned int, 13>;
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, HasAnyConnectionWorksWhenEmpty)
{
    performHasAnyConnectionOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, HasAnyConnectionWorksWhenNotEmpty)
{
    performHasAnyConnectionOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenEmpty)
{
    performIsConnectedOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenNotEmpty)
{
    performIsConnectedOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenEmpty)
{
    performGetNumberOfVerticesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    performGetNumberOfVerticesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenEmpty)
{
    performGetNumberOfEdgesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    performGetNumberOfEdgesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenEmpty)
{
    performGetVerticesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenNotEmpty)
{
    performGetVerticesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenEmpty)
{
    performGetEdgesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenNotEmpty)
{
    performGetEdgesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, ConnectWorks)
{
    performConnectOnUnsignedIntVertexTest<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, DisonnectWorks)
{
    performDisconnectOnUnsignedIntVertexTest<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, ComplicatedTestWorks)
{
    performUnsignedIntVertexComplicatedTest<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetDisplayableStringWorks)
{
    UndirectedGraphWithAdjacencyMatrix<unsigned int, 3> graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    EXPECT_EQ("Adjacency Matrix output:\n-----------------\n| X |[0]|[1]|[2]|\n-----------------\n|[0]| 0 | 1 | 1 |\n-----------------\n"
              "|[1]| 1 | 0 | 0 |\n-----------------\n|[2]| 1 | 0 | 0 |\n-----------------\n",
              graph.getDisplayableString());}

}

}
