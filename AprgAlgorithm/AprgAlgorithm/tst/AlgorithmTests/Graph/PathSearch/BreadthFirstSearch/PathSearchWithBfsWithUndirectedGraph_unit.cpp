#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/PathSearchUsingBfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = PathSearchUsingBfs<VertexForTest>;

void putConnectionsForTest(GraphForTest & graph)
{
    graph.connect(0U, 1U);    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
}
}

TEST(PathSearchUsingBfsTest, HasPathToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearchWithBfs(graph, 0U);

    EXPECT_TRUE(pathSearchWithBfs.hasPathTo(0U));
    EXPECT_TRUE(pathSearchWithBfs.hasPathTo(1U));
    EXPECT_TRUE(pathSearchWithBfs.hasPathTo(2U));
    EXPECT_TRUE(pathSearchWithBfs.hasPathTo(3U));
    EXPECT_TRUE(pathSearchWithBfs.hasPathTo(4U));
    EXPECT_TRUE(pathSearchWithBfs.hasPathTo(5U));
    EXPECT_FALSE(pathSearchWithBfs.hasPathTo(6U));
}

TEST(PathSearchUsingBfsTest, GetOrderedPathToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearchWithBfs(graph, 0U);

    PathForTest pathWith0{0U};
    PathForTest pathWith1{0U, 1U};
    PathForTest pathWith2{0U, 2U};
    PathForTest pathWith3{0U, 2U, 3U};
    PathForTest pathWith4{0U, 2U, 4U};
    PathForTest pathWith5{0U, 5U};
    PathForTest pathWith6;
    EXPECT_EQ(pathWith0, pathSearchWithBfs.getShortestPathTo(0U));
    EXPECT_EQ(pathWith1, pathSearchWithBfs.getShortestPathTo(1U));
    EXPECT_EQ(pathWith2, pathSearchWithBfs.getShortestPathTo(2U));
    EXPECT_EQ(pathWith3, pathSearchWithBfs.getShortestPathTo(3U));
    EXPECT_EQ(pathWith4, pathSearchWithBfs.getShortestPathTo(4U));
    EXPECT_EQ(pathWith5, pathSearchWithBfs.getShortestPathTo(5U));
    EXPECT_EQ(pathWith6, pathSearchWithBfs.getShortestPathTo(6U));
}

TEST(PathSearchUsingBfsTest, ReinitializeStartingFromWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearchWithBfs(graph, 0U);

    pathSearchWithBfs.reinitializeStartingFrom(3U);
    PathForTest pathWith0{3U, 2U, 0U};
    PathForTest pathWith1{3U, 2U, 1U};
    PathForTest pathWith2{3U, 2U};
    PathForTest pathWith3{3U};
    PathForTest pathWith4{3U, 4U};
    PathForTest pathWith5{3U, 5U};
    EXPECT_EQ(pathWith0, pathSearchWithBfs.getShortestPathTo(0U));
    EXPECT_EQ(pathWith1, pathSearchWithBfs.getShortestPathTo(1U));
    EXPECT_EQ(pathWith2, pathSearchWithBfs.getShortestPathTo(2U));
    EXPECT_EQ(pathWith3, pathSearchWithBfs.getShortestPathTo(3U));
    EXPECT_EQ(pathWith4, pathSearchWithBfs.getShortestPathTo(4U));
    EXPECT_EQ(pathWith5, pathSearchWithBfs.getShortestPathTo(5U));
    EXPECT_TRUE(pathSearchWithBfs.getShortestPathTo(6U).empty());
}

}

}
