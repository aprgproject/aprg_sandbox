#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/BreadthFirstSearch.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using SampleGraphForTest = UndirectedGraphWithListOfEdges;

void putConnectionsForTest(SampleGraphForTest & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 5U);    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
}
}

TEST(BreadthFirstSearchTest, HasPathToWorks)
{
    SampleGraphForTest graph;
    putConnectionsForTest(graph);
    BreadthFirstSearch dfs(graph, 0U);

    EXPECT_TRUE(dfs.hasPathTo(0U));    EXPECT_TRUE(dfs.hasPathTo(1U));
    EXPECT_TRUE(dfs.hasPathTo(2U));
    EXPECT_TRUE(dfs.hasPathTo(3U));
    EXPECT_TRUE(dfs.hasPathTo(4U));
    EXPECT_TRUE(dfs.hasPathTo(5U));
    EXPECT_FALSE(dfs.hasPathTo(6U));
}

TEST(BreadthFirstSearchTest, GetOrderedPathToWorks)
{
    SampleGraphForTest graph;
    putConnectionsForTest(graph);
    BreadthFirstSearch dfs(graph, 0U);

    Path pathWith0{0U};    Path pathWith1{0U, 1U};
    Path pathWith2{0U, 2U};
    Path pathWith3{0U, 2U, 3U};
    Path pathWith4{0U, 2U, 4U};
    Path pathWith5{0U, 5U};
    Path pathWith6;
    EXPECT_EQ(pathWith0, dfs.getShortestPathTo(0U));
    EXPECT_EQ(pathWith1, dfs.getShortestPathTo(1U));
    EXPECT_EQ(pathWith2, dfs.getShortestPathTo(2U));
    EXPECT_EQ(pathWith3, dfs.getShortestPathTo(3U));
    EXPECT_EQ(pathWith4, dfs.getShortestPathTo(4U));
    EXPECT_EQ(pathWith5, dfs.getShortestPathTo(5U));
    EXPECT_EQ(pathWith6, dfs.getShortestPathTo(6U));
}

TEST(BreadthFirstSearchTest, GetIsProcessedMapWorks)
{
    SampleGraphForTest graph;
    putConnectionsForTest(graph);
    BreadthFirstSearch dfs(graph, 0U);

    BreadthFirstSearch::IsProcessedMap const& mapToVerify(dfs.getIsProcessedMap());

    BreadthFirstSearch::IsProcessedMap mapToExpect{{0U, true}, {1U, true}, {2U, true}, {3U, true}, {4U, true}, {5U, true}};
    EXPECT_EQ(mapToExpect, mapToVerify);
}

TEST(BreadthFirstSearchTest, ReinitializeStartingFromWorks)
{
    SampleGraphForTest graph;
    putConnectionsForTest(graph);
    BreadthFirstSearch dfs(graph, 0U);

    dfs.reinitializeStartingFrom(3U);
    Path pathWith0{3U, 2U, 0U};
    Path pathWith1{3U, 2U, 1U};
    Path pathWith2{3U, 2U};
    Path pathWith3{3U};
    Path pathWith4{3U, 4U};
    Path pathWith5{3U, 5U};
    Path pathWith6;
    EXPECT_EQ(pathWith0, dfs.getShortestPathTo(0U));
    EXPECT_EQ(pathWith1, dfs.getShortestPathTo(1U));
    EXPECT_EQ(pathWith2, dfs.getShortestPathTo(2U));
    EXPECT_EQ(pathWith3, dfs.getShortestPathTo(3U));
    EXPECT_EQ(pathWith4, dfs.getShortestPathTo(4U));
    EXPECT_EQ(pathWith5, dfs.getShortestPathTo(5U));
    EXPECT_EQ(pathWith6, dfs.getShortestPathTo(6U));
}

}

}
