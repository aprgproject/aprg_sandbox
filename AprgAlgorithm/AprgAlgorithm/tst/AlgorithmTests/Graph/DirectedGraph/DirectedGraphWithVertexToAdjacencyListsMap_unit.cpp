#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithVertexToAdjacencyListsMap.hpp>
#include <AlgorithmTests/Graph/DirectedGraph/Utilities/CommonTestsWithDirectedGraph.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithDirectedGraph;
using namespace alba::stringHelper;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithVertexToAdjacencyListsMap<int>;
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetGraphDirectionTypeWorks) {
    testGetGraphDirectionTypeWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, IsEmptyWorks) { testIsEmptyWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenEmpty) {
    testGetNumberOfVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenNotEmpty) {
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenEmpty) {
    testGetNumberOfEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenNotEmpty) {
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenEmpty) {
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenNotEmpty) {
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenEmpty) {
    testGetVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenNotEmpty) {
    testGetVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenEmpty) {
    testGetEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenNotEmpty) {
    testGetEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, ConnectWorks) { testConnectWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, DisconnectWorks) { testDisconnectWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, ClearWorks) { testClearWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, GraphWorksAfterClear) {
    testGraphWorksAfterClearWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, ReverseDirectionsWorks) {
    testReverseDirectionsWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, ComplicatedTestWorks) {
    testWithComplicatedExampleWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithVertexToAdjacencyListsMapTest, OutputStreamOperatorWorks) {
    GraphForTest graph;

    graph.connect(0, 1);
    graph.connect(2, 0);

    EXPECT_EQ(
        "Adjacency Lists: \nAdjacent with vertex 0: {1, } \nAdjacent with vertex 2: {0, } \n", convertToString(graph));
}

}  // namespace algorithm

}  // namespace alba
