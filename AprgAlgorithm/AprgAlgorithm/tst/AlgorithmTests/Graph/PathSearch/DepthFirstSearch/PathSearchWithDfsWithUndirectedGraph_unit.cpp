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
    PathSearchForTest pathSearch(graph, 0U);

    EXPECT_TRUE(pathSearch.hasPathTo(0U));
    EXPECT_TRUE(pathSearch.hasPathTo(1U));
    EXPECT_TRUE(pathSearch.hasPathTo(2U));
    EXPECT_TRUE(pathSearch.hasPathTo(3U));
    EXPECT_TRUE(pathSearch.hasPathTo(4U));
    EXPECT_TRUE(pathSearch.hasPathTo(5U));
    EXPECT_FALSE(pathSearch.hasPathTo(6U));
}

TEST(PathSearchUsingDfsTest, GetOrderedPathToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0U));
    EXPECT_EQ(PathForTest({0U, 1U}), pathSearch.getOrderedPathTo(1U));
    EXPECT_EQ(PathForTest({0U, 1U, 2U}), pathSearch.getOrderedPathTo(2U));
    EXPECT_EQ(PathForTest({0U, 1U, 2U, 3U}), pathSearch.getOrderedPathTo(3U));
    EXPECT_EQ(PathForTest({0U, 1U, 2U, 3U, 4U}), pathSearch.getOrderedPathTo(4U));
    EXPECT_EQ(PathForTest({0U, 1U, 2U, 3U, 5U}), pathSearch.getOrderedPathTo(5U));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6U));
}

TEST(PathSearchUsingDfsTest, GetOrderedPathToWorksWithUndirectedGraphWithMultipleStartingPoints)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0U, 3U});

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0U));
    EXPECT_EQ(PathForTest({0U, 1U}), pathSearch.getOrderedPathTo(1U));
    EXPECT_EQ(PathForTest({0U, 1U, 2U}), pathSearch.getOrderedPathTo(2U));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(3U));
    EXPECT_EQ(PathForTest({3U, 4U}), pathSearch.getOrderedPathTo(4U));
    EXPECT_EQ(PathForTest({3U, 5U}), pathSearch.getOrderedPathTo(5U));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6U));
}

TEST(PathSearchUsingDfsTest, GetDistanceToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    EXPECT_EQ(0U, pathSearch.getDistanceTo(0U));
    EXPECT_EQ(1U, pathSearch.getDistanceTo(1U));
    EXPECT_EQ(2U, pathSearch.getDistanceTo(2U));
    EXPECT_EQ(3U, pathSearch.getDistanceTo(3U));
    EXPECT_EQ(4U, pathSearch.getDistanceTo(4U));
    EXPECT_EQ(4U, pathSearch.getDistanceTo(5U));
    EXPECT_EQ(0U, pathSearch.getDistanceTo(6U));
}

TEST(PathSearchUsingDfsTest, ReinitializeStartingFromWorksWithUndirectedGraph)
{
    GraphForTest graph;    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    pathSearch.reinitializeStartingFrom({3U});

    EXPECT_EQ(PathForTest({3U, 2U, 0U}), pathSearch.getOrderedPathTo(0U));    EXPECT_EQ(PathForTest({3U, 2U, 0U, 1U}), pathSearch.getOrderedPathTo(1U));
    EXPECT_EQ(PathForTest({3U, 2U}), pathSearch.getOrderedPathTo(2U));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(3U));
    EXPECT_EQ(PathForTest({3U, 2U, 4U}), pathSearch.getOrderedPathTo(4U));
    EXPECT_EQ(PathForTest({3U, 2U, 0U, 5U}), pathSearch.getOrderedPathTo(5U));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6U));
}

TEST(PathSearchUsingDfsTest, ReinitializeStartingFromWorksWithUndirectedGraphWithMultipleStartingPoints)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    pathSearch.reinitializeStartingFrom({0U, 3U});

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0U));
    EXPECT_EQ(PathForTest({0U, 1U}), pathSearch.getOrderedPathTo(1U));
    EXPECT_EQ(PathForTest({0U, 1U, 2U}), pathSearch.getOrderedPathTo(2U));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(3U));
    EXPECT_EQ(PathForTest({3U, 4U}), pathSearch.getOrderedPathTo(4U));
    EXPECT_EQ(PathForTest({3U, 5U}), pathSearch.getOrderedPathTo(5U));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6U));
}

}

}
