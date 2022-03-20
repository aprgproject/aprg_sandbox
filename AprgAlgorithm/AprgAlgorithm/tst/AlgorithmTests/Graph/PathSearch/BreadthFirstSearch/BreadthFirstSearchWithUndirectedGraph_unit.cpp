#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/BreadthFirstSearch.hpp>
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
using BfsForTest = BreadthFirstSearch<VertexForTest>;

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

TEST(BreadthFirstSearchTest, HasPathToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    BfsForTest bfs(graph, 0U);

    EXPECT_TRUE(bfs.hasPathTo(0U));
    EXPECT_TRUE(bfs.hasPathTo(1U));
    EXPECT_TRUE(bfs.hasPathTo(2U));
    EXPECT_TRUE(bfs.hasPathTo(3U));
    EXPECT_TRUE(bfs.hasPathTo(4U));
    EXPECT_TRUE(bfs.hasPathTo(5U));
    EXPECT_FALSE(bfs.hasPathTo(6U));
}

TEST(BreadthFirstSearchTest, GetOrderedPathToWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    BfsForTest bfs(graph, 0U);

    PathForTest pathWith0{0U};
    PathForTest pathWith1{0U, 1U};    PathForTest pathWith2{0U, 2U};
    PathForTest pathWith3{0U, 2U, 3U};
    PathForTest pathWith4{0U, 2U, 4U};
    PathForTest pathWith5{0U, 5U};
    PathForTest pathWith6;
    EXPECT_EQ(pathWith0, bfs.getShortestPathTo(0U));
    EXPECT_EQ(pathWith1, bfs.getShortestPathTo(1U));
    EXPECT_EQ(pathWith2, bfs.getShortestPathTo(2U));
    EXPECT_EQ(pathWith3, bfs.getShortestPathTo(3U));
    EXPECT_EQ(pathWith4, bfs.getShortestPathTo(4U));
    EXPECT_EQ(pathWith5, bfs.getShortestPathTo(5U));
    EXPECT_EQ(pathWith6, bfs.getShortestPathTo(6U));
}

TEST(BreadthFirstSearchTest, GetIsProcessedMapWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    BfsForTest bfs(graph, 0U);

    VertexToBoolMapForTest const& mapToVerify(bfs.getIsProcessedMap());

    VertexToBoolMapForTest mapToExpect{{0U, true}, {1U, true}, {2U, true}, {3U, true}, {4U, true}, {5U, true}};
    EXPECT_EQ(mapToExpect, mapToVerify);
}

TEST(BreadthFirstSearchTest, ReinitializeStartingFromWorksWithUndirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    BfsForTest bfs(graph, 0U);

    bfs.reinitializeStartingFrom(3U);

    PathForTest pathWith0{3U, 2U, 0U};
    PathForTest pathWith1{3U, 2U, 1U};    PathForTest pathWith2{3U, 2U};
    PathForTest pathWith3{3U};
    PathForTest pathWith4{3U, 4U};
    PathForTest pathWith5{3U, 5U};
    EXPECT_EQ(pathWith0, bfs.getShortestPathTo(0U));
    EXPECT_EQ(pathWith1, bfs.getShortestPathTo(1U));
    EXPECT_EQ(pathWith2, bfs.getShortestPathTo(2U));
    EXPECT_EQ(pathWith3, bfs.getShortestPathTo(3U));
    EXPECT_EQ(pathWith4, bfs.getShortestPathTo(4U));
    EXPECT_EQ(pathWith5, bfs.getShortestPathTo(5U));
    EXPECT_TRUE(bfs.getShortestPathTo(6U).empty());
}

}
}
