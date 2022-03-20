#include <Algorithm/Graph/PathSearch/DepthFirstSearch/DepthFirstSearch.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using VertexToBoolMapForTest = GraphTypes<VertexForTest>::VertexToBoolMap;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using DfsForTest = DepthFirstSearch<VertexForTest>;

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

TEST(DepthFirstSearchTest, HasPathToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);    DfsForTest dfs(graph, 0U);

    EXPECT_TRUE(dfs.hasPathTo(0U));
    EXPECT_TRUE(dfs.hasPathTo(1U));
    EXPECT_TRUE(dfs.hasPathTo(2U));
    EXPECT_TRUE(dfs.hasPathTo(3U));
    EXPECT_TRUE(dfs.hasPathTo(4U));
    EXPECT_TRUE(dfs.hasPathTo(5U));
    EXPECT_FALSE(dfs.hasPathTo(6U));
}

TEST(DepthFirstSearchTest, GetOrderedPathToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);    DfsForTest dfs(graph, 0U);

    PathForTest pathWith0{0U};
    PathForTest pathWith1{0U, 1U};
    PathForTest pathWith2{0U, 1U, 2U};
    PathForTest pathWith3{0U, 1U, 2U, 3U};
    PathForTest pathWith4{0U, 1U, 2U, 3U, 4U};
    PathForTest pathWith5{0U, 1U, 2U, 3U, 5U};
    PathForTest pathWith6;
    EXPECT_EQ(pathWith0, dfs.getOrderedPathTo(0U));
    EXPECT_EQ(pathWith1, dfs.getOrderedPathTo(1U));
    EXPECT_EQ(pathWith2, dfs.getOrderedPathTo(2U));
    EXPECT_EQ(pathWith3, dfs.getOrderedPathTo(3U));
    EXPECT_EQ(pathWith4, dfs.getOrderedPathTo(4U));
    EXPECT_EQ(pathWith5, dfs.getOrderedPathTo(5U));
    EXPECT_EQ(pathWith6, dfs.getOrderedPathTo(6U));
}

TEST(DepthFirstSearchTest, GetIsProcessedMapWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);    DfsForTest dfs(graph, 0U);

    VertexToBoolMapForTest const& mapToVerify(dfs.getIsProcessedMap());

    VertexToBoolMapForTest mapToExpect{{0U, true}, {1U, true}, {2U, true}, {3U, true}, {4U, true}, {5U, true}};
    EXPECT_EQ(mapToExpect, mapToVerify);
}

TEST(DepthFirstSearchTest, ReinitializeStartingFromWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);    DfsForTest dfs(graph, 0U);

    dfs.reinitializeStartingFrom(3U);

    PathForTest pathWith0{3U, 2U, 0U};
    PathForTest pathWith1{3U, 2U, 0U, 1U};
    PathForTest pathWith2{3U, 2U};
    PathForTest pathWith3{3U};
    PathForTest pathWith4{3U, 2U, 4U};
    PathForTest pathWith5{3U, 2U, 0U, 5U};
    EXPECT_EQ(pathWith0, dfs.getOrderedPathTo(0U));
    EXPECT_EQ(pathWith1, dfs.getOrderedPathTo(1U));
    EXPECT_EQ(pathWith2, dfs.getOrderedPathTo(2U));
    EXPECT_EQ(pathWith3, dfs.getOrderedPathTo(3U));
    EXPECT_EQ(pathWith4, dfs.getOrderedPathTo(4U));
    EXPECT_EQ(pathWith5, dfs.getOrderedPathTo(5U));
    EXPECT_TRUE(dfs.getOrderedPathTo(6U).empty());
}

}
}
