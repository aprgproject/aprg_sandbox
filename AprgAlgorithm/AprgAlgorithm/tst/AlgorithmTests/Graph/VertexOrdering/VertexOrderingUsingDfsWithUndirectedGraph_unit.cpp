#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using VerticesForTest = GraphTypes<VertexForTest>::Vertices;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using VertexOrderingForTest = VertexOrderingUsingDfs<VertexForTest>;
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksWhenGraphIsEmptyWithUndirectedGraph)
{
    GraphForTest graph;
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderVerticesToVerify(vertexOrderingWithDfs.getVerticesInThisOrder(VertexOrderingForTest::TraverseOrder::PreOrder));
    VerticesForTest postOrderVerticesToVerify(vertexOrderingWithDfs.getVerticesInThisOrder(VertexOrderingForTest::TraverseOrder::PostOrder));
    VerticesForTest reversePostOrderVerticesToVerify(vertexOrderingWithDfs.getVerticesInThisOrder(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    EXPECT_TRUE(preOrderVerticesToVerify.empty());
    EXPECT_TRUE(postOrderVerticesToVerify.empty());
    EXPECT_TRUE(reversePostOrderVerticesToVerify.empty());
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample1WithUndirectedGraph)
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

    VerticesForTest preOrderVerticesToVerify(vertexOrderingWithDfs.getVerticesInThisOrder(VertexOrderingForTest::TraverseOrder::PreOrder));
    VerticesForTest postOrderVerticesToVerify(vertexOrderingWithDfs.getVerticesInThisOrder(VertexOrderingForTest::TraverseOrder::PostOrder));
    VerticesForTest reversePostOrderVerticesToVerify(vertexOrderingWithDfs.getVerticesInThisOrder(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderVertices{10U, 20U, 30U, 40U, 31U, 21U, 11U, 32U, 22U, 12U, 33U, 23U, 13U};
    VerticesForTest expectedPostOrderVertices{11U, 21U, 31U, 12U, 22U, 32U, 13U, 23U, 33U, 40U, 30U, 20U, 10U};
    VerticesForTest expectedReversePostOrderVertices{10U, 20U, 30U, 40U, 33U, 23U, 13U, 32U, 22U, 12U, 31U, 21U, 11U};
    EXPECT_EQ(expectedPreOrderVertices, preOrderVerticesToVerify);
    EXPECT_EQ(expectedPostOrderVertices, postOrderVerticesToVerify);
    EXPECT_EQ(expectedReversePostOrderVertices, reversePostOrderVerticesToVerify);
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample2WithUndirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 5U);
    graph.connect(4U, 3U);
    graph.connect(0U, 1U);
    graph.connect(9U, 12U);
    graph.connect(6U, 4U);
    graph.connect(5U, 4U);
    graph.connect(0U, 2U);
    graph.connect(11U, 12U);
    graph.connect(9U, 10U);
    graph.connect(0U, 6U);
    graph.connect(7U, 8U);
    graph.connect(9U, 11U);
    graph.connect(5U, 3U);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest preOrderVerticesToVerify(vertexOrderingWithDfs.getVerticesInThisOrder(VertexOrderingForTest::TraverseOrder::PreOrder));
    VerticesForTest postOrderVerticesToVerify(vertexOrderingWithDfs.getVerticesInThisOrder(VertexOrderingForTest::TraverseOrder::PostOrder));
    VerticesForTest reversePostOrderVerticesToVerify(vertexOrderingWithDfs.getVerticesInThisOrder(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderVertices{0U, 1U, 2U, 5U, 3U, 4U, 6U, 7U, 8U, 9U, 10U, 11U, 12U};
    VerticesForTest expectedPostOrderVertices{1U, 2U, 6U, 4U, 3U, 5U, 0U, 8U, 7U, 10U, 12U, 11U, 9U};
    VerticesForTest expectedReversePostOrderVertices{9U, 11U, 12U, 10U, 7U, 8U, 0U, 5U, 3U, 4U, 6U, 2U, 1U};
    EXPECT_EQ(expectedPreOrderVertices, preOrderVerticesToVerify);
    EXPECT_EQ(expectedPostOrderVertices, postOrderVerticesToVerify);
    EXPECT_EQ(expectedReversePostOrderVertices, reversePostOrderVerticesToVerify);
}

TEST(VertexOrderingUsingDfsTest, GetVerticesInTopologicalOrderWorksAsInReversePostOrderWithUndirectedGraph)
{
    GraphForTest graph;
    graph.connect(0U, 5U);
    graph.connect(4U, 3U);
    graph.connect(0U, 1U);
    graph.connect(9U, 12U);
    graph.connect(6U, 4U);
    graph.connect(5U, 4U);
    graph.connect(0U, 2U);
    graph.connect(11U, 12U);
    graph.connect(9U, 10U);
    graph.connect(0U, 6U);
    graph.connect(7U, 8U);
    graph.connect(9U, 11U);
    graph.connect(5U, 3U);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    VerticesForTest verticesToVerify(vertexOrderingWithDfs.getVerticesInTopologicalOrder());

    VerticesForTest expectedVertices{9U, 11U, 12U, 10U, 7U, 8U, 0U, 5U, 3U, 4U, 6U, 2U, 1U};
    EXPECT_EQ(expectedVertices, verticesToVerify);
}

}

}
