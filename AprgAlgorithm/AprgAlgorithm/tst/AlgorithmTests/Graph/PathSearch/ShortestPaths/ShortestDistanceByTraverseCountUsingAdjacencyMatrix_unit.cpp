#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithAdjacencyMatrix.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/ShortestPaths/ShortestDistanceByTraverseCountUsingAdjacencyMatrix.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithAdjacencyMatrix.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
constexpr VertexForTest MAX_VERTEX_VALUE = 7U;

using WeightForTest = double;
using UndirectedGraphForTest = UndirectedGraphWithAdjacencyMatrix<VertexForTest, MAX_VERTEX_VALUE>;
using DirectedGraphForTest = DirectedGraphWithAdjacencyMatrix<VertexForTest, MAX_VERTEX_VALUE>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using EdgeWeightedDirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, DirectedGraphForTest>;
using ShortestPathsForUndirectedGraphForTest = ShortestDistanceByTraverseCountUsingAdjacencyMatrix<
    VertexForTest, WeightForTest, EdgeWeightedUndirectedGraphForTest>;
using ShortestPathsForDirectedGraphForTest =
    ShortestDistanceByTraverseCountUsingAdjacencyMatrix<VertexForTest, WeightForTest, EdgeWeightedDirectedGraphForTest>;
}  // namespace

TEST(ShortestDistanceByTraverseCountUsingAdjacencyMatrixTest, GetShortestDistanceWorksWithUndirectedGraphOnExample1) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(1U, 4U, 1.0);
    graph.connect(1U, 2U, 1.5);
    graph.connect(4U, 5U, 2.0);
    graph.connect(5U, 2U, 2.5);
    graph.connect(5U, 3U, 3.0);
    graph.connect(2U, 3U, 2.0);
    graph.connect(3U, 6U, 1.0);
    ShortestPathsForUndirectedGraphForTest shortestPaths(graph, 3U);

    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1U, 1U));
    EXPECT_DOUBLE_EQ(3.5, shortestPaths.getShortestDistance(1U, 2U));
    EXPECT_DOUBLE_EQ(6, shortestPaths.getShortestDistance(1U, 3U));
    EXPECT_DOUBLE_EQ(3, shortestPaths.getShortestDistance(1U, 4U));
    EXPECT_DOUBLE_EQ(6.5, shortestPaths.getShortestDistance(1U, 5U));
    EXPECT_DOUBLE_EQ(4.5, shortestPaths.getShortestDistance(1U, 6U));
}

TEST(ShortestDistanceByTraverseCountUsingAdjacencyMatrixTest, GetShortestDistanceWorksWithDirectedGraphOnExample1) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(1U, 4U, 1.0);
    graph.connect(1U, 2U, 1.5);
    graph.connect(4U, 5U, 2.0);
    graph.connect(5U, 2U, 2.5);
    graph.connect(5U, 3U, 3.0);
    graph.connect(2U, 3U, 2.0);
    graph.connect(3U, 6U, 1.0);
    ShortestPathsForDirectedGraphForTest shortestPaths(graph, 3U);

    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1U, 1U));
    EXPECT_DOUBLE_EQ(5.5, shortestPaths.getShortestDistance(1U, 2U));
    EXPECT_DOUBLE_EQ(6, shortestPaths.getShortestDistance(1U, 3U));
    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1U, 4U));
    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1U, 5U));
    EXPECT_DOUBLE_EQ(4.5, shortestPaths.getShortestDistance(1U, 6U));
}

TEST(ShortestDistanceByTraverseCountUsingAdjacencyMatrixTest, GetShortestDistanceWorksWithDirectedGraphOnExample2) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(1U, 4U, 4.0);
    graph.connect(2U, 1U, 2.0);
    graph.connect(2U, 5U, 1.0);
    graph.connect(2U, 6U, 2.0);
    graph.connect(3U, 2U, 4.0);
    graph.connect(4U, 2U, 1.0);
    graph.connect(6U, 3U, 3.0);
    graph.connect(6U, 5U, 2.0);
    ShortestPathsForDirectedGraphForTest shortestPaths(graph, 4U);

    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1U, 1U));
    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1U, 2U));
    EXPECT_DOUBLE_EQ(10, shortestPaths.getShortestDistance(1U, 3U));
    EXPECT_DOUBLE_EQ(11, shortestPaths.getShortestDistance(1U, 4U));
    EXPECT_DOUBLE_EQ(9, shortestPaths.getShortestDistance(1U, 5U));
    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1U, 6U));
    EXPECT_DOUBLE_EQ(8, shortestPaths.getShortestDistance(2U, 5U));
}

}  // namespace algorithm

}  // namespace alba
