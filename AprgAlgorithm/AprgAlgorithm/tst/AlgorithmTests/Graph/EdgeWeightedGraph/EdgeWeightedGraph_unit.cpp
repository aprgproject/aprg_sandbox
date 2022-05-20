#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{
namespace algorithm
{
namespace
{
using VertexForTest = unsigned int;
using WeightForTest = double;
using WeightsForTest = vector<double>;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using Edges = GraphTypes<VertexForTest>::Edges;using EdgeToWeightMap = EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap;
}

TEST(EdgeWeightedGraphTest, HasAUniqueMinimumSpanningTreeWorksOnUndirectedGraph){
    EdgeWeightedUndirectedGraphForTest graphWithDifferentWeights;
    graphWithDifferentWeights.connect(0U, 1U, 3.5);
    graphWithDifferentWeights.connect(0U, 2U, 4.5);
    EdgeWeightedUndirectedGraphForTest graphWithNonDifferentWeights;
    graphWithNonDifferentWeights.connect(0U, 1U, 3.5);
    graphWithNonDifferentWeights.connect(0U, 2U, 3.5);

    EXPECT_TRUE(graphWithDifferentWeights.hasAUniqueMinimumSpanningTree());
    EXPECT_FALSE(graphWithNonDifferentWeights.hasAUniqueMinimumSpanningTree());
}

TEST(EdgeWeightedGraphTest, GetWeightWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    EXPECT_EQ(3.5, graph.getWeight(0U, 1U));
    EXPECT_EQ(4.5, graph.getWeight(0U, 2U));
    EXPECT_EQ(3.5, graph.getWeight(1U, 0U));
    EXPECT_EQ(4.5, graph.getWeight(2U, 0U));
}

TEST(EdgeWeightedGraphTest, GetSortedWeightsWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    WeightsForTest expectedWeights{3.5, 4.5};
    EXPECT_EQ(expectedWeights, graph.getSortedWeights());
}

TEST(EdgeWeightedGraphTest, GetEdgeToWeightMapWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap expectedEdgesToWeight
    {{{0U, 1U}, 3.5}, {{0U, 2U}, 4.5}};
    EXPECT_EQ(expectedEdgesToWeight, graph.getEdgeToWeightMap());
}

TEST(EdgeWeightedGraphTest, GetEdgesWithWeightWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    EdgeWeightedUndirectedGraphForTest::EdgesWithWeight expectedEdgesWithWeight
    {{0U, 1U, 3.5}, {0U, 2U, 4.5}};
    EXPECT_EQ(expectedEdgesWithWeight, graph.getEdgesWithWeight());
}

TEST(EdgeWeightedGraphTest, ConnectWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    EXPECT_EQ(3U, graph.getNumberOfVertices());
    EXPECT_EQ(2U, graph.getNumberOfEdges());
    Edges edgesToExpect{{0U, 1U}, {0U, 2U}};
    EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap expectedEdgesToWeight
    {{{0U, 1U}, 3.5}, {{0U, 2U}, 4.5}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToWeight, graph.getEdgeToWeightMap());
}

TEST(EdgeWeightedGraphTest, DisconnectWorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 1U, 3.5);
    graph.connect(0U, 2U, 4.5);

    graph.disconnect(0U, 1U);

    EXPECT_EQ(2U, graph.getNumberOfVertices());
    EXPECT_EQ(1U, graph.getNumberOfEdges());
    Edges edgesToExpect{{0U, 2U}};
    EdgeWeightedUndirectedGraphForTest::EdgeToWeightMap expectedEdgesToWeight
    {{{0U, 2U}, 4.5}};
    EXPECT_EQ(edgesToExpect, graph.getEdges());
    EXPECT_EQ(expectedEdgesToWeight, graph.getEdgeToWeightMap());
}

}

}
