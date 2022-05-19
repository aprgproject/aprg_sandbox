#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using VerticesForTest = GraphTypes<VertexForTest>::Vertices;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using VertexOrderingForTest = VertexOrderingUsingDfs<VertexForTest>;
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksWhenGraphIsEmptyWithDirectedGraph)
{
    GraphForTest graph;
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderVerticesToVerify(vertexOrderingWithDfs.traverseAndGetVertices(VertexOrderingForTest::TraverseOrder::PreOrder));
    VerticesForTest postOrderVerticesToVerify(vertexOrderingWithDfs.traverseAndGetVertices(VertexOrderingForTest::TraverseOrder::PostOrder));
    VerticesForTest reversePostOrderVerticesToVerify(vertexOrderingWithDfs.traverseAndGetVertices(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    EXPECT_TRUE(preOrderVerticesToVerify.empty());
    EXPECT_TRUE(postOrderVerticesToVerify.empty());
    EXPECT_TRUE(reversePostOrderVerticesToVerify.empty());
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample1WithDirectedGraph)
{
    GraphForTest graph;
    graph.connect(40U, 30U); // first value set
    graph.connect(40U, 31U);
    graph.connect(40U, 32U);
    graph.connect(40U, 33U);
    graph.connect(30U, 20U); // second value set
    graph.connect(31U, 21U);
    graph.connect(32U, 22U);
    graph.connect(33U, 23U);
    graph.connect(20U, 10U); // third value set
    graph.connect(21U, 11U);
    graph.connect(22U, 12U);
    graph.connect(23U, 13U);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderVerticesToVerify(vertexOrderingWithDfs.traverseAndGetVertices(VertexOrderingForTest::TraverseOrder::PreOrder));
    VerticesForTest postOrderVerticesToVerify(vertexOrderingWithDfs.traverseAndGetVertices(VertexOrderingForTest::TraverseOrder::PostOrder));
    VerticesForTest reversePostOrderVerticesToVerify(vertexOrderingWithDfs.traverseAndGetVertices(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderVertices{20U, 10U, 21U, 11U, 22U, 12U, 23U, 13U, 30U, 31U, 32U, 33U, 40U};
    VerticesForTest expectedPostOrderVertices{10U, 20U, 11U, 21U, 12U, 22U, 13U, 23U, 30U, 31U, 32U, 33U, 40U};
    VerticesForTest expectedReversePostOrderVertices{40U, 33U, 32U, 31U, 30U, 23U, 13U, 22U, 12U, 21U, 11U, 20U, 10U};
    EXPECT_EQ(expectedPreOrderVertices, preOrderVerticesToVerify);
    EXPECT_EQ(expectedPostOrderVertices, postOrderVerticesToVerify);
    EXPECT_EQ(expectedReversePostOrderVertices, reversePostOrderVerticesToVerify);
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample2WithDirectedGraph)
{
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

    VerticesForTest preOrderVerticesToVerify(vertexOrderingWithDfs.traverseAndGetVertices(VertexOrderingForTest::TraverseOrder::PreOrder));
    VerticesForTest postOrderVerticesToVerify(vertexOrderingWithDfs.traverseAndGetVertices(VertexOrderingForTest::TraverseOrder::PostOrder));
    VerticesForTest reversePostOrderVerticesToVerify(vertexOrderingWithDfs.traverseAndGetVertices(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderVertices{0U, 1U, 5U, 4U, 6U, 9U, 10U, 11U, 12U, 2U, 3U, 7U, 8U};
    VerticesForTest expectedPostOrderVertices{1U, 4U, 5U, 10U, 12U, 11U, 9U, 6U, 0U, 3U, 2U, 7U, 8U};
    VerticesForTest expectedReversePostOrderVertices{8U, 7U, 2U, 3U, 0U, 6U, 9U, 11U, 12U, 10U, 5U, 4U, 1U};
    EXPECT_EQ(expectedPreOrderVertices, preOrderVerticesToVerify);
    EXPECT_EQ(expectedPostOrderVertices, postOrderVerticesToVerify);
    EXPECT_EQ(expectedReversePostOrderVertices, reversePostOrderVerticesToVerify);
}

TEST(VertexOrderingUsingDfsTest, GetVerticesInTopologicalOrderWorksAsInReversePostOrderWithDirectedGraph)
{
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

    VerticesForTest pathToVerify(vertexOrderingWithDfs.getVerticesInTopologicalOrder());

    VerticesForTest expectedVertices{8U, 7U, 2U, 3U, 0U, 6U, 9U, 11U, 12U, 10U, 5U, 4U, 1U};
    EXPECT_EQ(expectedVertices, pathToVerify);
}

}

}
