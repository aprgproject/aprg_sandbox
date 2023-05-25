#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithAdjacencyMatrix.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithUndirectedGraph.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUndirectedGraph;
using namespace alba::stringHelper;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = UndirectedGraphWithAdjacencyMatrix<int, 13>;
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetGraphDirectionTypeWorks) {
    testGetGraphDirectionTypeWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, IsEmptyWorks) { testIsEmptyWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithAdjacencyMatrixTest, HasAnyConnectionWorksWhenEmpty) {
    testHasAnyConnectionWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, HasAnyConnectionWorksWhenNotEmpty) {
    testHasAnyConnectionWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenEmpty) {
    testGetNumberOfVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfVerticesWorksWhenNotEmpty) {
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenEmpty) {
    testGetNumberOfEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetNumberOfEdgesWorksWhenNotEmpty) {
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenEmpty) {
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetAdjacentVerticesAtWorksWhenNotEmpty) {
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenEmpty) {
    testGetVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetVerticesWorksWhenNotEmpty) {
    testGetVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenEmpty) {
    testGetEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, GetEdgesWorksWhenNotEmpty) {
    testGetEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, ConnectWorks) { testConnectWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithAdjacencyMatrixTest, DisconnectWorks) { testDisconnectWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithAdjacencyMatrixTest, ClearWorks) { testClearWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithAdjacencyMatrixTest, GraphWorksAfterClear) {
    testGraphWorksAfterClearWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, ComplicatedTestWorks) {
    testWithComplicatedExampleWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithAdjacencyMatrixTest, OutputStreamOperatorWorks) {
    UndirectedGraphWithAdjacencyMatrix<int, 3> graph;

    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ(
        "Adjacency Matrix output:\n-----------------\n| X |[0]|[1]|[2]|\n-----------------\n|[0]| 0 | 1 | 1 "
        "|\n-----------------\n"
        "|[1]| 1 | 0 | 0 |\n-----------------\n|[2]| 1 | 0 | 0 |\n-----------------\n",
        convertToString(graph));
}

}  // namespace algorithm

}  // namespace alba
