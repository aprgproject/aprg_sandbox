#include <Algorithm/Graph/CycleDetection/BrentAlgorithmForSuccessorGraphs.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using PathsForTest = GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using CycleDetectionForTest = BrentAlgorithmForSuccessorGraphs<VertexForTest>;
}  // namespace

TEST(BrentAlgorithmForSuccessorGraphsTest, CycleDetectionWorksWhenGraphIsEmpty) {
    GraphForTest graph;
    CycleDetectionForTest cycleDetection(graph);

    EXPECT_FALSE(cycleDetection.hasACycle());
    EXPECT_TRUE(cycleDetection.getCycle().empty());
}

TEST(BrentAlgorithmForSuccessorGraphsTest, CycleDetectionWorksWhenThereIsNoCycle) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    CycleDetectionForTest cycleDetection(graph);

    cycleDetection.reinitializeStartingFrom(0);

    EXPECT_FALSE(cycleDetection.hasACycle());
    EXPECT_TRUE(cycleDetection.getCycle().empty());
}

TEST(BrentAlgorithmForSuccessorGraphsTest, CycleDetectionWorksUsingExample1) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 4);
    graph.connect(4, 5);
    graph.connect(5, 6);
    graph.connect(6, 4);
    CycleDetectionForTest cycleDetection(graph);

    cycleDetection.reinitializeStartingFrom(0);

    PathForTest expectedCycle{4, 5, 6, 4};
    EXPECT_TRUE(cycleDetection.hasACycle());
    EXPECT_EQ(expectedCycle, cycleDetection.getCycle());
}

}  // namespace algorithm

}  // namespace alba
