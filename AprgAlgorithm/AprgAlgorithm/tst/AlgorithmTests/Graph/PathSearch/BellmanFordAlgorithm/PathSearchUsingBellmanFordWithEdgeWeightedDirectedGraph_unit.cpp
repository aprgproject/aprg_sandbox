#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/BellmanFordAlgorithm/PathSearchUsingBellmanFord.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using WeightForTest = double;
using PathForTest = GraphTypes<VertexForTest>::Path;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedDirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, DirectedGraphForTest>;
using ShortestPathSearchForTest = PathSearchUsingBellmanFord<VertexForTest, WeightForTest, EdgeWeightedDirectedGraphForTest, std::less>;
using LongestPathSearchForTest = PathSearchUsingBellmanFord<VertexForTest, WeightForTest, EdgeWeightedDirectedGraphForTest, std::greater>;

void putConnectionsWithCyclesForTest(EdgeWeightedDirectedGraphForTest & graph)
{
    graph.connect(0U, 1U, 0.26);
    graph.connect(1U, 2U, 0.38);
    graph.connect(2U, 3U, 0.29);
    graph.connect(3U, 0U, 0.34);
}

void putConnectionsWithNoCyclesForTest(EdgeWeightedDirectedGraphForTest & graph)
{
    graph.connect(0U, 2U, 0.26);
    graph.connect(0U, 4U, 0.38);
    graph.connect(1U, 3U, 0.29);
    graph.connect(2U, 7U, 0.34);
    graph.connect(3U, 6U, 0.52);
    graph.connect(4U, 5U, 0.35);
    graph.connect(4U, 7U, 0.37);
    graph.connect(5U, 1U, 0.32);
    graph.connect(5U, 7U, 0.28);
    graph.connect(7U, 3U, 0.39);
}
}

TEST(PathSearchUsingBellmanFordTest, StillProcessWhenThereAreCycles)
{
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithCyclesForTest(graph);
    ShortestPathSearchForTest pathSearch(graph, 0U);

    PathForTest pathWith0;
    PathForTest pathWith1{0U, 1U};
    PathForTest pathWith2{0U, 1U, 2U};
    PathForTest pathWith3{0U, 1U, 2U, 3U};
    PathForTest pathWith4;
    EXPECT_TRUE(pathSearch.hasPathTo(0U));
    EXPECT_TRUE(pathSearch.hasPathTo(1U));
    EXPECT_TRUE(pathSearch.hasPathTo(2U));
    EXPECT_TRUE(pathSearch.hasPathTo(3U));
    EXPECT_FALSE(pathSearch.hasPathTo(4U));
    EXPECT_EQ(pathWith0, pathSearch.getPathTo(0U));
    EXPECT_EQ(pathWith1, pathSearch.getPathTo(1U));
    EXPECT_EQ(pathWith2, pathSearch.getPathTo(2U));
    EXPECT_EQ(pathWith3, pathSearch.getPathTo(3U));
    EXPECT_EQ(pathWith4, pathSearch.getPathTo(4U));
}

TEST(PathSearchUsingBellmanFordTest, HasPathToWorksWithEdgeWeightedDirectedGraphAndLesserComparison)
{
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithNoCyclesForTest(graph);
    ShortestPathSearchForTest pathSearch(graph, 0U);

    EXPECT_FALSE(pathSearch.hasPathTo(0U));
    EXPECT_TRUE(pathSearch.hasPathTo(1U));
    EXPECT_TRUE(pathSearch.hasPathTo(2U));
    EXPECT_TRUE(pathSearch.hasPathTo(3U));
    EXPECT_TRUE(pathSearch.hasPathTo(4U));
    EXPECT_TRUE(pathSearch.hasPathTo(5U));
    EXPECT_TRUE(pathSearch.hasPathTo(6U));
    EXPECT_TRUE(pathSearch.hasPathTo(7U));
    EXPECT_FALSE(pathSearch.hasPathTo(8U));
}

TEST(PathSearchUsingBellmanFordTest, GetPathToWorksWithEdgeWeightedDirectedGraphAndLesserComparison)
{
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithNoCyclesForTest(graph);
    ShortestPathSearchForTest pathSearch(graph, 0U);

    PathForTest pathWith0;
    PathForTest pathWith1{0U, 4U, 5U, 1U};
    PathForTest pathWith2{0U, 2U};
    PathForTest pathWith3{0U, 2U, 7U, 3U};
    PathForTest pathWith4{0U, 4U};
    PathForTest pathWith5{0U, 4U, 5U};
    PathForTest pathWith6{0U, 2U, 7U, 3U, 6U};
    PathForTest pathWith7{0U, 2U, 7U};
    PathForTest pathWith8;
    EXPECT_EQ(pathWith0, pathSearch.getPathTo(0U));
    EXPECT_EQ(pathWith1, pathSearch.getPathTo(1U));
    EXPECT_EQ(pathWith2, pathSearch.getPathTo(2U));
    EXPECT_EQ(pathWith3, pathSearch.getPathTo(3U));
    EXPECT_EQ(pathWith4, pathSearch.getPathTo(4U));
    EXPECT_EQ(pathWith5, pathSearch.getPathTo(5U));
    EXPECT_EQ(pathWith6, pathSearch.getPathTo(6U));
    EXPECT_EQ(pathWith7, pathSearch.getPathTo(7U));
    EXPECT_EQ(pathWith8, pathSearch.getPathTo(8U));
}

TEST(PathSearchUsingBellmanFordTest, HasPathToWorksWithEdgeWeightedDirectedGraphAndGreaterComparison)
{
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithNoCyclesForTest(graph);
    LongestPathSearchForTest pathSearch(graph, 0U);

    EXPECT_FALSE(pathSearch.hasPathTo(0U));
    EXPECT_TRUE(pathSearch.hasPathTo(1U));
    EXPECT_TRUE(pathSearch.hasPathTo(2U));
    EXPECT_TRUE(pathSearch.hasPathTo(3U));
    EXPECT_TRUE(pathSearch.hasPathTo(4U));
    EXPECT_TRUE(pathSearch.hasPathTo(5U));
    EXPECT_TRUE(pathSearch.hasPathTo(6U));
    EXPECT_TRUE(pathSearch.hasPathTo(7U));
    EXPECT_FALSE(pathSearch.hasPathTo(8U));
}

TEST(PathSearchUsingBellmanFordTest, GetPathToWorksWithEdgeWeightedDirectedGraphAndGreaterComparison)
{
    EdgeWeightedDirectedGraphForTest graph;
    putConnectionsWithNoCyclesForTest(graph);
    LongestPathSearchForTest pathSearch(graph, 0U);

    PathForTest pathWith0;
    PathForTest pathWith1{0U, 4U, 5U, 1U};
    PathForTest pathWith2{0U, 2U};
    PathForTest pathWith3{0U, 4U, 5U, 7U, 3U};
    PathForTest pathWith4{0U, 4U};
    PathForTest pathWith5{0U, 4U, 5U};
    PathForTest pathWith6{0U, 4U, 5U, 7U, 3U, 6U};
    PathForTest pathWith7{0U, 4U, 5U, 7U};
    PathForTest pathWith8;
    EXPECT_EQ(pathWith0, pathSearch.getPathTo(0U));
    EXPECT_EQ(pathWith1, pathSearch.getPathTo(1U));
    EXPECT_EQ(pathWith2, pathSearch.getPathTo(2U));
    EXPECT_EQ(pathWith3, pathSearch.getPathTo(3U));
    EXPECT_EQ(pathWith4, pathSearch.getPathTo(4U));
    EXPECT_EQ(pathWith5, pathSearch.getPathTo(5U));
    EXPECT_EQ(pathWith6, pathSearch.getPathTo(6U));
    EXPECT_EQ(pathWith7, pathSearch.getPathTo(7U));
    EXPECT_EQ(pathWith8, pathSearch.getPathTo(8U));
}

}

}
