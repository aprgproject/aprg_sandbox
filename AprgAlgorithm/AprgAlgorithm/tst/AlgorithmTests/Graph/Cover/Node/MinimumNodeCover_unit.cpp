#include <Algorithm/Graph/Cover/Node/MinimumNodeCover.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using Edges = typename GraphTypes<VertexForTest>::Edges;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using MinimumNodeCoverForTest = MinimumNodeCover<VertexForTest>;

VertexForTest newSourceVertex = numeric_limits<int>::max();
VertexForTest newSinkVertex = numeric_limits<int>::max() - 1;
}  // namespace

TEST(MinimumNodeCoverTest, GetMinimumNodeCoverSizeWorksOnExample1) {
    GraphForTest graph;
    graph.connect(1, 5);
    graph.connect(2, 7);
    graph.connect(3, 5);
    graph.connect(3, 6);
    graph.connect(3, 8);
    graph.connect(4, 7);
    MinimumNodeCoverForTest minimumNodeCover(graph);

    EXPECT_EQ(3, minimumNodeCover.getMinimumNodeCoverSize(newSourceVertex, newSinkVertex));
}

TEST(MinimumNodeCoverTest, GetMaximumIndependentSetSizeWorksOnExample1) {
    GraphForTest graph;
    graph.connect(1, 5);
    graph.connect(2, 7);
    graph.connect(3, 5);
    graph.connect(3, 6);
    graph.connect(3, 8);
    graph.connect(4, 7);
    MinimumNodeCoverForTest minimumNodeCover(graph);

    EXPECT_EQ(5, minimumNodeCover.getMaximumIndependentSetSize(newSourceVertex, newSinkVertex));
}

}  // namespace algorithm

}  // namespace alba
