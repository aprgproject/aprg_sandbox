#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/CountPaths/CountPathsInDirectedGraph.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using CountPathsForTest = CountPathsInDirectedGraph<VertexForTest>;
}

TEST(CountPathsInDirectedGraphTest, GetCountWorksOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 4U);
    graph.connect(1U, 2U);
    graph.connect(4U, 5U);
    graph.connect(5U, 2U);
    graph.connect(5U, 3U);
    graph.connect(2U, 3U);
    graph.connect(3U, 6U);
    CountPathsForTest countPaths(graph);

    EXPECT_EQ(1U, countPaths.getCount(1U, 1U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 4U));
    EXPECT_EQ(1U, countPaths.getCount(1U, 5U));
    EXPECT_EQ(2U, countPaths.getCount(1U, 2U));
    EXPECT_EQ(3U, countPaths.getCount(1U, 3U));
    EXPECT_EQ(3U, countPaths.getCount(1U, 6U));
    EXPECT_EQ(0U, countPaths.getCount(5U, 1U));
    EXPECT_EQ(0U, countPaths.getCount(5U, 4U));
    EXPECT_EQ(1U, countPaths.getCount(5U, 5U));
    EXPECT_EQ(1U, countPaths.getCount(5U, 2U));
    EXPECT_EQ(2U, countPaths.getCount(5U, 3U));
    EXPECT_EQ(2U, countPaths.getCount(5U, 6U));
}

}

}
