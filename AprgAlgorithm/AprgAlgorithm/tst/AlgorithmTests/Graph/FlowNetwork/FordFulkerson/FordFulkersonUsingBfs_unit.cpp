#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/FlowNetwork/FordFulkerson/FordFulkersonUsingBfs.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using FlowDataTypeForTest = double;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using FlowNetworkForTest = SinkSourceFlowNetwork<VertexForTest, FlowDataTypeForTest, DirectedGraphForTest>;
using MaxFlowForTest = FordFulkersonUsingBfs<FlowNetworkForTest>;
}

TEST(FordFulkersonUsingBfsTest, GetMaxFlowValueAndIsInMaxFlowMinCutWorks)
{
    FlowNetworkForTest flowNetwork(0, 5);
    flowNetwork.connect(0U, 1U, 2.0, 0.0);
    flowNetwork.connect(0U, 2U, 3.0, 0.0);
    flowNetwork.connect(1U, 3U, 3.0, 0.0);
    flowNetwork.connect(1U, 4U, 1.0, 0.0);
    flowNetwork.connect(2U, 3U, 1.0, 0.0);
    flowNetwork.connect(2U, 4U, 1.0, 0.0);
    flowNetwork.connect(3U, 5U, 2.0, 0.0);
    flowNetwork.connect(4U, 5U, 3.0, 0.0);
    MaxFlowForTest maxFlow(flowNetwork);

    EXPECT_EQ(4.0, maxFlow.getMaxFlowValue());
    EXPECT_TRUE(maxFlow.isInMaxFlowMinCut(0U));
    EXPECT_FALSE(maxFlow.isInMaxFlowMinCut(1U));
    EXPECT_TRUE(maxFlow.isInMaxFlowMinCut(2U));
    EXPECT_FALSE(maxFlow.isInMaxFlowMinCut(3U));
    EXPECT_FALSE(maxFlow.isInMaxFlowMinCut(4U));
    EXPECT_FALSE(maxFlow.isInMaxFlowMinCut(5U));
}

}

}
