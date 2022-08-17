#include <Algorithm/Graph/Bipartite/MaximumMatchings.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using Edges = typename GraphTypes<VertexForTest>::Edges;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using MaximumMatchingsForTest = MaximumMatchings<VertexForTest>;

VertexForTest newSourceVertex = 0xFFFFFFFEU;
VertexForTest newSinkVertex = 0xFFFFFFFFU;
}

TEST(MaximumMatchingsTest, GetMaximumMatchingsWorksOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 5U);
    graph.connect(2U, 7U);
    graph.connect(3U, 5U);
    graph.connect(3U, 6U);
    graph.connect(3U, 8U);
    graph.connect(4U, 7U);
    MaximumMatchingsForTest maximumMatchings(graph);

    Edges expectedMatchings{{1U, 5U}, {2U, 7U}, {3U, 6U}};
    EXPECT_EQ(expectedMatchings, maximumMatchings.getMaximumMatchings(newSourceVertex, newSinkVertex));
}

TEST(MaximumMatchingsTest, DoesHavePerfectMatchingByCheckingASubsetWorksOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 5U);
    graph.connect(2U, 7U);
    graph.connect(3U, 5U);
    graph.connect(3U, 6U);
    graph.connect(3U, 8U);
    graph.connect(4U, 7U);
    MaximumMatchingsForTest maximumMatchings(graph);

    EXPECT_TRUE(maximumMatchings.doesHavePerfectMatchingByCheckingASubset({1U, 3U}));
    EXPECT_FALSE(maximumMatchings.doesHavePerfectMatchingByCheckingASubset({2U, 4U}));
}

}

}
