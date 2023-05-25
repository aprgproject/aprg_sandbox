#include <Algorithm/Graph/Tree/LowestCommonAncestors.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using LowestCommonAncestorsForTest = LowestCommonAncestors<VertexForTest>;
using VerticesForTest = LowestCommonAncestorsForTest::Vertices;
using DepthsForTest = LowestCommonAncestorsForTest::Depths;
}  // namespace

TEST(LowestCommonAncestorsTest, Example1Works) {
    GraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(4, 7);
    graph.connect(4, 8);
    graph.connect(4, 9);
    LowestCommonAncestorsForTest lowestCommonAncestors(graph, 1);

    VerticesForTest expectedVertices{1, 2, 6, 2, 1, 3, 1, 4, 7, 4, 8, 4, 9, 4, 1, 5, 1};
    DepthsForTest expectedDepth{1, 2, 3, 2, 1, 2, 1, 2, 3, 2, 3, 2, 3, 2, 1, 2, 1};
    EXPECT_EQ(expectedVertices, lowestCommonAncestors.getVerticesInTreeOrder());
    EXPECT_EQ(expectedDepth, lowestCommonAncestors.getDepths());
    EXPECT_EQ(1, lowestCommonAncestors.getLowestCommonAncestor(6, 8));
    EXPECT_EQ(4, lowestCommonAncestors.getLowestCommonAncestor(8, 9));
    EXPECT_EQ(4, lowestCommonAncestors.getDistanceBetweenVertices(6, 8));
    EXPECT_EQ(2, lowestCommonAncestors.getDistanceBetweenVertices(8, 9));
}

TEST(LowestCommonAncestorsTest, Example2Works) {
    GraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(2, 5);
    graph.connect(2, 6);
    graph.connect(4, 7);
    graph.connect(6, 8);
    LowestCommonAncestorsForTest lowestCommonAncestors(graph, 1);

    VerticesForTest expectedVertices{1, 2, 5, 2, 6, 8, 6, 2, 1, 3, 1, 4, 7, 4, 1};
    DepthsForTest expectedDepth{1, 2, 3, 2, 3, 4, 3, 2, 1, 2, 1, 2, 3, 2, 1};
    EXPECT_EQ(expectedVertices, lowestCommonAncestors.getVerticesInTreeOrder());
    EXPECT_EQ(expectedDepth, lowestCommonAncestors.getDepths());
    EXPECT_EQ(1, lowestCommonAncestors.getLowestCommonAncestor(5, 7));
    EXPECT_EQ(2, lowestCommonAncestors.getLowestCommonAncestor(5, 8));
    EXPECT_EQ(4, lowestCommonAncestors.getDistanceBetweenVertices(5, 7));
    EXPECT_EQ(3, lowestCommonAncestors.getDistanceBetweenVertices(5, 8));
}

}  // namespace algorithm

}  // namespace alba
