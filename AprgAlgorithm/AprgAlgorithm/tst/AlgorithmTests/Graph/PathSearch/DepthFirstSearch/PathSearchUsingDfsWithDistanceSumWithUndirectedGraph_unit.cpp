#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfsWithDistanceSum.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using WeightForTest = double;
using ContentMapForTest = GraphTypesWithWeights<VertexForTest, WeightForTest>::VertexToWeightMap;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using PathSearchForTest =
    PathSearchUsingDfsWithDistanceSum<VertexForTest, WeightForTest, EdgeWeightedUndirectedGraphForTest>;

void putConnectionsForTest(EdgeWeightedUndirectedGraphForTest& graph) {
    graph.connect(0U, 1U, 0.05);
    graph.connect(0U, 2U, 0.10);
    graph.connect(0U, 5U, 0.15);
    graph.connect(1U, 2U, 0.20);
    graph.connect(2U, 3U, 0.25);
    graph.connect(2U, 4U, 0.30);
    graph.connect(3U, 4U, 0.35);
    graph.connect(3U, 5U, 0.40);
}
}  // namespace

TEST(PathSearchUsingDfsWithDistanceSumTest, GetDistanceToWorksWithUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0U});

    EXPECT_DOUBLE_EQ(0, pathSearch.getDistanceTo(0U));
    EXPECT_DOUBLE_EQ(0.05, pathSearch.getDistanceTo(1U));
    EXPECT_DOUBLE_EQ(0.25, pathSearch.getDistanceTo(2U));
    EXPECT_DOUBLE_EQ(0.5, pathSearch.getDistanceTo(3U));
    EXPECT_DOUBLE_EQ(0.85, pathSearch.getDistanceTo(4U));
    EXPECT_DOUBLE_EQ(0.9, pathSearch.getDistanceTo(5U));
    EXPECT_DOUBLE_EQ(0, pathSearch.getDistanceTo(6U));
}

TEST(PathSearchUsingDfsWithDistanceSumTest, GetEndVertexToDistanceSumMapWorksWithUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0U});

    ContentMapForTest expectedMap{{0U, 0.0}, {1U, 0.05}, {2U, 0.25}, {3U, 0.5}, {4U, 0.85}, {5U, 0.9}};
    EXPECT_EQ(expectedMap, pathSearch.getEndVertexToDistanceSumMap());
}

}  // namespace algorithm

}  // namespace alba
