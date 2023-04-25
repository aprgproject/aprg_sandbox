#include <Algorithm/Graph/Cover/Node/MinimumNodeCoverForTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using SetOfVertices = typename GraphTypes<VertexForTest>::SetOfVertices;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using MinimumNodeCoverForTreeForTest = MinimumNodeCoverForTree<VertexForTest>;
}  // namespace

TEST(MinimumNodeCoverForTreeTest, GetMinimumNodeCoverWorksOnExample1) {
    GraphForTest graph;
    graph.connect(10U, 20U);
    graph.connect(10U, 30U);
    graph.connect(20U, 40U);
    graph.connect(20U, 50U);
    graph.connect(30U, 60U);
    graph.connect(50U, 70U);
    graph.connect(50U, 80U);
    MinimumNodeCoverForTreeForTest minimumNodeCover(graph, 10U);

    EXPECT_EQ(3U, minimumNodeCover.getMinimumNodeCoverSize());
    EXPECT_EQ((SetOfVertices{20U, 30U, 50U}), minimumNodeCover.getMinimumNodeCover());
}

TEST(MinimumNodeCoverForTreeTest, GetMinimumNodeCoverWorksOnExample2) {
    GraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 4U);
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 3U);
    graph.connect(4U, 7U);
    graph.connect(7U, 8U);
    MinimumNodeCoverForTreeForTest minimumNodeCover(graph, 1U);

    EXPECT_EQ(4U, minimumNodeCover.getMinimumNodeCoverSize());
    EXPECT_EQ((SetOfVertices{1U, 2U, 4U, 7U}), minimumNodeCover.getMinimumNodeCover());
}

}  // namespace algorithm

}  // namespace alba
