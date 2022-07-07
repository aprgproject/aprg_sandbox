#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/SuccessorGraph/WalkInSuccessorGraph.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using WalkPathsForTest = WalkInSuccessorGraph<VertexForTest>;
}

TEST(WalkInSuccessorGraphTest, WalkWorksOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 3U);
    graph.connect(3U, 7U);
    graph.connect(7U, 1U);
    graph.connect(9U, 3U);
    WalkPathsForTest walkPaths(graph);

    EXPECT_EQ(3U, walkPaths.walk(1U, 1U));
    EXPECT_EQ(7U, walkPaths.walk(1U, 2U));
    EXPECT_EQ(1U, walkPaths.walk(1U, 3U));
    EXPECT_EQ(3U, walkPaths.walk(9U, 1U));
    EXPECT_EQ(7U, walkPaths.walk(9U, 2U));
    EXPECT_EQ(1U, walkPaths.walk(9U, 3U));
}

TEST(WalkInSuccessorGraphTest, WalkWorksOnExample2)
{
    GraphForTest graph;
    graph.connect(4U, 6U);
    graph.connect(8U, 6U);
    graph.connect(6U, 2U);
    graph.connect(2U, 5U);
    graph.connect(5U, 2U);
    WalkPathsForTest walkPaths(graph);

    EXPECT_EQ(6U, walkPaths.walk(4U, 1U));
    EXPECT_EQ(2U, walkPaths.walk(4U, 2U));
    EXPECT_EQ(5U, walkPaths.walk(4U, 3U));
    EXPECT_EQ(2U, walkPaths.walk(4U, 4U));
}

}

}
