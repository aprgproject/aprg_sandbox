#include <Algorithm/Graph/Tree/SubTreeQuery/SubTreeQueryWithAccumulator.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
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
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 7U);
    graph.connect(4U, 8U);
    graph.connect(4U, 9U);
    SubTreeQueryForTest subTreeQuery(graph, 1U, plusAccumulator, minusAccumulator);

    EXPECT_EQ(45U, subTreeQuery.getAccumulatedValueOfSubTreeAt(1U));
    EXPECT_EQ(28U, subTreeQuery.getAccumulatedValueOfSubTreeAt(4U));
}

}  // namespace algorithm

}  // namespace alba
