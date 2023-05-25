#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DisjointPaths/NodeDisjointPaths.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using PathsForTest = typename GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = NodeDisjointPaths<VertexForTest>;
}  // namespace

TEST(NodeDisjointPathsTest, Example1Works) {
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

    PathsForTest expectedNodeDisjointPaths{{1, 4, 3, 6}};
    EXPECT_EQ(1, pathSearch.getNumberOfNodeDisjointPaths());
    EXPECT_EQ(expectedNodeDisjointPaths, pathSearch.getNodeDisjointPaths());
}

}  // namespace algorithm

}  // namespace alba
