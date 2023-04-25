#include <Algorithm/Graph/ConnectedComponents/StronglyConnectedComponentsUsingKosarajuSharir.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/ConnectedComponents/Utilities/CommonTestsWithConnectedComponents.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithConnectedComponents;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = DirectedGraphWithListOfEdges<unsigned int>;
using ConnectedComponentsForTest = StronglyConnectedComponentsUsingKosarajuSharir<unsigned int>;
}  // namespace

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, GetNumberOfComponentIdsWorksWhenEmpty) {
    testGetNumberOfComponentIdsWhenEmptyWithVertexAsUnsignedIntWithDirectedGraph<
        ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, GetNumberOfComponentIdsWorksWhenNotEmpty) {
    testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsUnsignedIntWithDirectedGraph<
        ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsUnsignedIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, GetComponentIdWorks) {
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(3U, 0U);
    graph.connect(4U, 5U);
    graph.connect(5U, 4U);
    graph.connect(6U, 7U);
    graph.connect(7U, 6U);
    ConnectedComponentsForTest connectedComponents(graph);

    EXPECT_EQ(3U, connectedComponents.getComponentId(0U));
    EXPECT_EQ(3U, connectedComponents.getComponentId(1U));
    EXPECT_EQ(3U, connectedComponents.getComponentId(2U));
    EXPECT_EQ(3U, connectedComponents.getComponentId(3U));
    EXPECT_EQ(2U, connectedComponents.getComponentId(4U));
    EXPECT_EQ(2U, connectedComponents.getComponentId(5U));
    EXPECT_EQ(1U, connectedComponents.getComponentId(6U));
    EXPECT_EQ(1U, connectedComponents.getComponentId(7U));
}

}  // namespace algorithm

}  // namespace alba
