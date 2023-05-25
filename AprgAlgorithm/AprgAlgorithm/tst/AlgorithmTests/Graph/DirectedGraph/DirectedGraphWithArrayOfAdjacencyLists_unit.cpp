#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithArrayOfAdjacencyLists.hpp>
#include <AlgorithmTests/Graph/DirectedGraph/Utilities/CommonTestsWithDirectedGraph.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithDirectedGraph;
using namespace alba::stringHelper;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithArrayOfAdjacencyLists<int, 13>;
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetGraphDirectionTypeWorks) {
    testGetGraphDirectionTypeWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, IsEmptyWorks) { testIsEmptyWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenEmpty) {
    testGetNumberOfVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenNotEmpty) {
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenEmpty) {
    testGetNumberOfEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenNotEmpty) {
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenEmpty) {
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenNotEmpty) {
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenEmpty) {
    testGetVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenNotEmpty) {
    testGetVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenEmpty) {
    testGetEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenNotEmpty) {
    testGetEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, ConnectWorks) { testConnectWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, DisconnectWorks) { testDisconnectWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, ClearWorks) { testClearWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, GraphWorksAfterClear) {
    testGraphWorksAfterClearWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, ReverseDirectionsWorks) {
    testReverseDirectionsWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, ComplicatedTestWorks) {
    testWithComplicatedExampleWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithArrayOfAdjacencyListsTest, OutputStreamOperatorWorks) {
    GraphForTest graph;

    graph.connect(0, 1);
    graph.connect(2, 0);

    EXPECT_EQ(
        "Adjacency Lists: \nAdjacent with vertex 0: {1, } \nAdjacent with vertex 2: {0, } \n", convertToString(graph));
}

}  // namespace algorithm

}  // namespace alba
