#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithArrayOfAdjacencyLists.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithUndirectedGraph.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUndirectedGraph;
using namespace alba::stringHelper;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = UndirectedGraphWithArrayOfAdjacencyLists<int, 13>;
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetGraphDirectionTypeWorks) {
    testGetGraphDirectionTypeWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, IsEmptyWorks) { testIsEmptyWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, HasAnyConnectionWorksWhenEmpty) {
    testHasAnyConnectionWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, HasAnyConnectionWorksWhenNotEmpty) {
    testHasAnyConnectionWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenEmpty) {
    testGetNumberOfVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfVerticesWorksWhenNotEmpty) {
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenEmpty) {
    testGetNumberOfEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetNumberOfEdgesWorksWhenNotEmpty) {
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenEmpty) {
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetAdjacentVerticesAtWorksWhenNotEmpty) {
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenEmpty) {
    testGetVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetVerticesWorksWhenNotEmpty) {
    testGetVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenEmpty) {
    testGetEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GetEdgesWorksWhenNotEmpty) {
    testGetEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, ConnectWorks) { testConnectWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, DisconnectWorks) { testDisconnectWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, ClearWorks) { testClearWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, GraphWorksAfterClear) {
    testGraphWorksAfterClearWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, ComplicatedTestWorks) {
    testWithComplicatedExampleWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithArrayOfAdjacencyListsTest, OutputStreamOperatorWorks) {
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
