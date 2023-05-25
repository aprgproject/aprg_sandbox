#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithAdjacencyMatrix.hpp>
#include <Algorithm/Graph/PathSearch/CountPaths/CountPathsWithLengthUsingAdjacencyMatrix.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithAdjacencyMatrix.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
constexpr VertexForTest MAX_VERTEX_VALUE = 7;

using UndirectedGraphForTest = UndirectedGraphWithAdjacencyMatrix<VertexForTest, MAX_VERTEX_VALUE>;
using DirectedGraphForTest = DirectedGraphWithAdjacencyMatrix<VertexForTest, MAX_VERTEX_VALUE>;
using CountPathsForTest = CountPathsWithLengthUsingAdjacencyMatrix<VertexForTest>;
}  // namespace

TEST(CountPathsWithLengthUsingAdjacencyMatrixTest, GetCountWorksWithUndirectedGraphOnExample1) {
    UndirectedGraphForTest graph;
    graph.connect(1, 4);
    graph.connect(1, 2);
    graph.connect(4, 5);
    graph.connect(5, 2);
    graph.connect(5, 3);
    graph.connect(2, 3);
    graph.connect(3, 6);
    CountPathsForTest countPaths(3, graph.getAdjacencyMatrix());

    EXPECT_EQ(0, countPaths.getCount(1, 1));
    EXPECT_EQ(5, countPaths.getCount(1, 2));
    EXPECT_EQ(2, countPaths.getCount(1, 3));
    EXPECT_EQ(4, countPaths.getCount(1, 4));
    EXPECT_EQ(1, countPaths.getCount(1, 5));
    EXPECT_EQ(1, countPaths.getCount(1, 6));
}

TEST(CountPathsWithLengthUsingAdjacencyMatrixTest, GetCountWorksWithDirectedGraphOnExample1) {
    DirectedGraphForTest graph;
    graph.connect(1, 4);
    graph.connect(1, 2);
    graph.connect(4, 5);
    graph.connect(5, 2);
    graph.connect(5, 3);
    graph.connect(2, 3);
    graph.connect(3, 6);
    CountPathsForTest countPaths(3, graph.getAdjacencyMatrix());

    EXPECT_EQ(0, countPaths.getCount(1, 1));
    EXPECT_EQ(1, countPaths.getCount(1, 2));
    EXPECT_EQ(1, countPaths.getCount(1, 3));
    EXPECT_EQ(0, countPaths.getCount(1, 4));
    EXPECT_EQ(0, countPaths.getCount(1, 5));
    EXPECT_EQ(1, countPaths.getCount(1, 6));
}

TEST(CountPathsWithLengthUsingAdjacencyMatrixTest, GetCountWorksWithDirectedGraphOnExample2) {
    DirectedGraphForTest graph;
    graph.connect(1, 4);
    graph.connect(2, 1);
    graph.connect(2, 5);
    graph.connect(2, 6);
    graph.connect(3, 2);
    graph.connect(4, 2);
    graph.connect(6, 3);
    graph.connect(6, 5);
    CountPathsForTest countPaths(4, graph.getAdjacencyMatrix());

    EXPECT_EQ(0, countPaths.getCount(1, 1));
    EXPECT_EQ(0, countPaths.getCount(1, 2));
    EXPECT_EQ(1, countPaths.getCount(1, 3));
    EXPECT_EQ(1, countPaths.getCount(1, 4));
    EXPECT_EQ(1, countPaths.getCount(1, 5));
    EXPECT_EQ(0, countPaths.getCount(1, 6));
    EXPECT_EQ(2, countPaths.getCount(2, 5));
}

}  // namespace algorithm

}  // namespace alba
