#include <Algorithm/Graph/CycleDetection/CycleDetectionUsingDfs.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using CycleDetectionForTest = CycleDetectionUsingDfs<VertexForTest>;
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksWhenGraphIsEmptyWithDirectedGraph)
{
    GraphForTest graph;
    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_FALSE(cycleDetectionWithDfs.hasCycle());
    EXPECT_TRUE(cycleDetectionWithDfs.getPathWithCycle().empty());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksWhenThereIsNoCycleWithDirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(2U, 1U);
    graph.connect(2U, 3U);
    graph.connect(3U, 0U);
    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_FALSE(cycleDetectionWithDfs.hasCycle());
    EXPECT_TRUE(cycleDetectionWithDfs.getPathWithCycle().empty());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample1WithDirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 5U);
    graph.connect(3U, 5U);
    graph.connect(4U, 3U);
    graph.connect(5U, 4U);
    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_TRUE(cycleDetectionWithDfs.hasCycle());
    PathForTest expectedCyclePath{5U, 4U, 3U, 5U};
    EXPECT_EQ(expectedCyclePath, cycleDetectionWithDfs.getPathWithCycle());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample2WithDirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 5U);
    graph.connect(2U, 0U);
    graph.connect(2U, 3U);
    graph.connect(3U, 2U);
    graph.connect(3U, 5U);
    graph.connect(4U, 2U);
    graph.connect(4U, 3U);
    graph.connect(5U, 4U);
    graph.connect(6U, 0U);
    graph.connect(6U, 4U);
    graph.connect(6U, 8U);
    graph.connect(6U, 9U);
    graph.connect(7U, 6U);
    graph.connect(7U, 9U);
    graph.connect(8U, 6U);
    graph.connect(9U, 10U);
    graph.connect(9U, 11U);
    graph.connect(10U, 12U);
    graph.connect(11U, 4U);
    graph.connect(11U, 12U);
    graph.connect(12U, 9U);
    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_TRUE(cycleDetectionWithDfs.hasCycle());
    PathForTest expectedCyclePath{0U, 5U, 4U, 2U, 0U};
    EXPECT_EQ(expectedCyclePath, cycleDetectionWithDfs.getPathWithCycle());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample3WithDirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(3U, 4U);
    graph.connect(4U, 0U);

    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_TRUE(cycleDetectionWithDfs.hasCycle());
    PathForTest expectedCyclePath{0U, 1U, 2U, 3U, 4U, 0U};
    EXPECT_EQ(expectedCyclePath, cycleDetectionWithDfs.getPathWithCycle());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample4WithDirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 2U);
    graph.connect(0U, 4U);
    graph.connect(1U, 3U);
    graph.connect(2U, 7U);
    graph.connect(3U, 6U);
    graph.connect(4U, 5U);
    graph.connect(4U, 7U);
    graph.connect(5U, 1U);
    graph.connect(5U, 4U);
    graph.connect(5U, 7U);
    graph.connect(6U, 0U);
    graph.connect(6U, 2U);
    graph.connect(6U, 4U);
    graph.connect(7U, 3U);
    graph.connect(7U, 5U);
    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_TRUE(cycleDetectionWithDfs.hasCycle());
    PathForTest expectedCyclePath{0U, 2U, 7U, 3U, 6U, 0U};
    EXPECT_EQ(expectedCyclePath, cycleDetectionWithDfs.getPathWithCycle());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample5WithDirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 2U);
    graph.connect(0U, 4U);
    graph.connect(1U, 3U);
    graph.connect(2U, 7U);
    graph.connect(3U, 6U);
    graph.connect(4U, 5U);
    graph.connect(4U, 7U);
    graph.connect(5U, 1U);
    graph.connect(5U, 7U);
    graph.connect(7U, 3U);
    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_FALSE(cycleDetectionWithDfs.hasCycle());
    EXPECT_TRUE(cycleDetectionWithDfs.getPathWithCycle().empty());
}

}

}
