#include <Algorithm/Graph/PathSearch/HamiltonianPath/HamiltonianPathSearchWithDfs.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = HamiltonianPathSearchWithDfs<VertexForTest>;
using PathForTest = PathSearchForTest::Path;
using PathsForTest = PathSearchForTest::Paths;
}

TEST(HamiltonianPathSearchWithDfsTest_ForDirectedGraph, GetAllHamiltonianPathsWorks)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(3U, 0U);
    PathSearchForTest pathSearch(graph);

    PathsForTest pathsToVerify(pathSearch.getAllHamiltonianPaths());

    PathsForTest pathsToExpect
    {{0U, 1U, 2U, 3U}, {1U, 2U, 3U, 0U}, {2U, 3U, 0U, 1U}, {3U, 0U, 1U, 2U}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTest_ForDirectedGraph, GetOneHamiltonianPathWorks)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(3U, 0U);
    PathSearchForTest pathSearch(graph);

    PathForTest pathsToVerify(pathSearch.getOneHamiltonianPath());

    PathForTest pathsToExpect{0U, 1U, 2U, 3U};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTest_ForDirectedGraph, GetAllHamiltonianCyclesWorks)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(3U, 0U);
    PathSearchForTest pathSearch(graph);

    PathsForTest pathsToVerify(pathSearch.getAllHamiltonianCycles());

    PathsForTest pathsToExpect
    {{0U, 1U, 2U, 3U, 0U}, {1U, 2U, 3U, 0U, 1U}, {2U, 3U, 0U, 1U, 2U}, {3U, 0U, 1U, 2U, 3U}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchWithDfsTest_ForDirectedGraph, GetOneHamiltonianCycleWorks)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(3U, 0U);
    PathSearchForTest pathSearch(graph);

    PathForTest pathsToVerify(pathSearch.getOneHamiltonianCycle());

    PathForTest pathsToExpect{0U, 1U, 2U, 3U, 0U};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

}

}
