#include <Algorithm/Graph/CycleDetection/CycleDetectionUsingDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using PathsForTest = GraphTypes<VertexForTest>::Paths;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using CycleDetectionForTest = CycleDetectionUsingDfs<VertexForTest>;
}  // namespace

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksWhenGraphIsEmptyWithUndirectedGraph) {
    GraphForTest graph;
    CycleDetectionForTest cycleDetection(graph);

    EXPECT_TRUE(cycleDetection.getOneCycle().empty());
    EXPECT_TRUE(cycleDetection.getAllCycles().empty());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksWhenThereIsNoCycleWithUndirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    CycleDetectionForTest cycleDetection(graph);

    EXPECT_TRUE(cycleDetection.getOneCycle().empty());
    EXPECT_TRUE(cycleDetection.getAllCycles().empty());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample1WithUndirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 0);
    CycleDetectionForTest cycleDetection(graph);

    PathForTest expectedOneCycle{0, 1, 2, 0};
    PathsForTest expectedCycles{{0, 1, 2, 0}};
    EXPECT_EQ(expectedOneCycle, cycleDetection.getOneCycle());
    EXPECT_EQ(expectedCycles, cycleDetection.getAllCycles());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample2WithUndirectedGraph) {
    GraphForTest graph;
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
    CycleDetectionForTest cycleDetection(graph);

    PathForTest expectedOneCycle{5, 3, 4, 5};
    PathsForTest expectedCycles{{5, 3, 4, 5}, {0, 5, 3, 4, 6, 0}, {9, 11, 12, 9}};
    EXPECT_EQ(expectedOneCycle, cycleDetection.getOneCycle());
    EXPECT_EQ(expectedCycles, cycleDetection.getAllCycles());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample3WithUndirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(3, 4);
    graph.connect(4, 0);
    CycleDetectionForTest cycleDetection(graph);

    PathForTest expectedOneCycle{0, 1, 2, 3, 4, 0};
    PathsForTest expectedCycles{{0, 1, 2, 3, 4, 0}};
    EXPECT_EQ(expectedOneCycle, cycleDetection.getOneCycle());
    EXPECT_EQ(expectedCycles, cycleDetection.getAllCycles());
}

}  // namespace algorithm

}  // namespace alba
