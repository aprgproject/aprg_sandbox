#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithVertexToAdjacencyListsMap.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithUndirectedGraph.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUndirectedGraph;
using namespace alba::stringHelper;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = UndirectedGraphWithVertexToAdjacencyListsMap<int>;
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetGraphDirectionTypeWorks) {
    testGetGraphDirectionTypeWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, IsEmptyWorks) { testIsEmptyWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, HasAnyConnectionWorksWhenEmpty) {
    testHasAnyConnectionWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, HasAnyConnectionWorksWhenNotEmpty) {
    testHasAnyConnectionWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenEmpty) {
    testGetNumberOfVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfVerticesWorksWhenNotEmpty) {
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenEmpty) {
    testGetNumberOfEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetNumberOfEdgesWorksWhenNotEmpty) {
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenEmpty) {
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetAdjacentVerticesAtWorksWhenNotEmpty) {
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenEmpty) {
    testGetVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetVerticesWorksWhenNotEmpty) {
    testGetVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenEmpty) {
    testGetEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GetEdgesWorksWhenNotEmpty) {
    testGetEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ConnectWorks) { testConnectWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, DisconnectWorks) {
    testDisconnectWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ClearWorks) { testClearWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, GraphWorksAfterClear) {
    testGraphWorksAfterClearWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, ComplicatedTestWorks) {
    testWithComplicatedExampleWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithVertexToAdjacencyListsMapTest, OutputStreamOperatorWorks) {
    GraphForTest graph;

    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ(
        "Adjacency Lists: \nAdjacent with vertex 0: {1, 2, } \nAdjacent with vertex 1: {0, } \nAdjacent with vertex 2: "
        "{0, } \n",
        convertToString(graph));
}

}  // namespace algorithm

}  // namespace alba
