#include <Algorithm/Graph/DepthFirstSearch/DepthFirstSearch.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using SampleGraphForTest = UndirectedGraphWithListOfEdges;
}

TEST(DepthFirstSearchTest, GetPathsWithStartPointAndEndPointWorks)
{
    SampleGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
    DepthFirstSearch dfs(graph);

    Paths pathsToVerify(dfs.getPathsWithStartPointAndEndPoint(1U, 3U));

    Paths pathsToExpect{{1,0,2,3}, {1,0,2,4,3}, {1,0,5,3}, {1,2,0,5,3}, {1,2,3}, {1,2,4,3}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(DepthFirstSearchTest, GetCompletePathsWorks)
{
    SampleGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
    DepthFirstSearch dfs(graph);

    Paths pathsToVerify(dfs.getCompletePaths());

    Paths pathsToExpect
    {{0,1,2,4,3,5}, {0,5,3,4,2,1}, {1,0,2,4,3,5}, {1,0,5,3,2,4}, {1,0,5,3,4,2}, {1,2,0,5,3,4}, {1,2,4,3,5,0},
        {2,1,0,5,3,4}, {2,4,3,5,0,1}, {3,4,2,1,0,5}, {3,5,0,1,2,4}, {4,2,1,0,5,3}, {4,2,3,5,0,1}, {4,3,2,1,0,5},
        {4,3,5,0,1,2}, {4,3,5,0,2,1}, {5,0,1,2,3,4}, {5,0,1,2,4,3}, {5,3,4,2,0,1}, {5,3,4,2,1,0}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

TEST(DepthFirstSearchTest, TraverseWorks)
{
    SampleGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
    DepthFirstSearch dfs(graph);

    Paths pathsToVerify;
    dfs.traverse(1U, [&](Path const& path, bool &)
    {
        pathsToVerify.emplace_back(path);
    });

    Paths pathsToExpect
    {{1}, {1,0}, {1,0,2}, {1,0,2,3}, {1,0,2,3,4}, {1,0,2,3,5}, {1,0,2,4}, {1,0,2,4,3}, {1,0,2,4,3,5}, {1,0,5}, {1,0,5,3},
        {1,0,5,3,2}, {1,0,5,3,2,4}, {1,0,5,3,4}, {1,0,5,3,4,2}, {1,2}, {1,2,0}, {1,2,0,5}, {1,2,0,5,3}, {1,2,0,5,3,4}, {1,2,3},
        {1,2,3,4}, {1,2,3,5}, {1,2,3,5,0}, {1,2,4}, {1,2,4,3}, {1,2,4,3,5}, {1,2,4,3,5,0}};
    EXPECT_EQ(pathsToExpect, pathsToVerify);
}

}

}
