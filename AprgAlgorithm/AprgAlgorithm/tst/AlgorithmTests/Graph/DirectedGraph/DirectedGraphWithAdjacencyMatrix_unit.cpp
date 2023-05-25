#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithAdjacencyMatrix.hpp>
#include <AlgorithmTests/Graph/DirectedGraph/Utilities/CommonTestsWithDirectedGraph.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithDirectedGraph;
using namespace alba::stringHelper;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithAdjacencyMatrix<int, 13>;
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetGraphDirectionTypeWorks) {
    testGetGraphDirectionTypeWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, IsEmptyWorks) { testIsEmptyWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenEmpty) {
    testGetNumberOfVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenNotEmpty) {
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenEmpty) {
    testGetNumberOfEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenNotEmpty) {
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenEmpty) {
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenNotEmpty) {
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenEmpty) {
    testGetVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenNotEmpty) {
    testGetVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenEmpty) {
    testGetEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenNotEmpty) {
    testGetEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, ConnectWorks) { testConnectWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithAdjacencyMatrixTest, DisconnectWorks) { testDisconnectWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithAdjacencyMatrixTest, ClearWorks) { testClearWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithAdjacencyMatrixTest, GraphWorksAfterClear) {
    testGraphWorksAfterClearWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, ReverseDirectionsWorks) {
    testReverseDirectionsWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, ComplicatedTestWorks) {
    testWithComplicatedExampleWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithAdjacencyMatrixTest, OutputStreamOperatorWorks) {
    GraphForTest graph;

    graph.connect(0, 1);
    graph.connect(2, 0);

    EXPECT_EQ(
        "Adjacency Matrix output:\n-------------------------------------------------------------\n"
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
        "-------------------------------------------------------------\n",
        convertToString(graph));
}

}  // namespace algorithm

}  // namespace alba
