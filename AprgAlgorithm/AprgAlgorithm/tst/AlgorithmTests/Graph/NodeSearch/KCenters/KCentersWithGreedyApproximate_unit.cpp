#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/NodeSearch/KCenters/KCentersWithGreedyApproximate.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using WeightForTest = double;
using VerticesForTest = GraphTypes<VertexForTest>::Vertices;
using ContentMapForTest = GraphTypesWithWeights<VertexForTest, WeightForTest>::VertexToWeightMap;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using NodeSearchForTest = KCentersWithGreedyApproximate<VertexForTest, WeightForTest, EdgeWeightedUndirectedGraphForTest>;
}

TEST(KCentersWithGreedyApproximateTest, GetDistanceToWorksWithUndirectedGraphForExample1)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 0.05);
    graph.connect(0U, 2U, 0.10);
    graph.connect(0U, 5U, 0.15);
    graph.connect(1U, 2U, 0.20);
    graph.connect(2U, 3U, 0.25);
    graph.connect(2U, 4U, 0.30);
    graph.connect(3U, 4U, 0.35);
    graph.connect(3U, 5U, 0.40);
    NodeSearchForTest nodeSearch(graph, 0U, 3U);

    VerticesForTest expectedCenters{0U, 4U, 3U};
    EXPECT_EQ(expectedCenters, nodeSearch.getFoundCenters());
}

TEST(KCentersWithGreedyApproximateTest, GetDistanceToWorksWithUndirectedGraphForExample2)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 1.0);
    graph.connect(0U, 2U, 0.7);
    graph.connect(0U, 3U, 0.6);
    graph.connect(1U, 2U, 0.8);
    graph.connect(1U, 3U, 0.5);
    graph.connect(2U, 3U, 1.2);
    NodeSearchForTest nodeSearch(graph, 2U, 2U);

    VerticesForTest expectedCenters{2U, 3U};
    EXPECT_EQ(expectedCenters, nodeSearch.getFoundCenters());
}

}

}
