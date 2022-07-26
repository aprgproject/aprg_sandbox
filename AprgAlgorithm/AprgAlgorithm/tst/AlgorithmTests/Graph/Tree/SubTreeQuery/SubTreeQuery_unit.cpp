#include <Algorithm/Graph/Tree/SubTreeQuery/SubTreeQuery.hpp>
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
using SubTreeQueryForTest = SubTreeQuery<VertexForTest>;
using VerticesForTest = SubTreeQueryForTest::Vertices;
using CountsForTest = SubTreeQueryForTest::Counts;
}

TEST(SubTreeQueryTest, Example1Works)
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
    SubTreeQueryForTest subTreeQuery(graph, 1U);

    VerticesForTest expectedVertices{1U, 2U, 6U, 3U, 4U, 7U, 8U, 9U, 5U};
    CountsForTest expectedSizes{9U, 2U, 1U, 1U, 4U, 1U, 1U, 1U, 1U};
    VerticesForTest expectedVerticesOfSubTreeAt4{4U, 7U, 8U, 9U};
    EXPECT_EQ(expectedVertices, subTreeQuery.getVerticesInDfsPreOrder());
    EXPECT_EQ(expectedSizes, subTreeQuery.getSubTreeSize());
    EXPECT_EQ(expectedVerticesOfSubTreeAt4, subTreeQuery.getVerticesOfSubTreeAt(4U));
}

}

}
