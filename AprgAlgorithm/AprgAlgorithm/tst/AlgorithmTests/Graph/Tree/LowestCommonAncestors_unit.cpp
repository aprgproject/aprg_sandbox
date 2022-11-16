#include <Algorithm/Graph/Tree/LowestCommonAncestors.hpp>
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
using LowestCommonAncestorsForTest = LowestCommonAncestors<VertexForTest>;
using VerticesForTest = LowestCommonAncestorsForTest::Vertices;
using DepthsForTest = LowestCommonAncestorsForTest::Depths;
}

TEST(LowestCommonAncestorsTest, Example1Works)
{
    GraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 7U);
    graph.connect(4U, 8U);
    graph.connect(4U, 9U);
    LowestCommonAncestorsForTest lowestCommonAncestors(graph, 1U);

    VerticesForTest expectedVertices{1U, 2U, 6U, 2U, 1U, 3U, 1U, 4U, 7U, 4U, 8U, 4U, 9U, 4U, 1U, 5U, 1U};
    DepthsForTest expectedDepth{1U, 2U, 3U, 2U, 1U, 2U, 1U, 2U, 3U, 2U, 3U, 2U, 3U, 2U, 1U, 2U, 1U};
    EXPECT_EQ(expectedVertices, lowestCommonAncestors.getVerticesInTreeOrder());
    EXPECT_EQ(expectedDepth, lowestCommonAncestors.getDepths());
    EXPECT_EQ(1U, lowestCommonAncestors.getLowestCommonAncestor(6U, 8U));
    EXPECT_EQ(4U, lowestCommonAncestors.getLowestCommonAncestor(8U, 9U));
    EXPECT_EQ(4U, lowestCommonAncestors.getDistanceBetweenVertices(6U, 8U));
    EXPECT_EQ(2U, lowestCommonAncestors.getDistanceBetweenVertices(8U, 9U));
}
TEST(LowestCommonAncestorsTest, Example2Works)
{
    GraphForTest graph;    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(2U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 7U);
    graph.connect(6U, 8U);
    LowestCommonAncestorsForTest lowestCommonAncestors(graph, 1U);

    VerticesForTest expectedVertices{1U, 2U, 5U, 2U, 6U, 8U, 6U, 2U, 1U, 3U, 1U, 4U, 7U, 4U, 1U};
    DepthsForTest expectedDepth{1U, 2U, 3U, 2U, 3U, 4U, 3U, 2U, 1U, 2U, 1U, 2U, 3U, 2U, 1U};
    EXPECT_EQ(expectedVertices, lowestCommonAncestors.getVerticesInTreeOrder());
    EXPECT_EQ(expectedDepth, lowestCommonAncestors.getDepths());
    EXPECT_EQ(1U, lowestCommonAncestors.getLowestCommonAncestor(5U, 7U));
    EXPECT_EQ(2U, lowestCommonAncestors.getLowestCommonAncestor(5U, 8U));
    EXPECT_EQ(4U, lowestCommonAncestors.getDistanceBetweenVertices(5U, 7U));
    EXPECT_EQ(3U, lowestCommonAncestors.getDistanceBetweenVertices(5U, 8U));
}
}

}