#include <Algorithm/Graph/Bipartite/MaximumMatchings.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using Edges = typename GraphTypes<VertexForTest>::Edges;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using MaximumMatchingsForTest = MaximumMatchings<VertexForTest>;

VertexForTest newSourceVertex = numeric_limits<int>::max();
VertexForTest newSinkVertex = numeric_limits<int>::max() - 1;
}  // namespace

TEST(MaximumMatchingsTest, GetMaximumMatchingsWorksOnExample1) {
    GraphForTest graph;
    graph.connect(1, 5);
    graph.connect(2, 7);
    graph.connect(3, 5);
    graph.connect(3, 6);
    graph.connect(3, 8);
    graph.connect(4, 7);
    MaximumMatchingsForTest maximumMatchings(graph);

    Edges expectedMatchings{{1, 5}, {2, 7}, {3, 6}};
    EXPECT_EQ(expectedMatchings, maximumMatchings.getMaximumMatchings(newSourceVertex, newSinkVertex));
}

TEST(MaximumMatchingsTest, DoesHavePerfectMatchingByCheckingASubsetWorksOnExample1) {
    GraphForTest graph;
    graph.connect(1, 5);
    graph.connect(2, 7);
    graph.connect(3, 5);
    graph.connect(3, 6);
    graph.connect(3, 8);
    graph.connect(4, 7);
    MaximumMatchingsForTest maximumMatchings(graph);

    EXPECT_TRUE(maximumMatchings.doesHavePerfectMatchingByCheckingASubset({1, 3}));
    EXPECT_FALSE(maximumMatchings.doesHavePerfectMatchingByCheckingASubset({2, 4}));
}

}  // namespace algorithm

}  // namespace alba
