#include <Algorithm/Graph/Tree/SubTreeQuery/SubTreeQueryWithPathAccumulator.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using SubTreeQueryForTest = SubTreeQueryWithPathAccumulator<VertexForTest>;
using VerticesForTest = SubTreeQueryForTest::Vertices;
using CountsForTest = SubTreeQueryForTest::Counts;
SubTreeQueryForTest::AccumulatorFunction plusAccumulator = plus<>();
}  // namespace

TEST(SubTreeQueryWithPathAccumulatorTest, Example1Works) {
    GraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(4, 7);
    graph.connect(4, 8);
    graph.connect(4, 9);
    SubTreeQueryForTest subTreeQuery(graph, 1, plusAccumulator);

    VerticesForTest expectedVertices{1, 2, 6, 3, 4, 7, 8, 9, 5};
    CountsForTest expectedPathResults{1, 3, 9, 4, 5, 12, 13, 14, 6};
    EXPECT_EQ(expectedVertices, subTreeQuery.getVerticesInDfsPreOrder());
    EXPECT_EQ(expectedPathResults, subTreeQuery.getAccumulatedValuesOfPaths());
    EXPECT_EQ(9, subTreeQuery.getAccumulatedValueOfPathThatStartsAtTopAndEndsAt(6));
    EXPECT_EQ(12, subTreeQuery.getAccumulatedValueOfPathThatStartsAtTopAndEndsAt(7));
}

}  // namespace algorithm

}  // namespace alba
