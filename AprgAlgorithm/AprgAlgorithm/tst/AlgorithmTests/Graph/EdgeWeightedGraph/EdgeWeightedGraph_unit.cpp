#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using WeightForTest = double;
using WeightsForTest = vector<double>;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using Edges = GraphTypes<VertexForTest>::Edges;
using EdgeToWeightMap = EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap;
}  // namespace

TEST(EdgeWeightedGraphTest, HasAUniqueMinimumSpanningTreeWorksOnUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graphWithDifferentWeights;
    graphWithDifferentWeights.connect(0, 1, 3.5);
    graphWithDifferentWeights.connect(0, 2, 4.5);
    EdgeWeightedUndirectedGraphForTest graphWithNonDifferentWeights;
    graphWithNonDifferentWeights.connect(0, 1, 3.5);
    graphWithNonDifferentWeights.connect(0, 2, 3.5);

    EXPECT_TRUE(graphWithDifferentWeights.hasAUniqueMinimumSpanningTree());
    EXPECT_FALSE(graphWithNonDifferentWeights.hasAUniqueMinimumSpanningTree());
}

TEST(EdgeWeightedGraphTest, GetWeightWorksOnUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0, 1, 3.5);
    graph.connect(0, 2, 4.5);

    EXPECT_EQ(3.5, graph.getWeight(0, 1));
    EXPECT_EQ(4.5, graph.getWeight(0, 2));
    EXPECT_EQ(3.5, graph.getWeight(1, 0));
    EXPECT_EQ(4.5, graph.getWeight(2, 0));
}

TEST(EdgeWeightedGraphTest, GetSortedWeightsWorksOnUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0, 1, 3.5);
    graph.connect(0, 2, 4.5);

    WeightsForTest expectedWeights{3.5, 4.5};
    EXPECT_EQ(expectedWeights, graph.getSortedWeights());
}

TEST(EdgeWeightedGraphTest, GetEdgeToWeightMapWorksOnUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0, 1, 3.5);
    graph.connect(0, 2, 4.5);

    EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap expectedEdgesToWeight{{{0, 1}, 3.5}, {{0, 2}, 4.5}};
    EXPECT_EQ(expectedEdgesToWeight, graph.getEdgeToWeightMap());
}

TEST(EdgeWeightedGraphTest, GetEdgesWithWeightWorksOnUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0, 1, 3.5);
    graph.connect(0, 2, 4.5);

    EdgeWeightedUndirectedGraphForTest::EdgesWithWeight expectedEdgesWithWeight{{0, 1, 3.5}, {0, 2, 4.5}};
    EXPECT_EQ(expectedEdgesWithWeight, graph.getEdgesWithWeight());
}

TEST(EdgeWeightedGraphTest, ConnectWorksOnUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0, 1, 3.5);
    graph.connect(0, 2, 4.5);

    EXPECT_EQ(3, graph.getNumberOfVertices());
    EXPECT_EQ(2, graph.getNumberOfEdges());
    Edges edgesToExpect{{0, 1}, {0, 2}};
    EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap expectedEdgesToWeight{{{0, 1}, 3.5}, {{0, 2}, 4.5}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToWeight, graph.getEdgeToWeightMap());
}

TEST(EdgeWeightedGraphTest, DisconnectWorksOnUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0, 1, 3.5);
    graph.connect(0, 2, 4.5);

    graph.disconnect(0, 1);

    EXPECT_EQ(2, graph.getNumberOfVertices());
    EXPECT_EQ(1, graph.getNumberOfEdges());
    Edges edgesToExpect{{0, 2}};
    EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap expectedEdgesToWeight{{{0, 2}, 4.5}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToWeight, graph.getEdgeToWeightMap());
}

}  // namespace algorithm

}  // namespace alba
