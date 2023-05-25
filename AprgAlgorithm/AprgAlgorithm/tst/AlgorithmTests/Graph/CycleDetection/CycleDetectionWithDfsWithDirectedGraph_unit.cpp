#include <Algorithm/Graph/CycleDetection/CycleDetectionUsingDfs.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using PathsForTest = GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using CycleDetectionForTest = CycleDetectionUsingDfs<VertexForTest>;
}  // namespace

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksWhenGraphIsEmptyWithDirectedGraph) {
    GraphForTest graph;
    CycleDetectionForTest cycleDetection(graph);

    EXPECT_TRUE(cycleDetection.getOneCycle().empty());
    EXPECT_TRUE(cycleDetection.getAllCycles().empty());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksWhenThereIsNoCycleWithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(2, 1);
    graph.connect(2, 3);
    graph.connect(3, 0);
    CycleDetectionForTest cycleDetection(graph);

    EXPECT_TRUE(cycleDetection.getOneCycle().empty());
    EXPECT_TRUE(cycleDetection.getAllCycles().empty());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample1WithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 5);
    graph.connect(3, 5);
    graph.connect(4, 3);
    graph.connect(5, 4);
    CycleDetectionForTest cycleDetection(graph);

    PathForTest expectedOneCycle{5, 4, 3, 5};
    PathsForTest expectedCycles{{5, 4, 3, 5}};
    EXPECT_EQ(expectedOneCycle, cycleDetection.getOneCycle());
    EXPECT_EQ(expectedCycles, cycleDetection.getAllCycles());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample2WithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 5);
    graph.connect(2, 0);
    graph.connect(2, 3);
    graph.connect(3, 2);
    graph.connect(3, 5);
    graph.connect(4, 2);
    graph.connect(4, 3);
    graph.connect(5, 4);
    graph.connect(6, 0);
    graph.connect(6, 4);
    graph.connect(6, 8);
    graph.connect(6, 9);
    graph.connect(7, 6);
    graph.connect(7, 9);
    graph.connect(8, 6);
    graph.connect(9, 10);
    graph.connect(9, 11);
    graph.connect(10, 12);
    graph.connect(11, 4);
    graph.connect(11, 12);
    graph.connect(12, 9);
    CycleDetectionForTest cycleDetection(graph);

    PathForTest expectedOneCycle{0, 5, 4, 2, 0};
    PathsForTest expectedCycles{
        {0, 5, 4, 2, 0}, {2, 3, 2}, {5, 4, 2, 3, 5}, {6, 8, 6}, {9, 10, 12, 9}};
    EXPECT_EQ(expectedOneCycle, cycleDetection.getOneCycle());
    EXPECT_EQ(expectedCycles, cycleDetection.getAllCycles());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample3WithDirectedGraph) {
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

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample4WithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 2);
    graph.connect(0, 4);
    graph.connect(1, 3);
    graph.connect(2, 7);
    graph.connect(3, 6);
    graph.connect(4, 5);
    graph.connect(4, 7);
    graph.connect(5, 1);
    graph.connect(5, 4);
    graph.connect(5, 7);
    graph.connect(6, 0);
    graph.connect(6, 2);
    graph.connect(6, 4);
    graph.connect(7, 3);
    graph.connect(7, 5);
    CycleDetectionForTest cycleDetection(graph);

    PathForTest expectedOneCycle{0, 2, 7, 3, 6, 0};
    PathsForTest expectedCycles{{0, 2, 7, 3, 6, 0}, {2, 7, 3, 6, 2}, {3, 6, 4, 5, 1, 3}, {4, 5, 4},
                                {7, 3, 6, 4, 5, 7}, {7, 3, 6, 4, 7}};
    EXPECT_EQ(expectedOneCycle, cycleDetection.getOneCycle());
    EXPECT_EQ(expectedCycles, cycleDetection.getAllCycles());
}

TEST(CycleDetectionUsingDfsTest, CycleDetectionWorksUsingExample5WithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 2);
    graph.connect(0, 4);
    graph.connect(1, 3);
    graph.connect(2, 7);
    graph.connect(3, 6);
    graph.connect(4, 5);
    graph.connect(4, 7);
    graph.connect(5, 1);
    graph.connect(5, 7);
    graph.connect(7, 3);
    CycleDetectionForTest cycleDetection(graph);

    EXPECT_TRUE(cycleDetection.getOneCycle().empty());
    EXPECT_TRUE(cycleDetection.getAllCycles().empty());
}

}  // namespace algorithm

}  // namespace alba
