#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/FlowNetwork.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using FlowDataTypeForTest = double;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using FlowNetworkForTest = FlowNetwork<VertexForTest, FlowDataTypeForTest, DirectedGraphForTest>;
using Edges = GraphTypes<VertexForTest>::Edges;
}  // namespace

TEST(FlowNetworkTest, HasAUniqueMinimumSpanningTreeWorks) {
    FlowNetworkForTest graphWithDifferentWeights;
    graphWithDifferentWeights.connect(0U, 1U, 15.25, 3.5);
    graphWithDifferentWeights.connect(0U, 2U, 16.25, 4.5);
    FlowNetworkForTest graphWithNonDifferentWeights;
    graphWithNonDifferentWeights.connect(0U, 1U, 15.25, 3.5);
    graphWithNonDifferentWeights.connect(0U, 2U, 15.25, 3.5);

    EXPECT_TRUE(graphWithDifferentWeights.hasAUniqueMinimumSpanningTree());
    EXPECT_FALSE(graphWithNonDifferentWeights.hasAUniqueMinimumSpanningTree());
}

TEST(FlowNetworkTest, HasLocalEquilibriumWorks) {
    FlowNetworkForTest graphWithNoEquilibrium;
    graphWithNoEquilibrium.connect(0U, 1U, 15.25, 3.5);
    graphWithNoEquilibrium.connect(1U, 2U, 16.25, 4.5);
    FlowNetworkForTest graphWithEquilibrium;
    graphWithEquilibrium.connect(0U, 1U, 15.25, 3.5);
    graphWithEquilibrium.connect(1U, 2U, 16.25, 3.5);

    EXPECT_FALSE(graphWithNoEquilibrium.hasLocalEquilibrium(1U));
    EXPECT_TRUE(graphWithEquilibrium.hasLocalEquilibrium(1U));
}

TEST(FlowNetworkTest, GetFlowEdgeDetailsWorks) {
    FlowNetworkForTest graph;
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(0U, 2U, 16.25, 4.5);

    FlowNetworkForTest::FlowEdgeDetails expectedDetails1{15.25, 3.5};
    FlowNetworkForTest::FlowEdgeDetails expectedDetails2{16.25, 4.5};
    EXPECT_EQ(expectedDetails1, graph.getFlowEdgeDetails(0U, 1U));
    EXPECT_EQ(expectedDetails2, graph.getFlowEdgeDetails(0U, 2U));
}

TEST(FlowNetworkTest, GetDeltaFlowAtWorks) {
    FlowNetworkForTest graph;
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(0U, 2U, 16.25, 4.5);

    EXPECT_DOUBLE_EQ(-8, graph.getDeltaFlowAt(0U));
    EXPECT_DOUBLE_EQ(3.5, graph.getDeltaFlowAt(1U));
    EXPECT_DOUBLE_EQ(4.5, graph.getDeltaFlowAt(2U));
}

TEST(FlowNetworkTest, GetSortedCapacitiesWorks) {
    FlowNetworkForTest graph;
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(0U, 2U, 16.25, 4.5);

    FlowNetworkForTest::FlowDataTypes expectedCapacities{15.25, 16.25};
    EXPECT_EQ(expectedCapacities, graph.getSortedCapacities());
}

TEST(FlowNetworkTest, GetSortedFlowsWorks) {
    FlowNetworkForTest graph;
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(0U, 2U, 16.25, 4.5);

    FlowNetworkForTest::FlowDataTypes expectedFlows{3.5, 4.5};
    EXPECT_EQ(expectedFlows, graph.getSortedFlows());
}

TEST(FlowNetworkTest, GetSortedWeightsWorks) {
    FlowNetworkForTest graph;
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(0U, 2U, 16.25, 4.5);

    FlowNetworkForTest::FlowDataTypes expectedWeights{15.25, 16.25};
    EXPECT_EQ(expectedWeights, graph.getSortedWeights());
}

TEST(FlowNetworkTest, GetEdgeToFlowEdgeDetailsMapWorks) {
    FlowNetworkForTest graph;
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(0U, 2U, 16.25, 4.5);

    FlowNetworkForTest::EdgeToFlowEdgeDetailsMap expectedEdgesToDetails{
        {{0U, 1U}, {15.25, 3.5}}, {{0U, 2U}, {16.25, 4.5}}};
    EXPECT_EQ(expectedEdgesToDetails, graph.getEdgeToFlowEdgeDetailsMap());
}

TEST(FlowNetworkTest, GetFlowEdgesWorks) {
    FlowNetworkForTest graph;
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(0U, 2U, 16.25, 4.5);

    FlowNetworkForTest::FlowEdges expectedEdgesWithWeight{{0U, 1U, 15.25, 3.5}, {0U, 2U, 16.25, 4.5}};
    EXPECT_EQ(expectedEdgesWithWeight, graph.getFlowEdges());
}

TEST(FlowNetworkTest, ConnectWorks) {
    FlowNetworkForTest graph;
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(0U, 2U, 16.25, 4.5);

    EXPECT_EQ(3U, graph.getNumberOfVertices());
    EXPECT_EQ(2U, graph.getNumberOfEdges());
    Edges edgesToExpect{{0U, 1U}, {0U, 2U}};
    FlowNetworkForTest::EdgeToFlowEdgeDetailsMap expectedEdgesToDetails{
        {{0U, 1U}, {15.25, 3.5}}, {{0U, 2U}, {16.25, 4.5}}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToDetails, graph.getEdgeToFlowEdgeDetailsMap());
}

TEST(FlowNetworkTest, DisconnectWorks) {
    FlowNetworkForTest graph;
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(0U, 2U, 16.25, 4.5);

    graph.disconnect(0U, 1U);

    EXPECT_EQ(2U, graph.getNumberOfVertices());
    EXPECT_EQ(1U, graph.getNumberOfEdges());
    Edges edgesToExpect{{0U, 2U}};
    FlowNetworkForTest::EdgeToFlowEdgeDetailsMap expectedEdgesToDetails{{{0U, 2U}, {16.25, 4.5}}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToDetails, graph.getEdgeToFlowEdgeDetailsMap());
}

}  // namespace algorithm

}  // namespace alba
