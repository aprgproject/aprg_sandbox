#include <Algorithm/Graph/Cover/Path/NodeDisjointPathCover.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using Edges = typename GraphTypes<VertexForTest>::Edges;
using Paths = typename GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using NodeDisjointPathCoverForTest = NodeDisjointPathCover<VertexForTest>;

VertexForTest newSourceVertex = 0xFFFFFFFEU;
VertexForTest newSinkVertex = 0xFFFFFFFFU;
}

TEST(NodeDisjointPathCoverTest, GetNodeDisjointPathCoverWorksOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(3U, 4U);
    graph.connect(5U, 6U);
    graph.connect(6U, 3U);
    graph.connect(6U, 7U);
    NodeDisjointPathCoverForTest nodeDisjointPathCover(graph);

    Paths expectedPaths{{1U, 5U}, {2U, 6U, 3U, 4U}, {7U}};
    EXPECT_EQ(expectedPaths, nodeDisjointPathCover.getNodeDisjointPathCover(newSourceVertex, newSinkVertex));
}

TEST(NodeDisjointPathCoverTest, GetEdgesOfNodeDisjointPathCoverWorksOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(3U, 4U);
    graph.connect(5U, 6U);
    graph.connect(6U, 3U);
    graph.connect(6U, 7U);
    NodeDisjointPathCoverForTest nodeDisjointPathCover(graph);

    Edges expectedEdges{{1U, 5U}, {2U, 6U}, {3U, 4U}, {6U, 3U}};
    EXPECT_EQ(expectedEdges, nodeDisjointPathCover.getEdgesOfNodeDisjointPathCover(newSourceVertex, newSinkVertex));
}

}

}
