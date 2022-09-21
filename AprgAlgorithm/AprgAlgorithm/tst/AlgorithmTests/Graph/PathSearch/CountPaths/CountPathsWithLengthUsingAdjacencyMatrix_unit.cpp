#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithAdjacencyMatrix.hpp>
#include <Algorithm/Graph/PathSearch/CountPaths/CountPathsWithLengthUsingAdjacencyMatrix.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithAdjacencyMatrix.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
constexpr VertexForTest MAX_VERTEX_VALUE = 7U;

using UndirectedGraphForTest = UndirectedGraphWithAdjacencyMatrix<VertexForTest, MAX_VERTEX_VALUE>;
using DirectedGraphForTest = DirectedGraphWithAdjacencyMatrix<VertexForTest, MAX_VERTEX_VALUE>;
using CountPathsForTest = CountPathsWithLengthUsingAdjacencyMatrix<VertexForTest>;
}

TEST(CountPathsWithLengthUsingAdjacencyMatrixTest, GetCountWorksWithUndirectedGraphOnExample1)
{
    UndirectedGraphForTest graph;
    graph.connect(1U, 4U);
    graph.connect(1U, 2U);
    graph.connect(4U, 5U);
    graph.connect(5U, 2U);
    graph.connect(5U, 3U);
    graph.connect(2U, 3U);
    graph.connect(3U, 6U);
    CountPathsForTest countPaths(3U, graph.getAdjacencyMatrix());

    EXPECT_EQ(0U, countPaths.getCount(1U, 1U));
    EXPECT_EQ(5U, countPaths.getCount(1U, 2U));
    EXPECT_EQ(2U, countPaths.getCount(1U, 3U));
    EXPECT_EQ(4U, countPaths.getCount(1U, 4U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 5U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 6U));
}

TEST(CountPathsWithLengthUsingAdjacencyMatrixTest, GetCountWorksWithDirectedGraphOnExample1)
{
    DirectedGraphForTest graph;
    graph.connect(1U, 4U);
    graph.connect(1U, 2U);
    graph.connect(4U, 5U);
    graph.connect(5U, 2U);
    graph.connect(5U, 3U);
    graph.connect(2U, 3U);
    graph.connect(3U, 6U);
    CountPathsForTest countPaths(3U, graph.getAdjacencyMatrix());

    EXPECT_EQ(0U, countPaths.getCount(1U, 1U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 2U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 3U));
    EXPECT_EQ(0U, countPaths.getCount(1U, 4U));
    EXPECT_EQ(0U, countPaths.getCount(1U, 5U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 6U));
}

TEST(CountPathsWithLengthUsingAdjacencyMatrixTest, GetCountWorksWithDirectedGraphOnExample2)
{
    DirectedGraphForTest graph;
    graph.connect(1U, 4U);
    graph.connect(2U, 1U);
    graph.connect(2U, 5U);
    graph.connect(2U, 6U);
    graph.connect(3U, 2U);
    graph.connect(4U, 2U);
    graph.connect(6U, 3U);
    graph.connect(6U, 5U);
    CountPathsForTest countPaths(4U, graph.getAdjacencyMatrix());

    EXPECT_EQ(0U, countPaths.getCount(1U, 1U));
    EXPECT_EQ(0U, countPaths.getCount(1U, 2U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 3U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 4U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 5U));
    EXPECT_EQ(0U, countPaths.getCount(1U, 6U));
    EXPECT_EQ(2U, countPaths.getCount(2U, 5U));
}

}

}
