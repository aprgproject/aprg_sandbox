#include <Algorithm/Graph/Cover/Node/MinimumNodeCoverForTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using SetOfVertices = typename GraphTypes<VertexForTest>::SetOfVertices;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using MinimumNodeCoverForTreeForTest = MinimumNodeCoverForTree<VertexForTest>;
}  // namespace

TEST(MinimumNodeCoverForTreeTest, GetMinimumNodeCoverWorksOnExample1) {
    GraphForTest graph;
    graph.connect(10, 20);
    graph.connect(10, 30);
    graph.connect(20, 40);
    graph.connect(20, 50);
    graph.connect(30, 60);
    graph.connect(50, 70);
    graph.connect(50, 80);
    MinimumNodeCoverForTreeForTest minimumNodeCover(graph, 10);

    EXPECT_EQ(3, minimumNodeCover.getMinimumNodeCoverSize());
    EXPECT_EQ((SetOfVertices{20, 30, 50}), minimumNodeCover.getMinimumNodeCover());
}

TEST(MinimumNodeCoverForTreeTest, GetMinimumNodeCoverWorksOnExample2) {
    GraphForTest graph;
    graph.connect(1, 2);
    graph.connect(1, 4);
    graph.connect(1, 5);
    graph.connect(2, 6);
    graph.connect(4, 3);
    graph.connect(4, 7);
    graph.connect(7, 8);
    MinimumNodeCoverForTreeForTest minimumNodeCover(graph, 1);

    EXPECT_EQ(4, minimumNodeCover.getMinimumNodeCoverSize());
    EXPECT_EQ((SetOfVertices{1, 2, 4, 7}), minimumNodeCover.getMinimumNodeCover());
}

}  // namespace algorithm

}  // namespace alba
