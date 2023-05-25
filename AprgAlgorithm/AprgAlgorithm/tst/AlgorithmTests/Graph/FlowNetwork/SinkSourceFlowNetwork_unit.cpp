#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using FlowDataTypeForTest = double;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using FlowNetworkForTest = SinkSourceFlowNetwork<VertexForTest, FlowDataTypeForTest, DirectedGraphForTest>;
}  // namespace

TEST(FlowNetworkTest, IsAnStCutWorks) {
    FlowNetworkForTest graph(0, 2);
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(1, 2, 16.25, 4.5);

    EXPECT_FALSE(graph.isAnStCut({1, 2}, {0, 1}));
    EXPECT_FALSE(graph.isAnStCut({0, 1}, {0, 1}));
    EXPECT_FALSE(graph.isAnStCut({1, 2}, {1, 2}));
    EXPECT_TRUE(graph.isAnStCut({0, 1}, {1, 2}));
}

TEST(FlowNetworkTest, GetSourceVertexWorks) {
    FlowNetworkForTest graph(0, 2);
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(1, 2, 16.25, 4.5);

    EXPECT_EQ(0, graph.getSourceVertex());
}

TEST(FlowNetworkTest, GetSinkVerteWorks) {
    FlowNetworkForTest graph(0, 2);
    graph.connect(0, 1, 15.25, 3.5);
    graph.connect(1, 2, 16.25, 4.5);

    EXPECT_EQ(2, graph.getSinkVertex());
}

}  // namespace algorithm

}  // namespace alba
