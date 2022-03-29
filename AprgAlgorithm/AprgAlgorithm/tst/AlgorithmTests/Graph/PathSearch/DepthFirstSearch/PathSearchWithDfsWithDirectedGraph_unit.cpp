#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = PathSearchUsingDfs<VertexForTest>;

void putConnectionsForTest(GraphForTest & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(2U, 1U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
}
}

TEST(PathSearchUsingDfsTest, HasPathToWorksWithDirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    EXPECT_TRUE(pathSearch.hasPathTo(0U));
    EXPECT_TRUE(pathSearch.hasPathTo(1U));
    EXPECT_TRUE(pathSearch.hasPathTo(2U));
    EXPECT_TRUE(pathSearch.hasPathTo(3U));
    EXPECT_TRUE(pathSearch.hasPathTo(4U));
    EXPECT_TRUE(pathSearch.hasPathTo(5U));
    EXPECT_FALSE(pathSearch.hasPathTo(6U));
}

TEST(PathSearchUsingDfsTest, GetOrderedPathToWorksWithDirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    PathForTest pathWith0;
    PathForTest pathWith1{0U, 1U};
    PathForTest pathWith2{0U, 2U};
    PathForTest pathWith3{0U, 2U, 3U};
    PathForTest pathWith4{0U, 2U, 3U, 4U};
    PathForTest pathWith5{0U, 2U, 3U, 5U};
    PathForTest pathWith6;
    EXPECT_EQ(pathWith0, pathSearch.getOrderedPathTo(0U));
    EXPECT_EQ(pathWith1, pathSearch.getOrderedPathTo(1U));
    EXPECT_EQ(pathWith2, pathSearch.getOrderedPathTo(2U));
    EXPECT_EQ(pathWith3, pathSearch.getOrderedPathTo(3U));
    EXPECT_EQ(pathWith4, pathSearch.getOrderedPathTo(4U));
    EXPECT_EQ(pathWith5, pathSearch.getOrderedPathTo(5U));
    EXPECT_EQ(pathWith6, pathSearch.getOrderedPathTo(6U));
}

TEST(PathSearchUsingDfsTest, ReinitializeStartingFromWorksWithDirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    pathSearch.reinitializeStartingFrom(2U);

    PathForTest pathWith1{2U, 1U};
    PathForTest pathWith2;
    PathForTest pathWith3{2U, 3U};
    PathForTest pathWith4{2U, 3U, 4U};
    PathForTest pathWith5{2U, 3U, 5U};
    EXPECT_TRUE(pathSearch.getOrderedPathTo(0U).empty());
    EXPECT_EQ(pathWith1, pathSearch.getOrderedPathTo(1U));
    EXPECT_EQ(pathWith2, pathSearch.getOrderedPathTo(2U));
    EXPECT_EQ(pathWith3, pathSearch.getOrderedPathTo(3U));
    EXPECT_EQ(pathWith4, pathSearch.getOrderedPathTo(4U));
    EXPECT_EQ(pathWith5, pathSearch.getOrderedPathTo(5U));
    EXPECT_TRUE(pathSearch.getOrderedPathTo(6U).empty());
}

}

}
