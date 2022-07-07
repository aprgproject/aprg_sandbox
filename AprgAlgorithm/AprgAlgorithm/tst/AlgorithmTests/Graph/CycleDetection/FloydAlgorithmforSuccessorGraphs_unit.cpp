#include <Algorithm/Graph/CycleDetection/FloydAlgorithmforSuccessorGraphs.hpp>
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
using PathsForTest = GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using CycleDetectionForTest = FloydAlgorithmforSuccessorGraphs<VertexForTest>;
}

TEST(FloydAlgorithmforSuccessorGraphsTest, CycleDetectionWorksWhenGraphIsEmpty)
{
    GraphForTest graph;
    CycleDetectionForTest cycleDetection(graph);

    EXPECT_FALSE(cycleDetection.hasACycle());
    EXPECT_TRUE(cycleDetection.getCycle().empty());
}

TEST(FloydAlgorithmforSuccessorGraphsTest, CycleDetectionWorksWhenThereIsNoCycle)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    CycleDetectionForTest cycleDetection(graph);

    cycleDetection.reinitializeStartingFrom(0U);

    EXPECT_FALSE(cycleDetection.hasACycle());
    EXPECT_TRUE(cycleDetection.getCycle().empty());
}

TEST(FloydAlgorithmforSuccessorGraphsTest, CycleDetectionWorksUsingExample1)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(3U, 4U);
    graph.connect(4U, 5U);
    graph.connect(5U, 6U);
    graph.connect(6U, 4U);
    CycleDetectionForTest cycleDetection(graph);

    cycleDetection.reinitializeStartingFrom(0U);

    PathForTest expectedCycle{4U, 5U, 6U, 4U};
    EXPECT_TRUE(cycleDetection.hasACycle());
    EXPECT_EQ(expectedCycle, cycleDetection.getCycle());
}

}

}
