#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using VerticesForTest = GraphTypes<VertexForTest>::Vertices;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using VertexOrderingForTest = VertexOrderingUsingDfs<VertexForTest>;
}  // namespace

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksWhenGraphIsEmptyWithDirectedGraph) {
    GraphForTest graph;
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(1U, VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(1U, VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(1U, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest preOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    EXPECT_TRUE(preOrderFromAVertex.empty());
    EXPECT_TRUE(postOrderFromAVertex.empty());
    EXPECT_TRUE(reversePostOrderAVertex.empty());
    EXPECT_TRUE(preOrderFromAllVertices.empty());
    EXPECT_TRUE(postOrderFromAllVertices.empty());
    EXPECT_TRUE(reversePostOrderFromAllVertices.empty());
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample1WithDirectedGraph) {
    GraphForTest graph;
    graph.connect(40U, 30U);  // first value set
    graph.connect(40U, 31U);
    graph.connect(40U, 32U);
    graph.connect(40U, 33U);
    graph.connect(30U, 20U);  // second value set
    graph.connect(31U, 21U);
    graph.connect(32U, 22U);
    graph.connect(33U, 23U);
    graph.connect(20U, 10U);  // third value set
    graph.connect(21U, 11U);
    graph.connect(22U, 12U);
    graph.connect(23U, 13U);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(30U, VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(30U, VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(30U, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest preOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderFromAVertex{30U, 20U, 10U};
    VerticesForTest expectedPostOrderFromAVertex{10U, 20U, 30U};
    VerticesForTest expectedReversePostOrderFromAVertex{30U, 20U, 10U};
    VerticesForTest expectedPreOrderFromAllVertices{10U, 11U, 12U, 13U, 20U, 21U, 22U, 23U, 30U, 31U, 32U, 33U, 40U};
    VerticesForTest expectedPostOrderFromAllVertices{10U, 11U, 12U, 13U, 20U, 21U, 22U, 23U, 30U, 31U, 32U, 33U, 40U};
    VerticesForTest expectedReversePostOrderFromAllVertices{40U, 33U, 32U, 31U, 30U, 23U, 22U,
                                                            21U, 20U, 13U, 12U, 11U, 10U};
    EXPECT_EQ(expectedPreOrderFromAVertex, preOrderFromAVertex);
    EXPECT_EQ(expectedPostOrderFromAVertex, postOrderFromAVertex);
    EXPECT_EQ(expectedReversePostOrderFromAVertex, reversePostOrderAVertex);
    EXPECT_EQ(expectedPreOrderFromAllVertices, preOrderFromAllVertices);
    EXPECT_EQ(expectedPostOrderFromAllVertices, postOrderFromAllVertices);
    EXPECT_EQ(expectedReversePostOrderFromAllVertices, reversePostOrderFromAllVertices);
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample2WithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 5U);
    graph.connect(0U, 6U);
    graph.connect(2U, 0U);
    graph.connect(2U, 3U);
    graph.connect(3U, 5U);
    graph.connect(5U, 4U);
    graph.connect(6U, 4U);
    graph.connect(6U, 9U);
    graph.connect(7U, 6U);
    graph.connect(8U, 7U);
    graph.connect(9U, 10U);
    graph.connect(9U, 11U);
    graph.connect(9U, 12U);
    graph.connect(11U, 12U);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(7U, VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(7U, VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(7U, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest preOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderFromAVertex{7U, 6U, 4U, 9U, 10U, 11U, 12U};
    VerticesForTest expectedPostOrderFromAVertex{4U, 10U, 12U, 11U, 9U, 6U, 7U};
    VerticesForTest expectedReversePostOrderFromAVertex{7U, 6U, 9U, 11U, 12U, 10U, 4U};
    VerticesForTest expectedPreOrderFromAllVertices{0U, 1U, 5U, 4U, 6U, 9U, 10U, 11U, 12U, 2U, 3U, 7U, 8U};
    VerticesForTest expectedPostOrderFromAllVertices{1U, 4U, 5U, 10U, 12U, 11U, 9U, 6U, 0U, 3U, 2U, 7U, 8U};
    VerticesForTest expectedReversePostOrderFromAllVertices{8U, 7U, 2U, 3U, 0U, 6U, 9U, 11U, 12U, 10U, 5U, 4U, 1U};
    EXPECT_EQ(expectedPreOrderFromAVertex, preOrderFromAVertex);
    EXPECT_EQ(expectedPostOrderFromAVertex, postOrderFromAVertex);
    EXPECT_EQ(expectedReversePostOrderFromAVertex, reversePostOrderAVertex);
    EXPECT_EQ(expectedPreOrderFromAllVertices, preOrderFromAllVertices);
    EXPECT_EQ(expectedPostOrderFromAllVertices, postOrderFromAllVertices);
    EXPECT_EQ(expectedReversePostOrderFromAllVertices, reversePostOrderFromAllVertices);
}

TEST(VertexOrderingUsingDfsTest, GetVerticesInTopologicalOrderWorksAsInReversePostOrderWithDirectedGraph) {
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 5U);
    graph.connect(0U, 6U);
    graph.connect(2U, 0U);
    graph.connect(2U, 3U);
    graph.connect(3U, 5U);
    graph.connect(5U, 4U);
    graph.connect(6U, 4U);
    graph.connect(6U, 9U);
    graph.connect(7U, 6U);
    graph.connect(8U, 7U);
    graph.connect(9U, 10U);
    graph.connect(9U, 11U);
    graph.connect(9U, 12U);
    graph.connect(11U, 12U);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest pathFromAVertex(vertexOrderingWithDfs.getVerticesInTopologicalOrder(7U));
    VerticesForTest pathFromAllVertices(vertexOrderingWithDfs.getVerticesInTopologicalOrder());

    VerticesForTest expectedPathFromAVertex{7U, 6U, 9U, 11U, 12U, 10U, 4U};
    VerticesForTest expectedPathFromAllVertices{8U, 7U, 2U, 3U, 0U, 6U, 9U, 11U, 12U, 10U, 5U, 4U, 1U};
    EXPECT_EQ(expectedPathFromAVertex, pathFromAVertex);
    EXPECT_EQ(expectedPathFromAllVertices, pathFromAllVertices);
}

}  // namespace algorithm

}  // namespace alba
