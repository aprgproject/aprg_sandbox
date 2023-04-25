#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using FlowDataTypeForTest = double;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using FlowNetworkForTest = SinkSourceFlowNetwork<VertexForTest, FlowDataTypeForTest, DirectedGraphForTest>;
}  // namespace

TEST(FlowNetworkTest, IsAnStCutWorks) {
    FlowNetworkForTest graph(0U, 2U);
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(1U, 2U, 16.25, 4.5);

    EXPECT_FALSE(graph.isAnStCut({1U, 2U}, {0U, 1U}));
    EXPECT_FALSE(graph.isAnStCut({0U, 1U}, {0U, 1U}));
    EXPECT_FALSE(graph.isAnStCut({1U, 2U}, {1U, 2U}));
    EXPECT_TRUE(graph.isAnStCut({0U, 1U}, {1U, 2U}));
}

TEST(FlowNetworkTest, GetSourceVertexWorks) {
    FlowNetworkForTest graph(0U, 2U);
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(1U, 2U, 16.25, 4.5);

    EXPECT_EQ(0U, graph.getSourceVertex());
}

TEST(FlowNetworkTest, GetSinkVerteWorks) {
    FlowNetworkForTest graph(0U, 2U);
    graph.connect(0U, 1U, 15.25, 3.5);
    graph.connect(1U, 2U, 16.25, 4.5);

    EXPECT_EQ(2U, graph.getSinkVertex());
}

}  // namespace algorithm

}  // namespace alba
