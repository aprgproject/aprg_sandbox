#include <Algorithm/Graph/ConnectedComponents/StronglyConnectedComponentsUsingKosarajuSharir.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/ConnectedComponents/Utilities/CommonTestsWithConnectedComponents.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithConnectedComponents;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithListOfEdges<int>;
using ConnectedComponentsForTest = StronglyConnectedComponentsUsingKosarajuSharir<int>;
}  // namespace

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, GetNumberOfComponentIdsWorksWhenEmpty) {
    testGetNumberOfComponentIdsWhenEmptyWithVertexAsIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, GetNumberOfComponentIdsWorksWhenNotEmpty) {
    testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, GetComponentIdWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 0);
    graph.connect(4, 5);
    graph.connect(5, 4);
    graph.connect(6, 7);
    graph.connect(7, 6);
    ConnectedComponentsForTest connectedComponents(graph);

    EXPECT_EQ(3, connectedComponents.getComponentId(0));
    EXPECT_EQ(3, connectedComponents.getComponentId(1));
    EXPECT_EQ(3, connectedComponents.getComponentId(2));
    EXPECT_EQ(3, connectedComponents.getComponentId(3));
    EXPECT_EQ(2, connectedComponents.getComponentId(4));
    EXPECT_EQ(2, connectedComponents.getComponentId(5));
    EXPECT_EQ(1, connectedComponents.getComponentId(6));
    EXPECT_EQ(1, connectedComponents.getComponentId(7));
}

}  // namespace algorithm

}  // namespace alba
