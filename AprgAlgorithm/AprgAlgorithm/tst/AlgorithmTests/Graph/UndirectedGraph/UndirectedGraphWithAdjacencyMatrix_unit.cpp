#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithAdjacencyMatrix.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithUndirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUndirectedGraph;

namespace alba
{

namespace algorithm
{
namespace
{
using GraphForTest = UndirectedGraphWithAdjacencyMatrix<unsigned int, 13>;
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetGraphDirectionTypeWorks)
{
    testGetGraphDirectionTypeWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, HasAnyConnectionWorksWhenEmpty)
{
    testHasAnyConnectionWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, HasAnyConnectionWorksWhenNotEmpty)
{
    testHasAnyConnectionWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenEmpty)
{
    testIsConnectedWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenNotEmpty)
{
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenEmpty)
{
    testGetNumberOfVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenEmpty)
{
    testGetNumberOfEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenEmpty)
{
    testGetVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenNotEmpty)
{
    testGetVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenEmpty)
{
    testGetEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenNotEmpty)
{
    testGetEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, ConnectWorks)
{
    testConnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, DisconnectWorks)
{
    testDisconnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, ClearWorks)
{
    testClearWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, ComplicatedTestWorks)
{
    testWithComplicatedExampleWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GraphWorksAfterClear)
{
    using Edges = typename GraphForTest::Edges;
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.clear();

    graph.connect(3U, 4U);
    graph.connect(4U, 5U);
    graph.connect(5U, 6U);

    EXPECT_EQ(4U, graph.getNumberOfVertices());
    EXPECT_EQ(3U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{3U, 4U}, {4U, 5U}, {5U, 6U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetDisplayableStringWorks)
{
    UndirectedGraphWithAdjacencyMatrix<unsigned int, 3> graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ("Adjacency Matrix output:\n-----------------\n| X |[0]|[1]|[2]|\n-----------------\n|[0]| 0 | 1 | 1 |\n-----------------\n"
              "|[1]| 1 | 0 | 0 |\n-----------------\n|[2]| 1 | 0 | 0 |\n-----------------\n",
              graph.getDisplayableString());
}

}

}
