#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/FordFulkerson/FordFulkersonUsingBfs.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using FlowDataTypeForTest = int;
using EdgesForTest = typename GraphTypes<VertexForTest>::Edges;
using PathsForTest = typename GraphTypes<VertexForTest>::Paths;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using FlowNetworkForTest = SinkSourceFlowNetwork<VertexForTest, FlowDataTypeForTest, DirectedGraphForTest>;
using MaxFlowForTest = FordFulkersonUsingBfs<FlowNetworkForTest>;
}  // namespace

TEST(FordFulkersonUsingBfsTest, GetMaxFlowValueAndIsInMaxFlowMinCutWorksOnExample1) {
    FlowNetworkForTest flowNetwork(0, 5);
    flowNetwork.connect(0, 1, 2, 0);
    flowNetwork.connect(0, 2, 3, 0);
    flowNetwork.connect(1, 3, 3, 0);
    flowNetwork.connect(1, 4, 1, 0);
    flowNetwork.connect(2, 3, 1, 0);
    flowNetwork.connect(2, 4, 1, 0);
    flowNetwork.connect(3, 5, 2, 0);
    flowNetwork.connect(4, 5, 3, 0);
    MaxFlowForTest maxFlow(flowNetwork);

    PathsForTest expectedAugmentingPaths{{0, 1, 3, 5}, {0, 2, 4, 5}, {0, 2, 3, 1, 4, 5}};
    EdgesForTest expectedMinCutEdges{{0, 1}, {2, 3}, {2, 4}};
    EXPECT_DOUBLE_EQ(4, maxFlow.getMaxFlowValue());
    EXPECT_EQ(expectedAugmentingPaths, maxFlow.getAugmentingPaths());
    EXPECT_EQ(expectedMinCutEdges, maxFlow.getMinCutEdges());
}

TEST(FordFulkersonUsingBfsTest, GetMaxFlowValueAndIsInMaxFlowMinCutWorksOnExample2) {
    FlowNetworkForTest flowNetwork(1, 6);
    flowNetwork.connect(1, 2, 5, 0);
    flowNetwork.connect(1, 4, 4, 0);
    flowNetwork.connect(2, 3, 6, 0);
    flowNetwork.connect(3, 5, 8, 0);
    flowNetwork.connect(3, 6, 6, 0);
    flowNetwork.connect(4, 2, 3, 0);
    flowNetwork.connect(4, 5, 1, 0);
    flowNetwork.connect(5, 6, 2, 0);
    MaxFlowForTest maxFlow(flowNetwork);

    PathsForTest expectedAugmentingPaths{{1, 2, 3, 6}, {1, 4, 5, 6}, {1, 4, 2, 3, 6}};
    EdgesForTest expectedMinCutEdges{{2, 3}, {4, 5}};
    EXPECT_DOUBLE_EQ(7, maxFlow.getMaxFlowValue());
    EXPECT_EQ(expectedAugmentingPaths, maxFlow.getAugmentingPaths());
    EXPECT_EQ(expectedMinCutEdges, maxFlow.getMinCutEdges());
}

}  // namespace algorithm

}  // namespace alba
