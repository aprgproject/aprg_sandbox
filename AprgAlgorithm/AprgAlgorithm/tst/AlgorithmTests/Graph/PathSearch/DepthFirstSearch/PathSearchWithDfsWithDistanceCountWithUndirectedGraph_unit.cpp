#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfsWithDistanceCount.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using ContentMapForTest = GraphTypes<VertexForTest>::VertexToIntMap;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = PathSearchUsingDfsWithDistanceCount<VertexForTest>;

void putConnectionsForTest(GraphForTest& graph) {
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 5);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(2, 4);
    graph.connect(3, 4);
    graph.connect(3, 5);
}
}  // namespace

TEST(PathSearchUsingDfsWithDistanceCountTest, GetDistanceToWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0});

    EXPECT_EQ(0, pathSearch.getDistanceTo(0));
    EXPECT_EQ(1, pathSearch.getDistanceTo(1));
    EXPECT_EQ(2, pathSearch.getDistanceTo(2));
    EXPECT_EQ(3, pathSearch.getDistanceTo(3));
    EXPECT_EQ(4, pathSearch.getDistanceTo(4));
    EXPECT_EQ(4, pathSearch.getDistanceTo(5));
    EXPECT_EQ(0, pathSearch.getDistanceTo(6));
}

TEST(PathSearchUsingDfsWithDistanceCountTest, GetEndVertexToDistanceCountMapWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0});

    ContentMapForTest expectedMap{{0, 0}, {1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 4}};
    EXPECT_EQ(expectedMap, pathSearch.getEndVertexToDistanceCountMap());
}

}  // namespace algorithm

}  // namespace alba
