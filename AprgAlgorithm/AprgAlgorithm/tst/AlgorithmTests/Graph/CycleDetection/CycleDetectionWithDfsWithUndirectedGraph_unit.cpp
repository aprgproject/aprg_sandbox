#include <Algorithm/Graph/CycleDetection/CycleDetectionUsingDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using CycleDetectionForTest = CycleDetectionUsingDfs<VertexForTest>;
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksWhenGraphIsEmptyWithUndirectedGraph)
{
    GraphForTest graph;
    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_FALSE(cycleDetectionWithDfs.hasCycle());
    EXPECT_TRUE(cycleDetectionWithDfs.getPathWithCycle().empty());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksWhenThereIsNoCycleWithUndirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_FALSE(cycleDetectionWithDfs.hasCycle());
    EXPECT_TRUE(cycleDetectionWithDfs.getPathWithCycle().empty());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample1WithUndirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 0U);
    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_TRUE(cycleDetectionWithDfs.hasCycle());
    PathForTest expectedCyclePath{0U, 1U, 2U, 0U};
    EXPECT_EQ(expectedCyclePath, cycleDetectionWithDfs.getPathWithCycle());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample2WithUndirectedGraph)
{
    GraphForTest graph;
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

    CycleDetectionForTest cycleDetectionWithDfs(graph);

    cycleDetectionWithDfs.checkForCycles();

    EXPECT_TRUE(cycleDetectionWithDfs.hasCycle());
    PathForTest expectedCyclePath{5U, 3U, 4U, 5U};
    EXPECT_EQ(expectedCyclePath, cycleDetectionWithDfs.getPathWithCycle());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample3WithUndirectedGraph)
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

}

}
