#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DisjointPaths/EdgeDisjointPaths.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using PathsForTest = typename GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = EdgeDisjointPaths<VertexForTest>;
}  // namespace

TEST(EdgeDisjointPathsTest, Example1Works) {
    GraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 4U);
    graph.connect(2U, 4U);
    graph.connect(3U, 2U);
    graph.connect(3U, 5U);
    graph.connect(3U, 6U);
    graph.connect(4U, 3U);
    graph.connect(4U, 5U);
    graph.connect(5U, 6U);
    PathSearchForTest pathSearch(graph, 1U, 6U);

    PathsForTest expectedEdgeDisjointPaths{{1U, 4U, 3U, 6U}, {1U, 2U, 4U, 5U, 6U}};
    EXPECT_EQ(2U, pathSearch.getNumberOfEdgeDisjointPaths());
    EXPECT_EQ(expectedEdgeDisjointPaths, pathSearch.getEdgeDisjointPaths());
}

}  // namespace algorithm

}  // namespace alba
