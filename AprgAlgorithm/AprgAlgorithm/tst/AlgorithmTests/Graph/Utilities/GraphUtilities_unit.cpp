#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/FlowNetwork/FlowNetwork.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace GraphUtilities
{

namespace
{
using VertexForTest = unsigned int;
using WeightForTest = double;
using FlowDataTypeForTest = double;
using EdgesForTest = typename GraphTypes<VertexForTest>::Edges;
using ListOfEdgesForTest = typename GraphTypes<VertexForTest>::ListOfEdges;
using PathForTest = typename GraphTypes<VertexForTest>::Path;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using EdgeWeightedDirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, DirectedGraphForTest>;
using FlowNetworkForTest = FlowNetwork<VertexForTest, FlowDataTypeForTest, DirectedGraphForTest>;
using SinkSourceFlowNetworkForTest = SinkSourceFlowNetwork<VertexForTest, FlowDataTypeForTest, DirectedGraphForTest>;
}

TEST(GraphUtilitiesTest, IsASimplePathWorks)
{
    PathForTest simplePath{1U, 2U, 3U};
    PathForTest nonSimplePath{1U, 2U, 3U, 2U, 4U};

    EXPECT_TRUE(isASimplePath<VertexForTest>(simplePath));
    EXPECT_FALSE(isASimplePath<VertexForTest>(nonSimplePath));
}

TEST(GraphUtilitiesTest, IsACycleWorks)
{
    PathForTest cyclePath{1U, 2U, 3U, 1U};
    PathForTest nonCyclePath{1U, 2U, 3U, 1U, 4U};

    EXPECT_TRUE(isACycle<VertexForTest>(cyclePath));
    EXPECT_FALSE(isACycle<VertexForTest>(nonCyclePath));
}

TEST(GraphUtilitiesTest, IsASimpleCycleWorks)
{
    PathForTest cycleSimplePath{1U, 2U, 3U, 1U};
    PathForTest nonCycleSimplePath{1U, 2U, 3U, 2U, 1U};

    EXPECT_TRUE(isASimpleCycle<VertexForTest>(cycleSimplePath));
    EXPECT_FALSE(isASimpleCycle<VertexForTest>(nonCycleSimplePath));
}

TEST(GraphUtilitiesTest, IsDirectedAcyclicGraphWorks)
{
    UndirectedGraphForTest undirectedGraph;
    undirectedGraph.connect(0U, 1U);
    undirectedGraph.connect(1U, 2U);
    undirectedGraph.connect(2U, 0U);
    DirectedGraphForTest graphWithCycle;
    graphWithCycle.connect(0U, 1U);
    graphWithCycle.connect(1U, 2U);
    graphWithCycle.connect(2U, 0U);
    DirectedGraphForTest graphWithoutCycle;
    graphWithoutCycle.connect(0U, 1U);
    graphWithoutCycle.connect(0U, 2U);
    graphWithoutCycle.connect(0U, 3U);

    EXPECT_FALSE(isDirectedAcyclicGraph(undirectedGraph));
    EXPECT_FALSE(isDirectedAcyclicGraph(graphWithCycle));
    EXPECT_TRUE(isDirectedAcyclicGraph(graphWithoutCycle));
}

TEST(GraphUtilitiesTest, IsDirectedSuccessorGraphWorks)
{
    UndirectedGraphForTest undirectedGraph;
    undirectedGraph.connect(0U, 1U);
    undirectedGraph.connect(1U, 2U);
    undirectedGraph.connect(2U, 0U);
    DirectedGraphForTest graphWithMaxDegreeNot1;
    graphWithMaxDegreeNot1.connect(0U, 1U);
    graphWithMaxDegreeNot1.connect(0U, 2U);
    graphWithMaxDegreeNot1.connect(2U, 3U);
    DirectedGraphForTest graphWithMaxDegree1;
    graphWithMaxDegree1.connect(0U, 1U);
    graphWithMaxDegree1.connect(1U, 2U);
    graphWithMaxDegree1.connect(2U, 3U);

    EXPECT_FALSE(isDirectedSuccessorGraph(undirectedGraph));
    EXPECT_FALSE(isDirectedSuccessorGraph(graphWithMaxDegreeNot1));
    EXPECT_TRUE(isDirectedSuccessorGraph(graphWithMaxDegree1));
}

TEST(GraphUtilitiesTest, HasAnyCyclesOnGraphWorks)
{
    UndirectedGraphForTest graphWithoutCycle;
    graphWithoutCycle.connect(0U, 1U);
    graphWithoutCycle.connect(0U, 2U);
    graphWithoutCycle.connect(0U, 3U);
    UndirectedGraphForTest graphWithCycle;
    graphWithCycle.connect(0U, 1U);
    graphWithCycle.connect(1U, 2U);
    graphWithCycle.connect(2U, 0U);

    EXPECT_FALSE(hasAnyCyclesOnGraph(graphWithoutCycle));
    EXPECT_TRUE(hasAnyCyclesOnGraph(graphWithCycle));
}

TEST(GraphUtilitiesTest, IsARegularGraphWorks)
{
    UndirectedGraphForTest nonRegularGraph;
    nonRegularGraph.connect(0U, 1U);
    nonRegularGraph.connect(0U, 2U);
    UndirectedGraphForTest regularGraph;
    regularGraph.connect(0U, 1U);
    regularGraph.connect(0U, 2U);
    regularGraph.connect(1U, 2U);

    EXPECT_FALSE(isARegularGraph(nonRegularGraph));
    EXPECT_TRUE(isARegularGraph(regularGraph));
}

TEST(GraphUtilitiesTest, IsACompleteGraphWorks)
{
    UndirectedGraphForTest nonCompleteGraph;
    nonCompleteGraph.connect(0U, 1U);
    nonCompleteGraph.connect(0U, 2U);
    UndirectedGraphForTest completeGraph;
    completeGraph.connect(0U, 1U);
    completeGraph.connect(0U, 2U);
    completeGraph.connect(1U, 2U);

    EXPECT_FALSE(isACompleteGraph(nonCompleteGraph));
    EXPECT_TRUE(isACompleteGraph(completeGraph));
}

TEST(GraphUtilitiesTest, IsASimpleGraphWorks)
{
    UndirectedGraphForTest nonCompleteGraph;
    nonCompleteGraph.connect(0U, 1U);
    nonCompleteGraph.connect(0U, 2U);
    nonCompleteGraph.connect(0U, 0U);
    UndirectedGraphForTest completeGraph;
    completeGraph.connect(0U, 1U);
    completeGraph.connect(0U, 2U);

    EXPECT_FALSE(isASimpleGraph(nonCompleteGraph));
    EXPECT_TRUE(isASimpleGraph(completeGraph));
}

TEST(GraphUtilitiesTest, IsATreeWorks)
{
    UndirectedGraphForTest treeGraph;
    treeGraph.connect(0U, 1U);
    treeGraph.connect(0U, 2U);
    treeGraph.connect(0U, 3U);
    UndirectedGraphForTest nonTreeGraphWithCycle;
    nonTreeGraphWithCycle.connect(0U, 1U);
    nonTreeGraphWithCycle.connect(1U, 2U);
    nonTreeGraphWithCycle.connect(2U, 0U);
    UndirectedGraphForTest nonTreeGraphAndItsNotConnected;
    nonTreeGraphAndItsNotConnected.connect(0U, 1U);
    nonTreeGraphAndItsNotConnected.connect(0U, 2U);
    nonTreeGraphAndItsNotConnected.connect(3U, 4U);

    EXPECT_TRUE(isATree(treeGraph));
    EXPECT_FALSE(isATree(nonTreeGraphWithCycle));
    EXPECT_FALSE(isATree(nonTreeGraphAndItsNotConnected));
}

TEST(GraphUtilitiesTest, IsAForestWorks)
{
    UndirectedGraphForTest forestGraph;
    forestGraph.connect(0U, 1U);
    forestGraph.connect(0U, 2U);
    forestGraph.connect(3U, 4U);
    UndirectedGraphForTest nonForestGraphButTree;
    nonForestGraphButTree.connect(0U, 1U);
    nonForestGraphButTree.connect(0U, 2U);
    nonForestGraphButTree.connect(0U, 3U);
    UndirectedGraphForTest nonForestGraphGraphWithCycle;
    nonForestGraphGraphWithCycle.connect(0U, 1U);
    nonForestGraphGraphWithCycle.connect(1U, 2U);
    nonForestGraphGraphWithCycle.connect(2U, 0U);

    EXPECT_TRUE(isAForest(forestGraph));
    EXPECT_FALSE(isAForest(nonForestGraphButTree));
    EXPECT_FALSE(isAForest(nonForestGraphGraphWithCycle));
}

TEST(GraphUtilitiesTest, AreAllDegreesWorks)
{
    UndirectedGraphForTest graphWithVaryingDegrees;
    graphWithVaryingDegrees.connect(0U, 1U);
    graphWithVaryingDegrees.connect(0U, 2U);
    graphWithVaryingDegrees.connect(0U, 3U);
    UndirectedGraphForTest graphWithSameDegree;
    graphWithSameDegree.connect(0U, 1U);
    graphWithSameDegree.connect(1U, 2U);
    graphWithSameDegree.connect(2U, 0U);

    EXPECT_FALSE(areAllDegrees(graphWithVaryingDegrees, 3U));
    EXPECT_TRUE(areAllDegrees(graphWithSameDegree, 2U));
}

TEST(GraphUtilitiesTest, IsASpanningTreeWorks)
{
    UndirectedGraphForTest mainGraph;
    mainGraph.connect(0U, 1U);
    mainGraph.connect(0U, 3U);
    mainGraph.connect(1U, 2U);
    mainGraph.connect(2U, 3U);
    UndirectedGraphForTest spanningTree;
    spanningTree.connect(0U, 1U);
    spanningTree.connect(0U, 2U);
    spanningTree.connect(0U, 3U);
    UndirectedGraphForTest nonSpanningTree;
    nonSpanningTree.connect(0U, 1U);
    nonSpanningTree.connect(0U, 2U);
    nonSpanningTree.connect(0U, 9U);

    EXPECT_TRUE(isASpanningTree(mainGraph, spanningTree));
    EXPECT_FALSE(isASpanningTree(mainGraph, nonSpanningTree));
}

TEST(GraphUtilitiesTest, IsASpanningForestWorks)
{
    UndirectedGraphForTest mainGraph;
    mainGraph.connect(0U, 1U);
    mainGraph.connect(0U, 3U);
    mainGraph.connect(1U, 2U);
    mainGraph.connect(2U, 3U);
    UndirectedGraphForTest spanningForest;
    spanningForest.connect(0U, 1U);
    spanningForest.connect(2U, 3U);
    UndirectedGraphForTest nonSpanningForest;
    nonSpanningForest.connect(0U, 1U);
    nonSpanningForest.connect(2U, 9U);

    EXPECT_TRUE(isASpanningForest(mainGraph, spanningForest));
    EXPECT_FALSE(isASpanningForest(mainGraph, nonSpanningForest));
}

TEST(GraphUtilitiesTest, IsGraphConnectedWorksForUndirectedGraphs)
{
    UndirectedGraphForTest connectedGraph;
    connectedGraph.connect(0U, 1U);
    connectedGraph.connect(0U, 2U);
    connectedGraph.connect(0U, 3U);
    UndirectedGraphForTest nonConnectedGraph;
    nonConnectedGraph.connect(0U, 1U);
    nonConnectedGraph.connect(0U, 2U);
    nonConnectedGraph.connect(3U, 4U);

    EXPECT_TRUE(isGraphConnected(connectedGraph));
    EXPECT_FALSE(isGraphConnected(nonConnectedGraph));
}

TEST(GraphUtilitiesTest, IsGraphConnectedWorksForDirectedGraphs)
{
    DirectedGraphForTest stronglyConnectedGraph;
    stronglyConnectedGraph.connect(0U, 1U);
    stronglyConnectedGraph.connect(1U, 2U);
    stronglyConnectedGraph.connect(2U, 3U);
    stronglyConnectedGraph.connect(3U, 0U);
    DirectedGraphForTest nonStronglyConnectedGraph;
    stronglyConnectedGraph.connect(0U, 1U);
    stronglyConnectedGraph.connect(0U, 2U);
    stronglyConnectedGraph.connect(0U, 3U);

    EXPECT_TRUE(isGraphConnected(stronglyConnectedGraph));
    EXPECT_FALSE(isGraphConnected(nonStronglyConnectedGraph));
}

TEST(GraphUtilitiesTest, IsGraphStronglyConnectedWorks)
{
    DirectedGraphForTest stronglyConnectedGraph;
    stronglyConnectedGraph.connect(0U, 1U);
    stronglyConnectedGraph.connect(1U, 2U);
    stronglyConnectedGraph.connect(2U, 3U);
    stronglyConnectedGraph.connect(3U, 0U);
    DirectedGraphForTest nonStronglyConnectedGraph;
    stronglyConnectedGraph.connect(0U, 1U);
    stronglyConnectedGraph.connect(0U, 2U);
    stronglyConnectedGraph.connect(0U, 3U);

    EXPECT_TRUE(isGraphStronglyConnected(stronglyConnectedGraph));
    EXPECT_FALSE(isGraphStronglyConnected(nonStronglyConnectedGraph));
}

TEST(GraphUtilitiesTest, IsBipartiteWorks)
{
    UndirectedGraphForTest bipartiteGraph;
    bipartiteGraph.connect(0U, 1U);
    bipartiteGraph.connect(0U, 2U);
    bipartiteGraph.connect(0U, 3U);
    bipartiteGraph.connect(3U, 4U);
    bipartiteGraph.connect(3U, 6U);
    bipartiteGraph.connect(4U, 5U);
    bipartiteGraph.connect(5U, 6U);
    UndirectedGraphForTest nonBipartiteGraph;
    nonBipartiteGraph.connect(0U, 1U);
    nonBipartiteGraph.connect(0U, 2U);
    nonBipartiteGraph.connect(0U, 3U);
    nonBipartiteGraph.connect(3U, 4U);
    nonBipartiteGraph.connect(3U, 5U);
    nonBipartiteGraph.connect(4U, 5U);

    EXPECT_TRUE(isBipartite(bipartiteGraph));
    EXPECT_FALSE(isBipartite(nonBipartiteGraph));
}

TEST(GraphUtilitiesTest, IsFlowNetworkWorks)
{
    EdgeWeightedUndirectedGraphForTest undirectedGraph;
    undirectedGraph.connect(0U, 1U, 3.5);
    undirectedGraph.connect(0U, 1U, 4.5);
    EdgeWeightedDirectedGraphForTest directedGraphWithNegativeWeight;
    directedGraphWithNegativeWeight.connect(0U, 1U, 3.5);
    directedGraphWithNegativeWeight.connect(0U, 1U, -4.5);
    EdgeWeightedDirectedGraphForTest directedGraphWithPositiveWeight;
    directedGraphWithPositiveWeight.connect(0U, 1U, 3.5);
    directedGraphWithPositiveWeight.connect(0U, 1U, 4.5);
    FlowNetworkForTest flowNetwork;
    flowNetwork.connect(0U, 1U, 15.25, 3.5);
    flowNetwork.connect(0U, 2U, 16.25, 4.5);

    EXPECT_FALSE(isFlowNetwork(undirectedGraph));
    EXPECT_FALSE(isFlowNetwork(directedGraphWithNegativeWeight));
    EXPECT_TRUE(isFlowNetwork(directedGraphWithPositiveWeight));
    EXPECT_TRUE(isFlowNetwork(flowNetwork));
}

TEST(GraphUtilitiesTest, IsSinkSourceFlowNetworkFeasibleWorks)
{
    SinkSourceFlowNetworkForTest flowNetworkWithOutOfRangeFlows(0U, 2U);
    flowNetworkWithOutOfRangeFlows.connect(0U, 1U, 15.25, 16);
    flowNetworkWithOutOfRangeFlows.connect(1U, 2U, 16.25, -1);
    SinkSourceFlowNetworkForTest flowNetworkWithNoEquilbrium(0U, 2U);
    flowNetworkWithNoEquilbrium.connect(0U, 1U, 15.25, 3.5);
    flowNetworkWithNoEquilbrium.connect(1U, 2U, 16.25, 4.5);
    SinkSourceFlowNetworkForTest flowNetworkWithEquilbrium(0U, 2U);
    flowNetworkWithEquilbrium.connect(0U, 1U, 15.25, 3.5);
    flowNetworkWithEquilbrium.connect(1U, 2U, 16.25, 3.5);

    EXPECT_FALSE(isSinkSourceFlowNetworkFeasible(flowNetworkWithOutOfRangeFlows));
    EXPECT_FALSE(isSinkSourceFlowNetworkFeasible(flowNetworkWithNoEquilbrium));
    EXPECT_TRUE(isSinkSourceFlowNetworkFeasible(flowNetworkWithEquilbrium));
}

TEST(GraphUtilitiesTest, GetLengthOfPathWorks)
{
    PathForTest emptyPath;
    PathForTest nonEmptyPath{1U, 2U, 3U};

    EXPECT_EQ(0U, getLengthOfPath<VertexForTest>(emptyPath));
    EXPECT_EQ(2U, getLengthOfPath<VertexForTest>(nonEmptyPath));
}

TEST(GraphUtilitiesTest, GetDegreeAtWorks)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, getDegreeAt(graph, 0U));
    EXPECT_EQ(1U, getDegreeAt(graph, 1U));
    EXPECT_EQ(1U, getDegreeAt(graph, 2U));
}

TEST(GraphUtilitiesTest, GetMaxDegreeAtWorks)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, getMaxDegree(graph));
}

TEST(GraphUtilitiesTest, GetSumOfDegreesAtWorks)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(4U, getSumOfDegrees(graph));
}

TEST(GraphUtilitiesTest, GetAverageDegreeWorks)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);

    EXPECT_EQ(1.5, getAverageDegree(graph));
}

TEST(GraphUtilitiesTest, GetNumberOfSelfLoopsWorks)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    graph.connect(1U, 1U);
    graph.connect(2U, 2U);

    EXPECT_EQ(2U, getNumberOfSelfLoops(graph));
}

TEST(GraphUtilitiesTest, GetDiameterOfATreeWorks)
{
    UndirectedGraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(2U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 7U);

    EXPECT_EQ(4U, getDiameterOfATree(graph));
}

TEST(GraphUtilitiesTest, GetInDegreeAndOutDegreeAtWorks)
{
    DirectedGraphForTest graph;
    graph.connect(0U, 1U);    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    graph.connect(4U, 0U);

    auto inDegreeAndOutDegreePair(getInDegreeAndOutDegreeAt<VertexForTest>(graph, 0U));

    EXPECT_EQ(3U, inDegreeAndOutDegreePair.first);
    EXPECT_EQ(1U, inDegreeAndOutDegreePair.second);
}

TEST(GraphUtilitiesTest, GetAllInDegreesAndOutDegreesAtWorks)
{
    DirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(3U, 0U);

    auto vertexToInDegreeAndOutDegreePairMap(getAllInDegreesAndOutDegrees<VertexForTest>(graph));

    EXPECT_EQ(2U, vertexToInDegreeAndOutDegreePairMap.at(0U).first);
    EXPECT_EQ(1U, vertexToInDegreeAndOutDegreePairMap.at(0U).second);
    EXPECT_EQ(0U, vertexToInDegreeAndOutDegreePairMap.at(1U).first);
    EXPECT_EQ(1U, vertexToInDegreeAndOutDegreePairMap.at(1U).second);
    EXPECT_EQ(0U, vertexToInDegreeAndOutDegreePairMap.at(2U).first);
    EXPECT_EQ(1U, vertexToInDegreeAndOutDegreePairMap.at(2U).second);
    EXPECT_EQ(1U, vertexToInDegreeAndOutDegreePairMap.at(3U).first);
    EXPECT_EQ(0U, vertexToInDegreeAndOutDegreePairMap.at(3U).second);
}

TEST(GraphUtilitiesTest, GetEdgesOfMaximalConnectedSubgraphsWorks)
{
    UndirectedGraphForTest graph;    graph.connect(0U, 5U);
    graph.connect(4U, 3U);
    graph.connect(0U, 1U);
    graph.connect(9U, 12U);
    graph.connect(6U, 4U);
    graph.connect(5U, 4U);
    graph.connect(0U, 2U);
    graph.connect(11U, 12U);
    graph.connect(9U, 10U);
    graph.connect(0U, 6U);
    graph.connect(7U, 8U);
    graph.connect(9U, 11U);
    graph.connect(5U, 3U);

    ListOfEdgesForTest listOfEdgesToVerify(getEdgesOfMaximalConnectedSubgraphs(graph));

    ListOfEdgesForTest listOfEdgesToExpect;
    listOfEdgesToExpect.emplace_back(EdgesForTest{{0, 1}, {0, 2}, {0, 5}, {0, 6}, {3, 4}, {3, 5}, {4, 5}, {4, 6}});
    listOfEdgesToExpect.emplace_back(EdgesForTest{{7, 8}});
    listOfEdgesToExpect.emplace_back(EdgesForTest{{9, 10}, {9, 11}, {9, 12}, {11, 12}});
    EXPECT_EQ(listOfEdgesToExpect, listOfEdgesToVerify);
}

}

}

}
