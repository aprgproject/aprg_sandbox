#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DisjointPaths/EdgeDisjointPaths.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using PathsForTest = typename GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = EdgeDisjointPaths<VertexForTest>;
}  // namespace

TEST(EdgeDisjointPathsTest, Example1Works) {
    GraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 4);
    graph.connect(2, 4);
    graph.connect(3, 2);
    graph.connect(3, 5);
    graph.connect(3, 6);
    graph.connect(4, 3);
    graph.connect(4, 5);
    graph.connect(5, 6);
    PathSearchForTest pathSearch(graph, 1, 6);

    PathsForTest expectedEdgeDisjointPaths{{1, 4, 3, 6}, {1, 2, 4, 5, 6}};
    EXPECT_EQ(2, pathSearch.getNumberOfEdgeDisjointPaths());
    EXPECT_EQ(expectedEdgeDisjointPaths, pathSearch.getEdgeDisjointPaths());
}

}  // namespace algorithm

}  // namespace alba
