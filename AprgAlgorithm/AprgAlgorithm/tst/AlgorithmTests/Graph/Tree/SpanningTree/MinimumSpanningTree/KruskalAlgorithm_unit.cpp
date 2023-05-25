#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/Tree/SpanningTree/MinimumSpanningTree/KruskalAlgorithm.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using WeightForTest = double;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using MinimumSpanningTreeSearchForTest =
    KruskalAlgorithm<VertexForTest, WeightForTest, EdgeWeightedUndirectedGraphForTest>;
using Edges = GraphTypes<VertexForTest>::Edges;
}  // namespace

TEST(KruskalAlgorithmTest, WorksOnUndirectedGraph) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(0, 2, 0.26);
    graph.connect(0, 4, 0.38);
    graph.connect(0, 6, 0.58);
    graph.connect(0, 7, 0.16);
    graph.connect(1, 2, 0.36);
    graph.connect(1, 3, 0.29);
    graph.connect(1, 5, 0.32);
    graph.connect(1, 7, 0.19);
    graph.connect(2, 3, 0.17);
    graph.connect(2, 6, 0.40);
    graph.connect(2, 7, 0.34);
    graph.connect(3, 6, 0.52);
    graph.connect(4, 5, 0.35);
    graph.connect(4, 6, 0.93);
    graph.connect(4, 7, 0.37);
    graph.connect(5, 7, 0.28);

    MinimumSpanningTreeSearchForTest spanningTreeSearch(graph, 0);

    Edges expectedMinimumSpanningTree{{0, 7}, {2, 3}, {1, 7}, {0, 2}, {5, 7}, {4, 5}, {2, 6}};
    EXPECT_EQ(expectedMinimumSpanningTree, spanningTreeSearch.getMinimumSpanningTreeEdges());
}

}  // namespace algorithm

}  // namespace alba
