#include <Algorithm/Graph/Tree/ChildrenInTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using QueryForTest = ChildrenInTree<VertexForTest>;
using VerticesForTest = QueryForTest::Vertices;
}  // namespace

TEST(ChildrenInTreeTest, GetChildrenWorks) {
    GraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(4, 3);
    graph.connect(4, 7);
    graph.connect(7, 8);
    QueryForTest query(graph, 1);

    EXPECT_EQ((VerticesForTest{2, 4, 5}), query.getChildren(1));
    EXPECT_EQ((VerticesForTest{6}), query.getChildren(2));
    EXPECT_EQ((VerticesForTest{3, 7}), query.getChildren(4));
    EXPECT_EQ((VerticesForTest{8}), query.getChildren(7));
}

}  // namespace algorithm

}  // namespace alba
