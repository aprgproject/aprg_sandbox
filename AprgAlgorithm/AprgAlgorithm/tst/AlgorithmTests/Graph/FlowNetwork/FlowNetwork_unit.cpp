#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/FlowNetwork.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using FlowDataTypeForTest = double;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using FlowNetworkForTest = FlowNetwork<VertexForTest, FlowDataTypeForTest, DirectedGraphForTest>;
using Edges = GraphTypes<VertexForTest>::Edges;
}  // namespace

TEST(FlowNetworkTest, HasAUniqueMinimumSpanningTreeWorks) {
    FlowNetworkForTest graphWithDifferentWeights;
    graphWithDifferentWeights.connect(0, 1, 15.25, 3.5);
    graphWithDifferentWeights.connect(0, 2, 16.25, 4.5);
    FlowNetworkForTest graphWithNonDifferentWeights;
    graphWithNonDifferentWeights.connect(0, 1, 15.25, 3.5);
    graphWithNonDifferentWeights.connect(0, 2, 15.25, 3.5);

    EXPECT_TRUE(graphWithDifferentWeights.hasAUniqueMinimumSpanningTree());
    EXPECT_FALSE(graphWithNonDifferentWeights.hasAUniqueMinimumSpanningTree());
}

TEST(FlowNetworkTest, HasLocalEquilibriumWorks) {
    FlowNetworkForTest graphWithNoEquilibrium;
    graphWithNoEquilibrium.connect(0, 1, 15.25, 3.5);
    graphWithNoEquilibrium.connect(1, 2, 16.25, 4.5);
    FlowNetworkForTest graphWithEquilibrium;
    graphWithEquilibrium.connect(0, 1, 15.25, 3.5);
    graphWithEquilibrium.connect(1, 2, 16.25, 3.5);

    EXPECT_FALSE(graphWithNoEquilibrium.hasLocalEquilibrium(1));
    EXPECT_TRUE(graphWithEquilibrium.hasLocalEquilibrium(1));
}

TEST(FlowNetworkTest, GetFlowEdgeDetailsWorks) {
    FlowNetworkForTest graph;
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(0, 2, 16.25, 4.5);

    FlowNetworkForTest::FlowEdgeDetails expectedDetails1{15.25, 3.5};
    FlowNetworkForTest::FlowEdgeDetails expectedDetails2{16.25, 4.5};
    EXPECT_EQ(expectedDetails1, graph.getFlowEdgeDetails(0, 1));
    EXPECT_EQ(expectedDetails2, graph.getFlowEdgeDetails(0, 2));
}

TEST(FlowNetworkTest, GetDeltaFlowAtWorks) {
    FlowNetworkForTest graph;
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(0, 2, 16.25, 4.5);

    EXPECT_DOUBLE_EQ(-8, graph.getDeltaFlowAt(0));
    EXPECT_DOUBLE_EQ(3.5, graph.getDeltaFlowAt(1));
    EXPECT_DOUBLE_EQ(4.5, graph.getDeltaFlowAt(2));
}

TEST(FlowNetworkTest, GetSortedCapacitiesWorks) {
    FlowNetworkForTest graph;
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(0, 2, 16.25, 4.5);

    FlowNetworkForTest::FlowDataTypes expectedCapacities{15.25, 16.25};
    EXPECT_EQ(expectedCapacities, graph.getSortedCapacities());
}

TEST(FlowNetworkTest, GetSortedFlowsWorks) {
    FlowNetworkForTest graph;
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(0, 2, 16.25, 4.5);

    FlowNetworkForTest::FlowDataTypes expectedFlows{3.5, 4.5};
    EXPECT_EQ(expectedFlows, graph.getSortedFlows());
}

TEST(FlowNetworkTest, GetSortedWeightsWorks) {
    FlowNetworkForTest graph;
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(0, 2, 16.25, 4.5);

    FlowNetworkForTest::FlowDataTypes expectedWeights{15.25, 16.25};
    EXPECT_EQ(expectedWeights, graph.getSortedWeights());
}

TEST(FlowNetworkTest, GetEdgeToFlowEdgeDetailsMapWorks) {
    FlowNetworkForTest graph;
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(0, 2, 16.25, 4.5);

    FlowNetworkForTest::EdgeToFlowEdgeDetailsMap expectedEdgesToDetails{{{0, 1}, {15.25, 3.5}}, {{0, 2}, {16.25, 4.5}}};
    EXPECT_EQ(expectedEdgesToDetails, graph.getEdgeToFlowEdgeDetailsMap());
}

TEST(FlowNetworkTest, GetFlowEdgesWorks) {
    FlowNetworkForTest graph;
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(0, 2, 16.25, 4.5);

    FlowNetworkForTest::FlowEdges expectedEdgesWithWeight{{0, 1, 15.25, 3.5}, {0, 2, 16.25, 4.5}};
    EXPECT_EQ(expectedEdgesWithWeight, graph.getFlowEdges());
}

TEST(FlowNetworkTest, ConnectWorks) {
    FlowNetworkForTest graph;
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(0, 2, 16.25, 4.5);

    EXPECT_EQ(3, graph.getNumberOfVertices());
    EXPECT_EQ(2, graph.getNumberOfEdges());
    Edges edgesToExpect{{0, 1}, {0, 2}};
    FlowNetworkForTest::EdgeToFlowEdgeDetailsMap expectedEdgesToDetails{{{0, 1}, {15.25, 3.5}}, {{0, 2}, {16.25, 4.5}}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToDetails, graph.getEdgeToFlowEdgeDetailsMap());
}

TEST(FlowNetworkTest, DisconnectWorks) {
    FlowNetworkForTest graph;
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(0, 2, 16.25, 4.5);

    graph.disconnect(0, 1);

    EXPECT_EQ(2, graph.getNumberOfVertices());
    EXPECT_EQ(1, graph.getNumberOfEdges());
    Edges edgesToExpect{{0, 2}};
    FlowNetworkForTest::EdgeToFlowEdgeDetailsMap expectedEdgesToDetails{{{0, 2}, {16.25, 4.5}}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToDetails, graph.getEdgeToFlowEdgeDetailsMap());
}

}  // namespace algorithm

}  // namespace alba
