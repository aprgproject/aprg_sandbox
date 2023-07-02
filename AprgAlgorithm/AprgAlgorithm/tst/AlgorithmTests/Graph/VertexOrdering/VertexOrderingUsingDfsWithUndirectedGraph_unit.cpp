#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using VerticesForTest = GraphTypes<VertexForTest>::Vertices;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using VertexOrderingForTest = VertexOrderingUsingDfs<VertexForTest>;
}  // namespace

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksWhenGraphIsEmptyWithUndirectedGraph) {
    GraphForTest graph;
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    EXPECT_TRUE(preOrderFromAllVertices.empty());
    EXPECT_TRUE(postOrderFromAllVertices.empty());
    EXPECT_TRUE(reversePostOrderFromAllVertices.empty());
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample1WithUndirectedGraph) {
    GraphForTest graph;
    graph.connect(40, 30);  // first value set
    graph.connect(40, 31);
    graph.connect(40, 32);
    graph.connect(40, 33);
    graph.connect(30, 20);  // second value set
    graph.connect(31, 21);
    graph.connect(32, 22);
    graph.connect(33, 23);
    graph.connect(20, 10);  // third value set
    graph.connect(21, 11);
    graph.connect(22, 12);
    graph.connect(23, 13);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(30, VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(30, VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(30, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest preOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderFromAVertex{30, 20, 10, 40, 31, 21, 11, 32, 22, 12, 33, 23, 13};
    VerticesForTest expectedPostOrderFromAVertex{10, 20, 11, 21, 31, 12, 22, 32, 13, 23, 33, 40, 30};
    VerticesForTest expectedReversePostOrderFromAVertex{30, 40, 33, 23, 13, 32, 22, 12, 31, 21, 11, 20, 10};
    VerticesForTest expectedPreOrderFromAllVertices{10, 20, 30, 40, 31, 21, 11, 32, 22, 12, 33, 23, 13};
    VerticesForTest expectedPostOrderFromAllVertices{11, 21, 31, 12, 22, 32, 13, 23, 33, 40, 30, 20, 10};
    VerticesForTest expectedReversePostOrderFromAllVertices{10, 20, 30, 40, 33, 23, 13, 32, 22, 12, 31, 21, 11};
    EXPECT_EQ(expectedPreOrderFromAVertex, preOrderFromAVertex);
    EXPECT_EQ(expectedPostOrderFromAVertex, postOrderFromAVertex);
    EXPECT_EQ(expectedReversePostOrderFromAVertex, reversePostOrderAVertex);
    EXPECT_EQ(expectedPreOrderFromAllVertices, preOrderFromAllVertices);
    EXPECT_EQ(expectedPostOrderFromAllVertices, postOrderFromAllVertices);
    EXPECT_EQ(expectedReversePostOrderFromAllVertices, reversePostOrderFromAllVertices);
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample2WithUndirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 5);
    graph.connect(4, 3);
    graph.connect(0, 1);
    graph.connect(9, 12);
    graph.connect(6, 4);
    graph.connect(5, 4);
    graph.connect(0, 2);
    graph.connect(11, 12);
    graph.connect(9, 10);
    graph.connect(0, 6);
    graph.connect(7, 8);
    graph.connect(9, 11);
    graph.connect(5, 3);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(4, VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(4, VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderAVertex(
        vertexOrderingWithDfs.getVerticesInThisOrder(4, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest preOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderFromAllVertices(
        vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderFromAVertex{4, 3, 5, 0, 1, 2, 6};
    VerticesForTest expectedPostOrderFromAVertex{1, 2, 6, 0, 5, 3, 4};
    VerticesForTest expectedReversePostOrderFromAVertex{4, 3, 5, 0, 6, 2, 1};
    VerticesForTest expectedPreOrderFromAllVertices{0, 1, 2, 5, 3, 4, 6, 7, 8, 9, 10, 11, 12};
    VerticesForTest expectedPostOrderFromAllVertices{1, 2, 6, 4, 3, 5, 0, 8, 7, 10, 12, 11, 9};
    VerticesForTest expectedReversePostOrderFromAllVertices{9, 11, 12, 10, 7, 8, 0, 5, 3, 4, 6, 2, 1};
    EXPECT_EQ(expectedPreOrderFromAVertex, preOrderFromAVertex);
    EXPECT_EQ(expectedPostOrderFromAVertex, postOrderFromAVertex);
    EXPECT_EQ(expectedReversePostOrderFromAVertex, reversePostOrderAVertex);
    EXPECT_EQ(expectedPreOrderFromAllVertices, preOrderFromAllVertices);
    EXPECT_EQ(expectedPostOrderFromAllVertices, postOrderFromAllVertices);
    EXPECT_EQ(expectedReversePostOrderFromAllVertices, reversePostOrderFromAllVertices);
}

TEST(VertexOrderingUsingDfsTest, GetVerticesInTopologicalOrderWorksWithUndirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 5);
    graph.connect(4, 3);
    graph.connect(0, 1);
    graph.connect(9, 12);
    graph.connect(6, 4);
    graph.connect(5, 4);
    graph.connect(0, 2);
    graph.connect(11, 12);
    graph.connect(9, 10);
    graph.connect(0, 6);
    graph.connect(7, 8);
    graph.connect(9, 11);
    graph.connect(5, 3);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest pathFromAVertex(vertexOrderingWithDfs.getVerticesInTopologicalOrder(4));
    VerticesForTest pathFromAllVertices(vertexOrderingWithDfs.getVerticesInTopologicalOrder());

    VerticesForTest expectedPathFromAVertex{4, 3, 5, 0, 6, 2, 1};
    VerticesForTest expectedPathFromAllVertices{9, 11, 12, 10, 7, 8, 0, 5, 3, 4, 6, 2, 1};
    EXPECT_EQ(expectedPathFromAVertex, pathFromAVertex);
    EXPECT_EQ(expectedPathFromAllVertices, pathFromAllVertices);
}

TEST(VertexOrderingUsingDfsTest, GetVerticesInTopologicalOrderWorksWithDagCheckingWithUndirectedGraph) {
    GraphForTest graph;
    graph.connect(0, 5);
    graph.connect(4, 3);
    graph.connect(0, 1);
    graph.connect(9, 12);
    graph.connect(6, 4);
    graph.connect(5, 4);
    graph.connect(0, 2);
    graph.connect(11, 12);
    graph.connect(9, 10);
    graph.connect(0, 6);
    graph.connect(7, 8);
    graph.connect(9, 11);
    graph.connect(5, 3);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest pathFromAllVertices(vertexOrderingWithDfs.getVerticesInTopologicalOrderWithDagChecking());

    VerticesForTest expectedPathFromAllVertices{9, 11, 12, 10, 7, 8, 0, 5, 3, 4, 6, 2, 1};
    EXPECT_EQ(expectedPathFromAllVertices, pathFromAllVertices);
}

}  // namespace algorithm

}  // namespace alba
