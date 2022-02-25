#include <Algorithm/Graph/GraphUtilities.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace
{
using SampleGraphForTest = UndirectedGraphWithListOfEdges;
}

TEST(GraphUtilitiesTest, IsASimplePathWorks)
{
    Path simplePath{1U, 2U, 3U};
    Path nonSimplePath{1U, 2U, 3U, 2U, 4U};

    EXPECT_TRUE(isASimplePath(simplePath));
    EXPECT_FALSE(isASimplePath(nonSimplePath));
}

TEST(GraphUtilitiesTest, IsACycleWorks)
{
    Path cyclePath{1U, 2U, 3U, 1U};
    Path nonCyclePath{1U, 2U, 3U, 1U, 4U};

    EXPECT_TRUE(isACycle(cyclePath));
    EXPECT_FALSE(isACycle(nonCyclePath));
}

TEST(GraphUtilitiesTest, IsASimpleCycleWorks)
{
    Path cycleSimplePath{1U, 2U, 3U, 1U};
    Path nonCycleSimplePath{1U, 2U, 3U, 2U, 1U};

    EXPECT_TRUE(isASimpleCycle(cycleSimplePath));
    EXPECT_FALSE(isASimpleCycle(nonCycleSimplePath));
}

TEST(GraphUtilitiesTest, IsATreeWorks)
{
    SampleGraphForTest treeGraph;
    treeGraph.connect(0U, 1U);
    treeGraph.connect(0U, 2U);
    treeGraph.connect(0U, 3U);
    SampleGraphForTest nonTreeGraphWithCycle;
    nonTreeGraphWithCycle.connect(0U, 1U);
    nonTreeGraphWithCycle.connect(1U, 2U);
    nonTreeGraphWithCycle.connect(2U, 0U);
    SampleGraphForTest nonTreeGraphAndItsNotConnected;
    nonTreeGraphAndItsNotConnected.connect(0U, 1U);
    nonTreeGraphAndItsNotConnected.connect(0U, 2U);
    nonTreeGraphAndItsNotConnected.connect(3U, 4U);

    EXPECT_TRUE(isATree(treeGraph));
    EXPECT_FALSE(isATree(nonTreeGraphWithCycle));
    EXPECT_FALSE(isATree(nonTreeGraphAndItsNotConnected));
}

TEST(GraphUtilitiesTest, HasAnyCyclesOnGraphWorks)
{
    SampleGraphForTest graphWithoutCycle;
    graphWithoutCycle.connect(0U, 1U);
    graphWithoutCycle.connect(0U, 2U);
    graphWithoutCycle.connect(0U, 3U);
    SampleGraphForTest graphWithCycle;
    graphWithCycle.connect(0U, 1U);
    graphWithCycle.connect(1U, 2U);
    graphWithCycle.connect(2U, 0U);

    EXPECT_FALSE(hasAnyCyclesOnGraph(graphWithoutCycle));
    EXPECT_TRUE(hasAnyCyclesOnGraph(graphWithCycle));
}

TEST(GraphUtilitiesTest, IsGraphConnectedWorks)
{
    SampleGraphForTest connectedGraph;
    connectedGraph.connect(0U, 1U);
    connectedGraph.connect(0U, 2U);
    connectedGraph.connect(0U, 3U);
    SampleGraphForTest nonConnectedGraph;
    nonConnectedGraph.connect(0U, 1U);
    nonConnectedGraph.connect(0U, 2U);
    nonConnectedGraph.connect(3U, 4U);

    EXPECT_TRUE(isGraphConnected(connectedGraph));
    EXPECT_FALSE(isGraphConnected(nonConnectedGraph));
}

TEST(GraphUtilitiesTest, GetDegreeAtWorks)
{
    SampleGraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, getDegreeAt(graph, 0U));
    EXPECT_EQ(1U, getDegreeAt(graph, 1U));
    EXPECT_EQ(1U, getDegreeAt(graph, 2U));
}

TEST(GraphUtilitiesTest, GetMaxDegreeAtWorks)
{
    SampleGraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, getMaxDegree(graph));
}

TEST(GraphUtilitiesTest, GetAverageDegreeWorks)
{
    SampleGraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);

    EXPECT_EQ(1.5, getAverageDegree(graph));
}

TEST(GraphUtilitiesTest, GetNumberOfSelfLoopsWorks)
{
    SampleGraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    graph.connect(1U, 1U);
    graph.connect(2U, 2U);

    EXPECT_EQ(2U, getNumberOfSelfLoops(graph));
}

TEST(GraphUtilitiesTest, GetEdgesOfMaximalConnectedSubgraphsWorks)
{
    SampleGraphForTest graph;
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

    ListOfEdges listOfEdgesToVerify(getEdgesOfMaximalConnectedSubgraphs(graph));

    ListOfEdges listOfEdgesToExpect;
    listOfEdgesToExpect.emplace_back(Edges{{0, 1}, {0, 2}, {0, 5}, {0, 6}, {3, 4}, {3, 5}, {4, 5}, {4, 6}});
    listOfEdgesToExpect.emplace_back(Edges{{7, 8}});
    listOfEdgesToExpect.emplace_back(Edges{{9, 10}, {9, 11}, {9, 12}, {11, 12}});
    EXPECT_EQ(listOfEdgesToExpect, listOfEdgesToVerify);
}


}

}
