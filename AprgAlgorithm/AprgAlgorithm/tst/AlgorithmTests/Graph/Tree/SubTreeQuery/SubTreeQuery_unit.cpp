#include <Algorithm/Graph/Tree/SubTreeQuery/SubTreeQuery.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using SubTreeQueryForTest = SubTreeQuery<VertexForTest>;
using VerticesForTest = SubTreeQueryForTest::Vertices;
using CountsForTest = SubTreeQueryForTest::Counts;
}  // namespace

TEST(SubTreeQueryTest, Example1Works) {
    GraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(4, 7);
    graph.connect(4, 8);
    graph.connect(4, 9);
    SubTreeQueryForTest subTreeQuery(graph, 1);

    VerticesForTest expectedVertices{1, 2, 6, 3, 4, 7, 8, 9, 5};
    CountsForTest expectedSizes{9, 2, 1, 1, 4, 1, 1, 1, 1};
    VerticesForTest expectedVerticesOfSubTreeAt4{4, 7, 8, 9};
    EXPECT_EQ(expectedVertices, subTreeQuery.getVerticesInDfsPreOrder());
    EXPECT_EQ(expectedSizes, subTreeQuery.getSubTreeSize());
    EXPECT_EQ(expectedVerticesOfSubTreeAt4, subTreeQuery.getVerticesOfSubTreeAt(4));
}

}  // namespace algorithm

}  // namespace alba
