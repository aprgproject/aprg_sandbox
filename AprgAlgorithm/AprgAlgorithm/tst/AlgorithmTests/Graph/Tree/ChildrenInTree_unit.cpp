#include <Algorithm/Graph/Tree/ChildrenInTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using QueryForTest = ChildrenInTree<VertexForTest>;
using VerticesForTest = QueryForTest::Vertices;
}  // namespace

TEST(ChildrenInTreeTest, GetChildrenWorks) {
    GraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 4U);
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 3U);
    graph.connect(4U, 7U);
    graph.connect(7U, 8U);
    QueryForTest query(graph, 1U);

    EXPECT_EQ((VerticesForTest{2U, 4U, 5U}), query.getChildren(1U));
    EXPECT_EQ((VerticesForTest{6U}), query.getChildren(2U));
    EXPECT_EQ((VerticesForTest{3U, 7U}), query.getChildren(4U));
    EXPECT_EQ((VerticesForTest{8U}), query.getChildren(7U));
}

}  // namespace algorithm

}  // namespace alba
