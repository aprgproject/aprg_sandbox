#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithAdjacencyMatrix.hpp>
#include <AlgorithmTests/Graph/DirectedGraph/Utilities/CommonTestsWithDirectedGraph.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithDirectedGraph;
using namespace alba::stringHelper;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = DirectedGraphWithAdjacencyMatrix<unsigned int, 13>;
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetGraphDirectionTypeWorks)
{
    testGetGraphDirectionTypeWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, IsEmptyWorks)
{
    testIsEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenEmpty)
{
    testIsConnectedWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenNotEmpty)
{
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenEmpty)
{
    testGetNumberOfVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenEmpty)
{
    testGetNumberOfEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenEmpty)
{
    testGetVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenNotEmpty)
{
    testGetVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenEmpty)
{
    testGetEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenNotEmpty)
{
    testGetEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, ConnectWorks)
{
    testConnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, DisconnectWorks)
{
    testDisconnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, ClearWorks)
{
    testClearWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GraphWorksAfterClear)
{
    testGraphWorksAfterClearWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, ReverseDirectionsWorks)
{
    testReverseDirectionsWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, ComplicatedTestWorks)
{
    testWithComplicatedExampleWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, OutputStreamOperatorWorks)
{
    GraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    EXPECT_EQ("Adjacency Matrix output:\n-------------------------------------------------------------\n"
              "| X  |[0]|[1]|[2]|[3]|[4]|[5]|[6]|[7]|[8]|[9]|[10]|[11]|[12]|\n"
              "-------------------------------------------------------------\n"
              "|[0] | 0 | 0 | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[1] | 1 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[2] | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[3] | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[4] | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[5] | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[6] | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[7] | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[8] | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[9] | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[10]| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[11]| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              "|[12]| 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0 | 0  | 0  | 0  |\n"
              "-------------------------------------------------------------\n"
              , convertToString(graph));
}

}

}
