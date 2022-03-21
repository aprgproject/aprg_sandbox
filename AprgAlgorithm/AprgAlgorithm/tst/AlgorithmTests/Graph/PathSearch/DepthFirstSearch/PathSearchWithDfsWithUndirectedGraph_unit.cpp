#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>
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
using PathSearchForTest = PathSearchUsingDfs<VertexForTest>;
void putConnectionsForTest(GraphForTest & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
}
}

TEST(PathSearchUsingDfsTest, HasPathToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearchWithDfs(graph, 0U);

    EXPECT_TRUE(pathSearchWithDfs.hasPathTo(0U));
    EXPECT_TRUE(pathSearchWithDfs.hasPathTo(1U));
    EXPECT_TRUE(pathSearchWithDfs.hasPathTo(2U));
    EXPECT_TRUE(pathSearchWithDfs.hasPathTo(3U));
    EXPECT_TRUE(pathSearchWithDfs.hasPathTo(4U));
    EXPECT_TRUE(pathSearchWithDfs.hasPathTo(5U));
    EXPECT_FALSE(pathSearchWithDfs.hasPathTo(6U));
}

TEST(PathSearchUsingDfsTest, GetOrderedPathToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearchWithDfs(graph, 0U);

    PathForTest pathWith0{0U};
    PathForTest pathWith1{0U, 1U};
    PathForTest pathWith2{0U, 1U, 2U};
    PathForTest pathWith3{0U, 1U, 2U, 3U};
    PathForTest pathWith4{0U, 1U, 2U, 3U, 4U};
    PathForTest pathWith5{0U, 1U, 2U, 3U, 5U};
    PathForTest pathWith6;
    EXPECT_EQ(pathWith0, pathSearchWithDfs.getOrderedPathTo(0U));
    EXPECT_EQ(pathWith1, pathSearchWithDfs.getOrderedPathTo(1U));
    EXPECT_EQ(pathWith2, pathSearchWithDfs.getOrderedPathTo(2U));
    EXPECT_EQ(pathWith3, pathSearchWithDfs.getOrderedPathTo(3U));
    EXPECT_EQ(pathWith4, pathSearchWithDfs.getOrderedPathTo(4U));
    EXPECT_EQ(pathWith5, pathSearchWithDfs.getOrderedPathTo(5U));
    EXPECT_EQ(pathWith6, pathSearchWithDfs.getOrderedPathTo(6U));
}

TEST(PathSearchUsingDfsTest, ReinitializeStartingFromWorksWithUndirectedGraph)
{
    GraphForTest graph;    putConnectionsForTest(graph);
    PathSearchForTest pathSearchWithDfs(graph, 0U);

    pathSearchWithDfs.reinitializeStartingFrom(3U);

    PathForTest pathWith0{3U, 2U, 0U};
    PathForTest pathWith1{3U, 2U, 0U, 1U};
    PathForTest pathWith2{3U, 2U};
    PathForTest pathWith3{3U};
    PathForTest pathWith4{3U, 2U, 4U};
    PathForTest pathWith5{3U, 2U, 0U, 5U};
    EXPECT_EQ(pathWith0, pathSearchWithDfs.getOrderedPathTo(0U));
    EXPECT_EQ(pathWith1, pathSearchWithDfs.getOrderedPathTo(1U));
    EXPECT_EQ(pathWith2, pathSearchWithDfs.getOrderedPathTo(2U));
    EXPECT_EQ(pathWith3, pathSearchWithDfs.getOrderedPathTo(3U));
    EXPECT_EQ(pathWith4, pathSearchWithDfs.getOrderedPathTo(4U));
    EXPECT_EQ(pathWith5, pathSearchWithDfs.getOrderedPathTo(5U));
    EXPECT_TRUE(pathSearchWithDfs.getOrderedPathTo(6U).empty());
}

}

}
