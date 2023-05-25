#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/DirectedGraph/Utilities/CommonTestsWithDirectedGraph.hpp>
#include <Common/String/AlbaStringHelper.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithDirectedGraph;
using namespace alba::stringHelper;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithListOfEdges<int>;
}

TEST(DirectedGraphWithListOfEdgesTest, GetGraphDirectionTypeWorks) {
    testGetGraphDirectionTypeWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, IsEmptyWorks) { testIsEmptyWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithListOfEdgesTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenEmpty) {
    testGetNumberOfVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenNotEmpty) {
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenEmpty) {
    testGetNumberOfEdgesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenNotEmpty) {
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenEmpty) {
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenNotEmpty) {
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenEmpty) {
    testGetVerticesWhenEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenNotEmpty) {
    testGetVerticesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenEmpty) { testGetEdgesWhenEmptyWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenNotEmpty) {
    testGetEdgesWhenNotEmptyWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, ConnectWorks) { testConnectWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithListOfEdgesTest, DisconnectWorks) { testDisconnectWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithListOfEdgesTest, ClearWorks) { testClearWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithListOfEdgesTest, GraphWorksAfterClear) {
    testGraphWorksAfterClearWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, ReverseDirectionsWorks) { testReverseDirectionsWithVertexAsInt<GraphForTest>(); }

TEST(DirectedGraphWithListOfEdgesTest, ComplicatedTestWorks) {
    testWithComplicatedExampleWithVertexAsInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, OutputStreamOperatorWorks) {
    GraphForTest graph;

    graph.connect(0, 1);
    graph.connect(2, 0);

    EXPECT_EQ("Edges: {0->1, 2->0, }", convertToString(graph));
}

}  // namespace algorithm

}  // namespace alba
