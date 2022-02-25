#include <Algorithm/Graph/DepthFirstSearch/DepthFirstSearch.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using SampleGraphForTest = UndirectedGraphWithListOfEdges;
}

TEST(DepthFirstSearchTest, HasPathToWorks)
{
    SampleGraphForTest graph;
    graph.connect(0U, 1U);    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
    DepthFirstSearch dfs(graph, 0U);

    EXPECT_TRUE(dfs.hasPathTo(0U));
    EXPECT_TRUE(dfs.hasPathTo(1U));
    EXPECT_TRUE(dfs.hasPathTo(2U));
    EXPECT_TRUE(dfs.hasPathTo(3U));
    EXPECT_TRUE(dfs.hasPathTo(4U));
    EXPECT_TRUE(dfs.hasPathTo(5U));
    EXPECT_FALSE(dfs.hasPathTo(6U));
}

TEST(DepthFirstSearchTest, GetOrderedPathToWorks)
{
    SampleGraphForTest graph;
    graph.connect(0U, 1U);    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
    DepthFirstSearch dfs(graph, 0U);

    Path pathWith0{0U};
    Path pathWith1{0U, 1U};
    Path pathWith2{0U, 1U, 2U};
    Path pathWith3{0U, 1U, 2U, 3U};
    Path pathWith4{0U, 1U, 2U, 3U, 4U};
    Path pathWith5{0U, 1U, 2U, 3U, 5U};
    Path pathWith6;
    EXPECT_EQ(pathWith0, dfs.getOrderedPathTo(0U));
    EXPECT_EQ(pathWith1, dfs.getOrderedPathTo(1U));
    EXPECT_EQ(pathWith2, dfs.getOrderedPathTo(2U));
    EXPECT_EQ(pathWith3, dfs.getOrderedPathTo(3U));
    EXPECT_EQ(pathWith4, dfs.getOrderedPathTo(4U));
    EXPECT_EQ(pathWith5, dfs.getOrderedPathTo(5U));
    EXPECT_EQ(pathWith6, dfs.getOrderedPathTo(6U));
}

TEST(DepthFirstSearchTest, ReinitializeStartingFromWorks)
{
    SampleGraphForTest graph;
    graph.connect(0U, 1U);    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
    DepthFirstSearch dfs(graph, 0U);

    dfs.reinitializeStartingFrom(3U);

    Path pathWith0{3U, 2U, 0U};
    Path pathWith1{3U, 2U, 0U, 1U};
    Path pathWith2{3U, 2U};
    Path pathWith3{3U};
    Path pathWith4{3U, 2U, 4U};
    Path pathWith5{3U, 2U, 0U, 5U};
    Path pathWith6;
    EXPECT_EQ(pathWith0, dfs.getOrderedPathTo(0U));
    EXPECT_EQ(pathWith1, dfs.getOrderedPathTo(1U));
    EXPECT_EQ(pathWith2, dfs.getOrderedPathTo(2U));
    EXPECT_EQ(pathWith3, dfs.getOrderedPathTo(3U));
    EXPECT_EQ(pathWith4, dfs.getOrderedPathTo(4U));
    EXPECT_EQ(pathWith5, dfs.getOrderedPathTo(5U));
    EXPECT_EQ(pathWith6, dfs.getOrderedPathTo(6U));
}

}
}