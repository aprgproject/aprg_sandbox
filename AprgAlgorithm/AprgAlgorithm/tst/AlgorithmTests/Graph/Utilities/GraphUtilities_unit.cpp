#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/FlowNetwork/FlowNetwork.hpp>
#include <Algorithm/Graph/FlowNetwork/SinkSourceFlowNetwork.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace GraphUtilities {

namespace {
using VertexForTest = int;
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
}  // namespace

TEST(GraphUtilitiesTest, IsASimplePathWorks) {
    PathForTest simplePath{1, 2, 3};
    PathForTest nonSimplePath{1, 2, 3, 2, 4};

    EXPECT_TRUE(isASimplePath<VertexForTest>(simplePath));
    EXPECT_FALSE(isASimplePath<VertexForTest>(nonSimplePath));
}

TEST(GraphUtilitiesTest, IsACycleWorks) {
    PathForTest cyclePath{1, 2, 3, 1};
    PathForTest nonCyclePath{1, 2, 3, 1, 4};

    EXPECT_TRUE(isACycle<VertexForTest>(cyclePath));
    EXPECT_FALSE(isACycle<VertexForTest>(nonCyclePath));
}

TEST(GraphUtilitiesTest, IsASimpleCycleWorks) {
    PathForTest cycleSimplePath{1, 2, 3, 1};
    PathForTest nonCycleSimplePath{1, 2, 3, 2, 1};

    EXPECT_TRUE(isASimpleCycle<VertexForTest>(cycleSimplePath));
    EXPECT_FALSE(isASimpleCycle<VertexForTest>(nonCycleSimplePath));
}

TEST(GraphUtilitiesTest, IsDirectedAcyclicGraphWorks) {
    UndirectedGraphForTest undirectedGraph;
    undirectedGraph.connect(0, 1);
    undirectedGraph.connect(1, 2);
    undirectedGraph.connect(2, 0);
    DirectedGraphForTest graphWithCycle;
    graphWithCycle.connect(0, 1);
    graphWithCycle.connect(1, 2);
    graphWithCycle.connect(2, 0);
    DirectedGraphForTest graphWithoutCycle;
    graphWithoutCycle.connect(0, 1);
    graphWithoutCycle.connect(0, 2);
    graphWithoutCycle.connect(0, 3);

    EXPECT_FALSE(isDirectedAcyclicGraph(undirectedGraph));
    EXPECT_FALSE(isDirectedAcyclicGraph(graphWithCycle));
    EXPECT_TRUE(isDirectedAcyclicGraph(graphWithoutCycle));
}

TEST(GraphUtilitiesTest, IsDirectedSuccessorGraphWorks) {
    UndirectedGraphForTest undirectedGraph;
    undirectedGraph.connect(0, 1);
    undirectedGraph.connect(1, 2);
    undirectedGraph.connect(2, 0);
    DirectedGraphForTest graphWithMaxDegreeNot1;
    graphWithMaxDegreeNot1.connect(0, 1);
    graphWithMaxDegreeNot1.connect(0, 2);
    graphWithMaxDegreeNot1.connect(2, 3);
    DirectedGraphForTest graphWithMaxDegree1;
    graphWithMaxDegree1.connect(0, 1);
    graphWithMaxDegree1.connect(1, 2);
    graphWithMaxDegree1.connect(2, 3);

    EXPECT_FALSE(isDirectedSuccessorGraph(undirectedGraph));
    EXPECT_FALSE(isDirectedSuccessorGraph(graphWithMaxDegreeNot1));
    EXPECT_TRUE(isDirectedSuccessorGraph(graphWithMaxDegree1));
}

TEST(GraphUtilitiesTest, HasAnyCyclesOnGraphWorks) {
    UndirectedGraphForTest graphWithoutCycle;
    graphWithoutCycle.connect(0, 1);
    graphWithoutCycle.connect(0, 2);
    graphWithoutCycle.connect(0, 3);
    UndirectedGraphForTest graphWithCycle;
    graphWithCycle.connect(0, 1);
    graphWithCycle.connect(1, 2);
    graphWithCycle.connect(2, 0);

    EXPECT_FALSE(hasAnyCyclesOnGraph(graphWithoutCycle));
    EXPECT_TRUE(hasAnyCyclesOnGraph(graphWithCycle));
}

TEST(GraphUtilitiesTest, IsARegularGraphWorks) {
    UndirectedGraphForTest nonRegularGraph;
    nonRegularGraph.connect(0, 1);
    nonRegularGraph.connect(0, 2);
    UndirectedGraphForTest regularGraph;
    regularGraph.connect(0, 1);
    regularGraph.connect(0, 2);
    regularGraph.connect(1, 2);

    EXPECT_FALSE(isARegularGraph(nonRegularGraph));
    EXPECT_TRUE(isARegularGraph(regularGraph));
}

TEST(GraphUtilitiesTest, IsACompleteGraphWorks) {
    UndirectedGraphForTest nonCompleteGraph;
    nonCompleteGraph.connect(0, 1);
    nonCompleteGraph.connect(0, 2);
    UndirectedGraphForTest completeGraph;
    completeGraph.connect(0, 1);
    completeGraph.connect(0, 2);
    completeGraph.connect(1, 2);

    EXPECT_FALSE(isACompleteGraph(nonCompleteGraph));
    EXPECT_TRUE(isACompleteGraph(completeGraph));
}

TEST(GraphUtilitiesTest, IsASimpleGraphWorks) {
    UndirectedGraphForTest nonCompleteGraph;
    nonCompleteGraph.connect(0, 1);
    nonCompleteGraph.connect(0, 2);
    nonCompleteGraph.connect(0, 0);
    UndirectedGraphForTest completeGraph;
    completeGraph.connect(0, 1);
    completeGraph.connect(0, 2);

    EXPECT_FALSE(isASimpleGraph(nonCompleteGraph));
    EXPECT_TRUE(isASimpleGraph(completeGraph));
}

TEST(GraphUtilitiesTest, IsATreeWorks) {
    UndirectedGraphForTest treeGraph;
    treeGraph.connect(0, 1);
    treeGraph.connect(0, 2);
    treeGraph.connect(0, 3);
    UndirectedGraphForTest nonTreeGraphWithCycle;
    nonTreeGraphWithCycle.connect(0, 1);
    nonTreeGraphWithCycle.connect(1, 2);
    nonTreeGraphWithCycle.connect(2, 0);
    UndirectedGraphForTest nonTreeGraphAndItsNotConnected;
    nonTreeGraphAndItsNotConnected.connect(0, 1);
    nonTreeGraphAndItsNotConnected.connect(0, 2);
    nonTreeGraphAndItsNotConnected.connect(3, 4);

    EXPECT_TRUE(isATree(treeGraph));
    EXPECT_FALSE(isATree(nonTreeGraphWithCycle));
    EXPECT_FALSE(isATree(nonTreeGraphAndItsNotConnected));
}

TEST(GraphUtilitiesTest, IsAForestWorks) {
    UndirectedGraphForTest forestGraph;
    forestGraph.connect(0, 1);
    forestGraph.connect(0, 2);
    forestGraph.connect(3, 4);
    UndirectedGraphForTest nonForestGraphButTree;
    nonForestGraphButTree.connect(0, 1);
    nonForestGraphButTree.connect(0, 2);
    nonForestGraphButTree.connect(0, 3);
    UndirectedGraphForTest nonForestGraphGraphWithCycle;
    nonForestGraphGraphWithCycle.connect(0, 1);
    nonForestGraphGraphWithCycle.connect(1, 2);
    nonForestGraphGraphWithCycle.connect(2, 0);

    EXPECT_TRUE(isAForest(forestGraph));
    EXPECT_FALSE(isAForest(nonForestGraphButTree));
    EXPECT_FALSE(isAForest(nonForestGraphGraphWithCycle));
}

TEST(GraphUtilitiesTest, AreAllDegreesWorks) {
    UndirectedGraphForTest graphWithVaryingDegrees;
    graphWithVaryingDegrees.connect(0, 1);
    graphWithVaryingDegrees.connect(0, 2);
    graphWithVaryingDegrees.connect(0, 3);
    UndirectedGraphForTest graphWithSameDegree;
    graphWithSameDegree.connect(0, 1);
    graphWithSameDegree.connect(1, 2);
    graphWithSameDegree.connect(2, 0);

    EXPECT_FALSE(areAllDegrees(graphWithVaryingDegrees, 3));
    EXPECT_TRUE(areAllDegrees(graphWithSameDegree, 2));
}

TEST(GraphUtilitiesTest, IsASpanningTreeWorks) {
    UndirectedGraphForTest mainGraph;
    mainGraph.connect(0, 1);
    mainGraph.connect(0, 3);
    mainGraph.connect(1, 2);
    mainGraph.connect(2, 3);
    UndirectedGraphForTest spanningTree;
    spanningTree.connect(0, 1);
    spanningTree.connect(0, 2);
    spanningTree.connect(0, 3);
    UndirectedGraphForTest nonSpanningTree;
    nonSpanningTree.connect(0, 1);
    nonSpanningTree.connect(0, 2);
    nonSpanningTree.connect(0, 9);

    EXPECT_TRUE(isASpanningTree(mainGraph, spanningTree));
    EXPECT_FALSE(isASpanningTree(mainGraph, nonSpanningTree));
}

TEST(GraphUtilitiesTest, IsASpanningForestWorks) {
    UndirectedGraphForTest mainGraph;
    mainGraph.connect(0, 1);
    mainGraph.connect(0, 3);
    mainGraph.connect(1, 2);
    mainGraph.connect(2, 3);
    UndirectedGraphForTest spanningForest;
    spanningForest.connect(0, 1);
    spanningForest.connect(2, 3);
    UndirectedGraphForTest nonSpanningForest;
    nonSpanningForest.connect(0, 1);
    nonSpanningForest.connect(2, 9);

    EXPECT_TRUE(isASpanningForest(mainGraph, spanningForest));
    EXPECT_FALSE(isASpanningForest(mainGraph, nonSpanningForest));
}

TEST(GraphUtilitiesTest, IsGraphConnectedWorksForUndirectedGraphs) {
    UndirectedGraphForTest connectedGraph;
    connectedGraph.connect(0, 1);
    connectedGraph.connect(0, 2);
    connectedGraph.connect(0, 3);
    UndirectedGraphForTest nonConnectedGraph;
    nonConnectedGraph.connect(0, 1);
    nonConnectedGraph.connect(0, 2);
    nonConnectedGraph.connect(3, 4);

    EXPECT_TRUE(isGraphConnected(connectedGraph));
    EXPECT_FALSE(isGraphConnected(nonConnectedGraph));
}

TEST(GraphUtilitiesTest, IsGraphConnectedWorksForDirectedGraphs) {
    DirectedGraphForTest stronglyConnectedGraph;
    stronglyConnectedGraph.connect(0, 1);
    stronglyConnectedGraph.connect(1, 2);
    stronglyConnectedGraph.connect(2, 3);
    stronglyConnectedGraph.connect(3, 0);
    DirectedGraphForTest nonStronglyConnectedGraph;
    stronglyConnectedGraph.connect(0, 1);
    stronglyConnectedGraph.connect(0, 2);
    stronglyConnectedGraph.connect(0, 3);

    EXPECT_TRUE(isGraphConnected(stronglyConnectedGraph));
    EXPECT_FALSE(isGraphConnected(nonStronglyConnectedGraph));
}

TEST(GraphUtilitiesTest, IsGraphStronglyConnectedWorks) {
    DirectedGraphForTest stronglyConnectedGraph;
    stronglyConnectedGraph.connect(0, 1);
    stronglyConnectedGraph.connect(1, 2);
    stronglyConnectedGraph.connect(2, 3);
    stronglyConnectedGraph.connect(3, 0);
    DirectedGraphForTest nonStronglyConnectedGraph;
    stronglyConnectedGraph.connect(0, 1);
    stronglyConnectedGraph.connect(0, 2);
    stronglyConnectedGraph.connect(0, 3);

    EXPECT_TRUE(isGraphStronglyConnected(stronglyConnectedGraph));
    EXPECT_FALSE(isGraphStronglyConnected(nonStronglyConnectedGraph));
}

TEST(GraphUtilitiesTest, IsBipartiteWorks) {
    UndirectedGraphForTest bipartiteGraph;
    bipartiteGraph.connect(0, 1);
    bipartiteGraph.connect(0, 2);
    bipartiteGraph.connect(0, 3);
    bipartiteGraph.connect(3, 4);
    bipartiteGraph.connect(3, 6);
    bipartiteGraph.connect(4, 5);
    bipartiteGraph.connect(5, 6);
    UndirectedGraphForTest nonBipartiteGraph;
    nonBipartiteGraph.connect(0, 1);
    nonBipartiteGraph.connect(0, 2);
    nonBipartiteGraph.connect(0, 3);
    nonBipartiteGraph.connect(3, 4);
    nonBipartiteGraph.connect(3, 5);
    nonBipartiteGraph.connect(4, 5);

    EXPECT_TRUE(isBipartite(bipartiteGraph));
    EXPECT_FALSE(isBipartite(nonBipartiteGraph));
}

TEST(GraphUtilitiesTest, IsFlowNetworkWorks) {
    EdgeWeightedUndirectedGraphForTest undirectedGraph;
    undirectedGraph.connect(0, 1, 3.5);
    undirectedGraph.connect(0, 1, 4.5);
    EdgeWeightedDirectedGraphForTest directedGraphWithNegativeWeight;
    directedGraphWithNegativeWeight.connect(0, 1, 3.5);
    directedGraphWithNegativeWeight.connect(0, 1, -4.5);
    EdgeWeightedDirectedGraphForTest directedGraphWithPositiveWeight;
    directedGraphWithPositiveWeight.connect(0, 1, 3.5);
    directedGraphWithPositiveWeight.connect(0, 1, 4.5);
    FlowNetworkForTest flowNetwork;
    flowNetwork.connect(0, 1, 15.25, 3.5);
    flowNetwork.connect(0, 2, 16.25, 4.5);

    EXPECT_FALSE(isFlowNetwork(undirectedGraph));
    EXPECT_FALSE(isFlowNetwork(directedGraphWithNegativeWeight));
    EXPECT_TRUE(isFlowNetwork(directedGraphWithPositiveWeight));
    EXPECT_TRUE(isFlowNetwork(flowNetwork));
}

TEST(GraphUtilitiesTest, IsSinkSourceFlowNetworkFeasibleWorks) {
    SinkSourceFlowNetworkForTest flowNetworkWithOutOfRangeFlows(0, 2);
    flowNetworkWithOutOfRangeFlows.connect(0, 1, 15.25, 16);
    flowNetworkWithOutOfRangeFlows.connect(1, 2, 16.25, -1);
    SinkSourceFlowNetworkForTest flowNetworkWithNoEquilbrium(0, 2);
    flowNetworkWithNoEquilbrium.connect(0, 1, 15.25, 3.5);
    flowNetworkWithNoEquilbrium.connect(1, 2, 16.25, 4.5);
    SinkSourceFlowNetworkForTest flowNetworkWithEquilbrium(0, 2);
    flowNetworkWithEquilbrium.connect(0, 1, 15.25, 3.5);
    flowNetworkWithEquilbrium.connect(1, 2, 16.25, 3.5);

    EXPECT_FALSE(isSinkSourceFlowNetworkFeasible(flowNetworkWithOutOfRangeFlows));
    EXPECT_FALSE(isSinkSourceFlowNetworkFeasible(flowNetworkWithNoEquilbrium));
    EXPECT_TRUE(isSinkSourceFlowNetworkFeasible(flowNetworkWithEquilbrium));
}

TEST(GraphUtilitiesTest, GetLengthOfPathWorks) {
    PathForTest emptyPath;
    PathForTest nonEmptyPath{1, 2, 3};

    EXPECT_EQ(0, getLengthOfPath<VertexForTest>(emptyPath));
    EXPECT_EQ(2, getLengthOfPath<VertexForTest>(nonEmptyPath));
}

TEST(GraphUtilitiesTest, GetDegreeAtWorks) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ(2, getDegreeAt(graph, 0));
    EXPECT_EQ(1, getDegreeAt(graph, 1));
    EXPECT_EQ(1, getDegreeAt(graph, 2));
}

TEST(GraphUtilitiesTest, GetMaxDegreeAtWorks) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ(2, getMaxDegree(graph));
}

TEST(GraphUtilitiesTest, GetMinDegreeAtWorks) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ(1, getMinDegree(graph));
}

TEST(GraphUtilitiesTest, GetSumOfDegreesAtWorks) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_EQ(4, getSumOfDegrees(graph));
}

TEST(GraphUtilitiesTest, GetAverageDegreeWorks) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);

    EXPECT_EQ(1.5, getAverageDegree(graph));
}

TEST(GraphUtilitiesTest, GetNumberOfSelfLoopsWorks) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    graph.connect(1, 1);
    graph.connect(2, 2);

    EXPECT_EQ(2, getNumberOfSelfLoops(graph));
}

TEST(GraphUtilitiesTest, GetDiameterOfATreeWorks) {
    UndirectedGraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(2, 5);
    graph.connect(2, 6);
    graph.connect(4, 7);

    EXPECT_EQ(4, getDiameterOfATree(graph));
}

TEST(GraphUtilitiesTest, GetInDegreeAndOutDegreeAtWorks) {
    DirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    graph.connect(4, 0);

    auto inDegreeAndOutDegreePair(getInDegreeAndOutDegreeAt<VertexForTest>(graph, 0));

    EXPECT_EQ(3, inDegreeAndOutDegreePair.first);
    EXPECT_EQ(1, inDegreeAndOutDegreePair.second);
}

TEST(GraphUtilitiesTest, GetAllInDegreesAndOutDegreesAtWorks) {
    DirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(3, 0);

    auto vertexToInDegreeAndOutDegreePairMap(getAllInDegreesAndOutDegrees<VertexForTest>(graph));

    EXPECT_EQ(2, vertexToInDegreeAndOutDegreePairMap.at(0).first);
    EXPECT_EQ(1, vertexToInDegreeAndOutDegreePairMap.at(0).second);
    EXPECT_EQ(0, vertexToInDegreeAndOutDegreePairMap.at(1).first);
    EXPECT_EQ(1, vertexToInDegreeAndOutDegreePairMap.at(1).second);
    EXPECT_EQ(0, vertexToInDegreeAndOutDegreePairMap.at(2).first);
    EXPECT_EQ(1, vertexToInDegreeAndOutDegreePairMap.at(2).second);
    EXPECT_EQ(1, vertexToInDegreeAndOutDegreePairMap.at(3).first);
    EXPECT_EQ(0, vertexToInDegreeAndOutDegreePairMap.at(3).second);
}

TEST(GraphUtilitiesTest, GetEdgesOfMaximalConnectedSubgraphsWorks) {
    UndirectedGraphForTest graph;
    graph.connect(0, 5);
    graph.connect(4, 3);
    graph.connect(0, 1);
    graph.connect(9, 12);
    graph.connect(6, 4);
    graph.connect(5, 4);
    graph.connect(0, 2);
    graph.connect(11, 12);
    graph.connect(9, 10);
    graph.connect(0, 6);
    graph.connect(7, 8);
    graph.connect(9, 11);
    graph.connect(5, 3);

    ListOfEdgesForTest listOfEdgesToVerify(getEdgesOfMaximalConnectedSubgraphs(graph));

    ListOfEdgesForTest listOfEdgesToExpect;
    listOfEdgesToExpect.emplace_back(EdgesForTest{{0, 1}, {0, 2}, {0, 5}, {0, 6}, {3, 4}, {3, 5}, {4, 5}, {4, 6}});
    listOfEdgesToExpect.emplace_back(EdgesForTest{{7, 8}});
    listOfEdgesToExpect.emplace_back(EdgesForTest{{9, 10}, {9, 11}, {9, 12}, {11, 12}});
    EXPECT_EQ(listOfEdgesToExpect, listOfEdgesToVerify);
}

}  // namespace GraphUtilities

}  // namespace algorithm

}  // namespace alba
