#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/MinimumSpanningTree/PrimAlgorithmLazyVersion.hpp>
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
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using MinimumSpanningTreeSearchForTest = PrimAlgorithmLazyVersion<VertexForTest, WeightForTest, EdgeWeightedUndirectedGraphForTest>;
using Edges = GraphTypes<VertexForTest>::Edges;
}

TEST(PrimAlgorithmLazyVersionTest, WorksOnUndirectedGraph)
{
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0U, 2U, 0.26);
    graph.connect(0U, 4U, 0.38);
    graph.connect(0U, 6U, 0.58);
    graph.connect(0U, 7U, 0.16);
    graph.connect(1U, 2U, 0.36);
    graph.connect(1U, 3U, 0.29);
    graph.connect(1U, 5U, 0.32);
    graph.connect(1U, 7U, 0.19);
    graph.connect(2U, 3U, 0.17);
    graph.connect(2U, 6U, 0.40);
    graph.connect(2U, 7U, 0.34);
    graph.connect(3U, 6U, 0.52);
    graph.connect(4U, 5U, 0.35);
    graph.connect(4U, 6U, 0.93);
    graph.connect(4U, 7U, 0.37);
    graph.connect(5U, 7U, 0.28);

    MinimumSpanningTreeSearchForTest spanningTreeSearch(graph, 0U);

    Edges expectedMinimumSpanningTree
    {{0U, 7U}, {1U, 7U}, {0U, 2U}, {2U, 3U}, {5U, 7U}, {4U, 5U}, {2U, 6U}};
    EXPECT_EQ(expectedMinimumSpanningTree, spanningTreeSearch.getMinimumSpanningTreeEdges());
}

}

}
