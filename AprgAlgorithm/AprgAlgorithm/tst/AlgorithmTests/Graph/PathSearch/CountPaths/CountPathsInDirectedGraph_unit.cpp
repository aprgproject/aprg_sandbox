#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/CountPaths/CountPathsInDirectedGraph.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using CountPathsForTest = CountPathsInDirectedGraph<VertexForTest>;
}  // namespace

TEST(CountPathsInDirectedGraphTest, GetCountWorksOnExample1) {
    GraphForTest graph;
    graph.connect(1, 4);
    graph.connect(1, 2);
    graph.connect(4, 5);
    graph.connect(5, 2);
    graph.connect(5, 3);
    graph.connect(2, 3);
    graph.connect(3, 6);
    CountPathsForTest countPaths(graph);

    EXPECT_EQ(1, countPaths.getCount(1, 1));
    EXPECT_EQ(1, countPaths.getCount(1, 4));
    EXPECT_EQ(1, countPaths.getCount(1, 5));
    EXPECT_EQ(2, countPaths.getCount(1, 2));
    EXPECT_EQ(3, countPaths.getCount(1, 3));
    EXPECT_EQ(3, countPaths.getCount(1, 6));
    EXPECT_EQ(0, countPaths.getCount(5, 1));
    EXPECT_EQ(0, countPaths.getCount(5, 4));
    EXPECT_EQ(1, countPaths.getCount(5, 5));
    EXPECT_EQ(1, countPaths.getCount(5, 2));
    EXPECT_EQ(2, countPaths.getCount(5, 3));
    EXPECT_EQ(2, countPaths.getCount(5, 6));
}

}  // namespace algorithm

}  // namespace alba
