#include <Algorithm/Graph/PathSearch/HamiltonianPath/UndirectedGraph/HamiltonianPathSearchForUndirectedGraphWithDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>
namespace alba
{
namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = HamiltonianPathSearchForUndirectedGraphWithDfs<VertexForTest>;
using PathForTest = PathSearchForTest::Path;
using PathsForTest = PathSearchForTest::Paths;
}

TEST(HamiltonianPathSearchForUndirectedGraphWithDfsTest, GetAllHamiltonianPathsWorks)
{
    GraphForTest graph;
    graph.connect(0U, 1U);    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(2U, 3U);
    PathSearchForTest pathSearch(graph);

    PathsForTest pathsToVerify(pathSearch.getAllHamiltonianPaths());

    PathsForTest pathsToExpect
    {{0U, 1U, 2U, 3U}, {0U, 1U, 3U, 2U}, {0U, 2U, 1U, 3U}, {0U, 2U, 3U, 1U}, {1U, 0U, 2U, 3U},
        {1U, 3U, 2U, 0U}, {2U, 0U, 1U, 3U}, {2U, 3U, 1U, 0U}, {3U, 1U, 0U, 2U}, {3U, 1U, 2U, 0U},
        {3U, 2U, 0U, 1U}, {3U, 2U, 1U, 0U}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchForUndirectedGraphWithDfsTest, GetOneHamiltonianPathWorks)
{
    GraphForTest graph;
    graph.connect(0U, 1U);    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(2U, 3U);
    PathSearchForTest pathSearch(graph);

    PathForTest pathsToVerify(pathSearch.getOneHamiltonianPath());

    PathForTest pathsToExpect{0U, 1U, 2U, 3U};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchForUndirectedGraphWithDfsTest, GetAllHamiltonianCyclesWorks)
{
    GraphForTest graph;
    graph.connect(0U, 1U);    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(2U, 3U);
    PathSearchForTest pathSearch(graph);

    PathsForTest pathsToVerify(pathSearch.getAllHamiltonianCycles());

    PathsForTest pathsToExpect
    {{0U, 1U, 3U, 2U, 0U}, {0U, 2U, 3U, 1U, 0U}, {1U, 0U, 2U, 3U, 1U}, {1U, 3U, 2U, 0U, 1U},
        {2U, 0U, 1U, 3U, 2U}, {2U, 3U, 1U, 0U, 2U}, {3U, 1U, 0U, 2U, 3U}, {3U, 2U, 0U, 1U, 3U}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(HamiltonianPathSearchForUndirectedGraphWithDfsTest, GetOneHamiltonianCycleWorks)
{
    GraphForTest graph;
    graph.connect(0U, 1U);    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(2U, 3U);
    PathSearchForTest pathSearch(graph);

    PathForTest pathsToVerify(pathSearch.getOneHamiltonianCycle());

    PathForTest pathsToExpect{0U, 1U, 3U, 2U, 0U};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

}

}
