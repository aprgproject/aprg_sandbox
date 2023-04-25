#include <Algorithm/Graph/Tree/SubTreeQuery/SubTreeQueryWithPathAccumulator.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using SubTreeQueryForTest = SubTreeQueryWithPathAccumulator<VertexForTest>;
using VerticesForTest = SubTreeQueryForTest::Vertices;
using CountsForTest = SubTreeQueryForTest::Counts;
SubTreeQueryForTest::AccumulatorFunction plusAccumulator = plus<>();
}  // namespace

TEST(SubTreeQueryWithPathAccumulatorTest, Example1Works) {
    GraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 7U);
    graph.connect(4U, 8U);
    graph.connect(4U, 9U);
    SubTreeQueryForTest subTreeQuery(graph, 1U, plusAccumulator);

    VerticesForTest expectedVertices{1U, 2U, 6U, 3U, 4U, 7U, 8U, 9U, 5U};
    CountsForTest expectedPathResults{1U, 3U, 9U, 4U, 5U, 12U, 13U, 14U, 6U};
    EXPECT_EQ(expectedVertices, subTreeQuery.getVerticesInDfsPreOrder());
    EXPECT_EQ(expectedPathResults, subTreeQuery.getAccumulatedValuesOfPaths());
    EXPECT_EQ(9U, subTreeQuery.getAccumulatedValueOfPathThatStartsAtTopAndEndsAt(6U));
    EXPECT_EQ(12U, subTreeQuery.getAccumulatedValueOfPathThatStartsAtTopAndEndsAt(7U));
}

}  // namespace algorithm

}  // namespace alba
