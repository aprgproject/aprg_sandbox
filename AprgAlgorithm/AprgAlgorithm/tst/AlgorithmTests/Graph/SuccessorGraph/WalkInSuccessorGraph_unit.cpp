#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/SuccessorGraph/WalkInSuccessorGraph.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using WalkPathsForTest = WalkInSuccessorGraph<VertexForTest>;
}  // namespace

TEST(WalkInSuccessorGraphTest, WalkWorksOnExample1) {
    GraphForTest graph;
    graph.connect(1, 3);
    graph.connect(3, 7);
    graph.connect(7, 1);
    graph.connect(9, 3);
    WalkPathsForTest walkPaths(graph);

    EXPECT_EQ(3, walkPaths.walk(1, 1));
    EXPECT_EQ(7, walkPaths.walk(1, 2));
    EXPECT_EQ(1, walkPaths.walk(1, 3));
    EXPECT_EQ(3, walkPaths.walk(9, 1));
    EXPECT_EQ(7, walkPaths.walk(9, 2));
    EXPECT_EQ(1, walkPaths.walk(9, 3));
}

TEST(WalkInSuccessorGraphTest, WalkWorksOnExample2) {
    GraphForTest graph;
    graph.connect(4, 6);
    graph.connect(8, 6);
    graph.connect(6, 2);
    graph.connect(2, 5);
    graph.connect(5, 2);
    WalkPathsForTest walkPaths(graph);

    EXPECT_EQ(6, walkPaths.walk(4, 1));
    EXPECT_EQ(2, walkPaths.walk(4, 2));
    EXPECT_EQ(5, walkPaths.walk(4, 3));
    EXPECT_EQ(2, walkPaths.walk(4, 4));
}

}  // namespace algorithm

}  // namespace alba
