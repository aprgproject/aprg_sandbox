#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphUtilitiesForTest = GraphUtilities<unsigned int>;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<unsigned int>;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<unsigned int>;
}

TEST(GraphUtilitiesTest, IsASimplePathWorks)
{
    GraphUtilitiesForTest::Path simplePath{1U, 2U, 3U};
    GraphUtilitiesForTest::Path nonSimplePath{1U, 2U, 3U, 2U, 4U};

    EXPECT_TRUE(GraphUtilitiesForTest::isASimplePath(simplePath));
    EXPECT_FALSE(GraphUtilitiesForTest::isASimplePath(nonSimplePath));
}

TEST(GraphUtilitiesTest, IsACycleWorks)
{
    GraphUtilitiesForTest::Path cyclePath{1U, 2U, 3U, 1U};
    GraphUtilitiesForTest::Path nonCyclePath{1U, 2U, 3U, 1U, 4U};

    EXPECT_TRUE(GraphUtilitiesForTest::isACycle(cyclePath));
    EXPECT_FALSE(GraphUtilitiesForTest::isACycle(nonCyclePath));
}

TEST(GraphUtilitiesTest, IsASimpleCycleWorks)
{
    GraphUtilitiesForTest::Path cycleSimplePath{1U, 2U, 3U, 1U};
    GraphUtilitiesForTest::Path nonCycleSimplePath{1U, 2U, 3U, 2U, 1U};

    EXPECT_TRUE(GraphUtilitiesForTest::isASimpleCycle(cycleSimplePath));
    EXPECT_FALSE(GraphUtilitiesForTest::isASimpleCycle(nonCycleSimplePath));
}

TEST(GraphUtilitiesTest, IsDirectedAcyclicGraphWorks)
{
    UndirectedGraphForTest undirectedGraph;
    undirectedGraph.connect(0U, 1U);
    undirectedGraph.connect(1U, 2U);
    undirectedGraph.connect(2U, 0U);
    DirectedGraphForTest graphWithoutCycle;
    graphWithoutCycle.connect(0U, 1U);
    graphWithoutCycle.connect(0U, 2U);
    graphWithoutCycle.connect(0U, 3U);
    DirectedGraphForTest graphWithCycle;
    graphWithCycle.connect(0U, 1U);
    graphWithCycle.connect(1U, 2U);
    graphWithCycle.connect(2U, 0U);

    EXPECT_FALSE(GraphUtilitiesForTest::isDirectedAcyclicGraph(undirectedGraph));
    EXPECT_FALSE(GraphUtilitiesForTest::isDirectedAcyclicGraph(graphWithoutCycle));
    EXPECT_TRUE(GraphUtilitiesForTest::isDirectedAcyclicGraph(graphWithCycle));
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

    EXPECT_FALSE(GraphUtilitiesForTest::hasAnyCyclesOnGraph(graphWithoutCycle));
    EXPECT_TRUE(GraphUtilitiesForTest::hasAnyCyclesOnGraph(graphWithCycle));
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

    EXPECT_TRUE(GraphUtilitiesForTest::isATree(treeGraph));
    EXPECT_FALSE(GraphUtilitiesForTest::isATree(nonTreeGraphWithCycle));
    EXPECT_FALSE(GraphUtilitiesForTest::isATree(nonTreeGraphAndItsNotConnected));
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

    EXPECT_TRUE(GraphUtilitiesForTest::isAForest(forestGraph));
    EXPECT_FALSE(GraphUtilitiesForTest::isAForest(nonForestGraphButTree));
    EXPECT_FALSE(GraphUtilitiesForTest::isAForest(nonForestGraphGraphWithCycle));
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

    EXPECT_TRUE(GraphUtilitiesForTest::isASpanningTree(mainGraph, spanningTree));
    EXPECT_FALSE(GraphUtilitiesForTest::isASpanningTree(mainGraph, nonSpanningTree));
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

    EXPECT_TRUE(GraphUtilitiesForTest::isASpanningForest(mainGraph, spanningForest));
    EXPECT_FALSE(GraphUtilitiesForTest::isASpanningForest(mainGraph, nonSpanningForest));
}

TEST(GraphUtilitiesTest, IsGraphConnectedWorks)
{
    UndirectedGraphForTest connectedGraph;
    connectedGraph.connect(0U, 1U);
    connectedGraph.connect(0U, 2U);
    connectedGraph.connect(0U, 3U);
    UndirectedGraphForTest nonConnectedGraph;
    nonConnectedGraph.connect(0U, 1U);
    nonConnectedGraph.connect(0U, 2U);
    nonConnectedGraph.connect(3U, 4U);

    EXPECT_TRUE(GraphUtilitiesForTest::isGraphConnected(connectedGraph));
    EXPECT_FALSE(GraphUtilitiesForTest::isGraphConnected(nonConnectedGraph));
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

    EXPECT_TRUE(GraphUtilitiesForTest::isGraphStronglyConnected(stronglyConnectedGraph));
    EXPECT_FALSE(GraphUtilitiesForTest::isGraphStronglyConnected(nonStronglyConnectedGraph));
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

    EXPECT_TRUE(GraphUtilitiesForTest::isBipartite(bipartiteGraph));
    EXPECT_FALSE(GraphUtilitiesForTest::isBipartite(nonBipartiteGraph));
}

TEST(GraphUtilitiesTest, GetDegreeAtWorks)
{
    UndirectedGraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, GraphUtilitiesForTest::getDegreeAt(graph, 0U));
    EXPECT_EQ(1U, GraphUtilitiesForTest::getDegreeAt(graph, 1U));
    EXPECT_EQ(1U, GraphUtilitiesForTest::getDegreeAt(graph, 2U));
}

TEST(GraphUtilitiesTest, GetMaxDegreeAtWorks)
{
    UndirectedGraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, GraphUtilitiesForTest::getMaxDegree(graph));
}

TEST(GraphUtilitiesTest, GetAverageDegreeWorks)
{
    UndirectedGraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);

    EXPECT_EQ(1.5, GraphUtilitiesForTest::getAverageDegree(graph));
}

TEST(GraphUtilitiesTest, GetNumberOfSelfLoopsWorks)
{
    UndirectedGraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    graph.connect(1U, 1U);
    graph.connect(2U, 2U);

    EXPECT_EQ(2U, GraphUtilitiesForTest::getNumberOfSelfLoops(graph));
}

TEST(GraphUtilitiesTest, GetEdgesOfMaximalConnectedSubgraphsWorks)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 5U);
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

    GraphUtilitiesForTest::ListOfEdges listOfEdgesToVerify(GraphUtilitiesForTest::getEdgesOfMaximalConnectedSubgraphs(graph));

    GraphUtilitiesForTest::ListOfEdges listOfEdgesToExpect;
    listOfEdgesToExpect.emplace_back(GraphUtilitiesForTest::Edges{{0, 1}, {0, 2}, {0, 5}, {0, 6}, {3, 4}, {3, 5}, {4, 5}, {4, 6}});
    listOfEdgesToExpect.emplace_back(GraphUtilitiesForTest::Edges{{7, 8}});
    listOfEdgesToExpect.emplace_back(GraphUtilitiesForTest::Edges{{9, 10}, {9, 11}, {9, 12}, {11, 12}});
    EXPECT_EQ(listOfEdgesToExpect, listOfEdgesToVerify);
}


}

}
