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
using VertexForTest = int;
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
    graph.connect(1, 2, 3.0);
    graph.connect(1, 3, 5.0);
    graph.connect(2, 3, 2.0);
    graph.connect(2, 4, 4.0);
    graph.connect(2, 5, 8.0);
    graph.connect(3, 4, 2.0);
    graph.connect(4, 5, 1.0);
    ShortestPathSearchForTest pathSearch(graph, 1);

    EdgeWeightedDirectedGraphForTest optimalGraph(
        getOptimalDirectedGraph<EdgeWeightedDirectedGraphForTest, ShortestPathSearchForTest>(pathSearch));

    EdgesWithWeightForTest expectedEdges{{1, 2, 3.0}, {1, 3, 5.0}, {2, 4, 7.0}, {4, 5, 8.0}};
    EXPECT_EQ(expectedEdges, optimalGraph.getEdgesWithWeight());
}

}  // namespace algorithm

}  // namespace alba
