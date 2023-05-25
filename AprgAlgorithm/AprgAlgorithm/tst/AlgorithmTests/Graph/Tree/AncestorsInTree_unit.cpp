#include <Algorithm/Graph/Tree/AncestorsInTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using QueryForTest = AncestorsInTree<VertexForTest>;
}  // namespace

TEST(AncestorsInTreeTest, GetAncestorWorks) {
    GraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(4, 3);
    graph.connect(4, 7);
    graph.connect(7, 8);
    QueryForTest query(graph, 1);

    EXPECT_EQ(1, query.getAncestor(2, 1));
    EXPECT_EQ(7, query.getAncestor(8, 1));
    EXPECT_EQ(4, query.getAncestor(8, 2));
    EXPECT_EQ(1, query.getAncestor(8, 3));
}

}  // namespace algorithm

}  // namespace alba
