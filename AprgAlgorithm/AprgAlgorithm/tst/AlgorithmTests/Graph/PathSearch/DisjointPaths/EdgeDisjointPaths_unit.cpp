#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DisjointPaths/EdgeDisjointPaths.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using EdgeDisjointPathsForTest = EdgeDisjointPaths<VertexForTest>;
}

TEST(EdgeDisjointPathsTest, GetNumberOfEdgeDisjointPathsWorksOnExample1)
{
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

    EdgeDisjointPathsForTest edgeDisjointPaths;
    EXPECT_EQ(2U, edgeDisjointPaths.getNumberOfEdgeDisjointPaths(graph, 1U, 6U));
}

}

}
