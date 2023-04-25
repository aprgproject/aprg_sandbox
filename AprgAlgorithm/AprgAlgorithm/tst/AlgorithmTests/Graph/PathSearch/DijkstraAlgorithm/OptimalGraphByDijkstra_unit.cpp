#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/EdgeWeightedGraph/EdgeWeightedGraph.hpp>
#include <Algorithm/Graph/PathSearch/DijkstraAlgorithm/OptimalGraphByDijkstra.hpp>
#include <Algorithm/Graph/PathSearch/DijkstraAlgorithm/PathSearchUsingDijkstra.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using WeightForTest = double;
using PathForTest = GraphTypes<VertexForTest>::Path;
using EdgesWithWeightForTest = GraphTypesWithWeights<VertexForTest, WeightForTest>::EdgesWithWeight;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using EdgeWeightedDirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, DirectedGraphForTest>;
using EdgeWeightedUndirectedGraphForTest = EdgeWeightedGraph<VertexForTest, WeightForTest, UndirectedGraphForTest>;
using ShortestPathSearchForTest =
    PathSearchUsingDijkstra<VertexForTest, WeightForTest, EdgeWeightedUndirectedGraphForTest, less>;

}  // namespace

TEST(OptimalGraphByDijkstraTest, GetOptimalDirectedGraph_UndirectedToOptimizedDirectedWorksOnExample1) {
    EdgeWeightedUndirectedGraphForTest graph;
    graph.connect(1U, 2U, 3.0);
    graph.connect(1U, 3U, 5.0);
    graph.connect(2U, 3U, 2.0);
    graph.connect(2U, 4U, 4.0);
    graph.connect(2U, 5U, 8.0);
    graph.connect(3U, 4U, 2.0);
    graph.connect(4U, 5U, 1.0);
    ShortestPathSearchForTest pathSearch(graph, 1U);

    EdgeWeightedDirectedGraphForTest optimalGraph(
        getOptimalDirectedGraph<EdgeWeightedDirectedGraphForTest, ShortestPathSearchForTest>(pathSearch));

    EdgesWithWeightForTest expectedEdges{{1U, 2U, 3.0}, {1U, 3U, 5.0}, {2U, 4U, 7.0}, {4U, 5U, 8.0}};
    EXPECT_EQ(expectedEdges, optimalGraph.getEdgesWithWeight());
}

}  // namespace algorithm

}  // namespace alba
