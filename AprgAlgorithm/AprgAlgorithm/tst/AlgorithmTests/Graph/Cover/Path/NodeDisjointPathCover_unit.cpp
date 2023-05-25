#include <Algorithm/Graph/Cover/Path/NodeDisjointPathCover.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using Edges = typename GraphTypes<VertexForTest>::Edges;
using Paths = typename GraphTypes<VertexForTest>::Paths;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using NodeDisjointPathCoverForTest = NodeDisjointPathCover<VertexForTest>;

VertexForTest newSourceVertex = numeric_limits<int>::max();
VertexForTest newSinkVertex = numeric_limits<int>::max() - 1;
}  // namespace

TEST(NodeDisjointPathCoverTest, GetNodeDisjointPathCoverWorksOnExample1) {
    GraphForTest graph;
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(3, 4);
    graph.connect(5, 6);
    graph.connect(6, 3);
    graph.connect(6, 7);
    NodeDisjointPathCoverForTest nodeDisjointPathCover(graph);

    Paths expectedPaths{{1, 5}, {2, 6, 3, 4}, {7}};
    Edges expectedEdges{{1, 5}, {2, 6}, {3, 4}, {6, 3}};
    EXPECT_EQ(expectedPaths, nodeDisjointPathCover.getNodeDisjointPathCover(newSourceVertex, newSinkVertex));
    EXPECT_EQ(expectedEdges, nodeDisjointPathCover.getEdgesOfNodeDisjointPathCover(newSourceVertex, newSinkVertex));
}

TEST(NodeDisjointPathCoverTest, GetNodeDisjointPathCoverWorksOnExample2) {
    GraphForTest graph;
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(1, 6);
    graph.connect(2, 1);
    graph.connect(2, 4);
    graph.connect(2, 5);
    graph.connect(2, 6);
    graph.connect(2, 7);
    graph.connect(3, 4);
    graph.connect(3, 5);
    graph.connect(3, 6);
    graph.connect(3, 7);
    graph.connect(4, 5);
    graph.connect(7, 5);
    NodeDisjointPathCoverForTest nodeDisjointPathCover(graph);

    Paths expectedPaths{{2, 1, 4, 5}, {3, 6}, {7}};
    Edges expectedEdges{{1, 4}, {2, 1}, {3, 6}, {4, 5}};
    EXPECT_EQ(expectedPaths, nodeDisjointPathCover.getNodeDisjointPathCover(newSourceVertex, newSinkVertex));
    EXPECT_EQ(expectedEdges, nodeDisjointPathCover.getEdgesOfNodeDisjointPathCover(newSourceVertex, newSinkVertex));
}

}  // namespace algorithm

}  // namespace alba
