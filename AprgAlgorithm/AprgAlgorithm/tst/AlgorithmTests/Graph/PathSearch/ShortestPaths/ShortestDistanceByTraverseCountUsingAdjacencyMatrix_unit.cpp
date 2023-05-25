#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithAdjacencyMatrix.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/ShortestPaths/ShortestDistanceByTraverseCountUsingAdjacencyMatrix.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithAdjacencyMatrix.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
constexpr VertexForTest MAX_VERTEX_VALUE = 7;

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
    graph.connect(1, 4, 1.0);
    graph.connect(1, 2, 1.5);
    graph.connect(4, 5, 2.0);
    graph.connect(5, 2, 2.5);
    graph.connect(5, 3, 3.0);
    graph.connect(2, 3, 2.0);
    graph.connect(3, 6, 1.0);
    ShortestPathsForUndirectedGraphForTest shortestPaths(graph, 3);

    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1, 1));
    EXPECT_DOUBLE_EQ(3.5, shortestPaths.getShortestDistance(1, 2));
    EXPECT_DOUBLE_EQ(6, shortestPaths.getShortestDistance(1, 3));
    EXPECT_DOUBLE_EQ(3, shortestPaths.getShortestDistance(1, 4));
    EXPECT_DOUBLE_EQ(6.5, shortestPaths.getShortestDistance(1, 5));
    EXPECT_DOUBLE_EQ(4.5, shortestPaths.getShortestDistance(1, 6));
}

TEST(ShortestDistanceByTraverseCountUsingAdjacencyMatrixTest, GetShortestDistanceWorksWithDirectedGraphOnExample1) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(1, 4, 1.0);
    graph.connect(1, 2, 1.5);
    graph.connect(4, 5, 2.0);
    graph.connect(5, 2, 2.5);
    graph.connect(5, 3, 3.0);
    graph.connect(2, 3, 2.0);
    graph.connect(3, 6, 1.0);
    ShortestPathsForDirectedGraphForTest shortestPaths(graph, 3);

    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1, 1));
    EXPECT_DOUBLE_EQ(5.5, shortestPaths.getShortestDistance(1, 2));
    EXPECT_DOUBLE_EQ(6, shortestPaths.getShortestDistance(1, 3));
    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1, 4));
    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1, 5));
    EXPECT_DOUBLE_EQ(4.5, shortestPaths.getShortestDistance(1, 6));
}

TEST(ShortestDistanceByTraverseCountUsingAdjacencyMatrixTest, GetShortestDistanceWorksWithDirectedGraphOnExample2) {
    EdgeWeightedDirectedGraphForTest graph;
    graph.connect(1, 4, 4.0);
    graph.connect(2, 1, 2.0);
    graph.connect(2, 5, 1.0);
    graph.connect(2, 6, 2.0);
    graph.connect(3, 2, 4.0);
    graph.connect(4, 2, 1.0);
    graph.connect(6, 3, 3.0);
    graph.connect(6, 5, 2.0);
    ShortestPathsForDirectedGraphForTest shortestPaths(graph, 4);

    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1, 1));
    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1, 2));
    EXPECT_DOUBLE_EQ(10, shortestPaths.getShortestDistance(1, 3));
    EXPECT_DOUBLE_EQ(11, shortestPaths.getShortestDistance(1, 4));
    EXPECT_DOUBLE_EQ(9, shortestPaths.getShortestDistance(1, 5));
    EXPECT_DOUBLE_EQ(INFINITY, shortestPaths.getShortestDistance(1, 6));
    EXPECT_DOUBLE_EQ(8, shortestPaths.getShortestDistance(2, 5));
}

}  // namespace algorithm

}  // namespace alba
