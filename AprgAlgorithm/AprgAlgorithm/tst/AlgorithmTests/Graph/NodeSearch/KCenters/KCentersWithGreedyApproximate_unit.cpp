#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/NodeSearch/KCenters/KCentersWithGreedyApproximate.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using WeightForTest = double;
using VerticesForTest = GraphTypes<VertexForTest>::Vertices;
using ContentMapForTest = GraphTypesWithWeights<VertexForTest, WeightForTest>::VertexToWeightMap;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using NodeSearchForTest =
    KCentersWithGreedyApproximate<VertexForTest, WeightForTest, EdgeWeightedUndirectedGraphForTest>;
}  // namespace

TEST(KCentersWithGreedyApproximateTest, GetDistanceToWorksWithUndirectedGraphForExample1) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0, 1, 0.05);
    graph.connect(0, 2, 0.10);
    graph.connect(0, 5, 0.15);
    graph.connect(1, 2, 0.20);
    graph.connect(2, 3, 0.25);
    graph.connect(2, 4, 0.30);
    graph.connect(3, 4, 0.35);
    graph.connect(3, 5, 0.40);
    NodeSearchForTest nodeSearch(graph, 0, 3);

    VerticesForTest expectedCenters{0, 4, 3};
    EXPECT_EQ(expectedCenters, nodeSearch.getFoundCenters());
}

TEST(KCentersWithGreedyApproximateTest, GetDistanceToWorksWithUndirectedGraphForExample2) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0, 1, 1.0);
    graph.connect(0, 2, 0.7);
    graph.connect(0, 3, 0.6);
    graph.connect(1, 2, 0.8);
    graph.connect(1, 3, 0.5);
    graph.connect(2, 3, 1.2);
    NodeSearchForTest nodeSearch(graph, 2, 2);

    VerticesForTest expectedCenters{2, 3};
    EXPECT_EQ(expectedCenters, nodeSearch.getFoundCenters());
}

}  // namespace algorithm

}  // namespace alba
