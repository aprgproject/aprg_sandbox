#include <Algorithm/Graph/Tree/SubTreeQuery/SubTreeQueryWithAccumulator.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using SubTreeQueryForTest = SubTreeQueryWithAccumulator<VertexForTest>;
using VerticesForTest = SubTreeQueryForTest::Vertices;
using RangeQueryForTest = SubTreeQueryForTest::RangeQuery;
using CountsForTest = SubTreeQueryForTest::Counts;
RangeQueryForTest::AccumulatorFunction plusAccumulator = plus<>();
RangeQueryForTest::AccumulatorFunction minusAccumulator = minus<>();
}  // namespace

TEST(SubTreeQueryWithAccumulatorTest, GetAccumulatedValueOfSubTreeAtWorks) {
    GraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(4, 7);
    graph.connect(4, 8);
    graph.connect(4, 9);
    SubTreeQueryForTest subTreeQuery(graph, 1, plusAccumulator, minusAccumulator);

    EXPECT_EQ(45, subTreeQuery.getAccumulatedValueOfSubTreeAt(1));
    EXPECT_EQ(28, subTreeQuery.getAccumulatedValueOfSubTreeAt(4));
}

}  // namespace algorithm

}  // namespace alba
