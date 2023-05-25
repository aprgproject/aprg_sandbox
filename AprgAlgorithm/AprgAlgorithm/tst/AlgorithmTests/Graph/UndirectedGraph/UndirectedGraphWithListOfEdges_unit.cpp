#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithUndirectedGraph.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithUndirectedGraph;
using namespace alba::stringHelper;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = UndirectedGraphWithListOfEdges<int>;
}

TEST(UndirectedGraphWithListOfEdgesTest, GetGraphDirectionTypeWorks) {
    testGetGraphDirectionTypeWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, IsEmptyWorks) { testIsEmptyWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithListOfEdgesTest, HasAnyConnectionWorksWhenEmpty) {
    testHasAnyConnectionWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, HasAnyConnectionWorksWhenNotEmpty) {
    testHasAnyConnectionWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenEmpty) {
    testGetNumberOfVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenNotEmpty) {
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenEmpty) {
    testGetNumberOfEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenNotEmpty) {
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenEmpty) {
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenNotEmpty) {
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenEmpty) {
    testGetVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenNotEmpty) {
    testGetVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenEmpty) {
    testGetEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenNotEmpty) {
    testGetEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, ConnectWorks) { testConnectWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithListOfEdgesTest, DisconnectWorks) { testDisconnectWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithListOfEdgesTest, ClearWorks) { testClearWithVertexAsInt<GraphForTest>(); }

TEST(UndirectedGraphWithListOfEdgesTest, GraphWorksAfterClear) {
    testGraphWorksAfterClearWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, ComplicatedTestWorks) {
    testWithComplicatedExampleWithVertexAsInt<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, OutputStreamOperatorWorks) {
    GraphForTest graph;

    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ("Edges: {0<->1, 0<->2, 1<->0, 2<->0, }", convertToString(graph));
}

}  // namespace algorithm

}  // namespace alba
