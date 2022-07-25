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

    VerticesForTest preOrderFromAllVertices(vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAllVertices(vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderFromAllVertices(vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    EXPECT_TRUE(preOrderFromAllVertices.empty());
    EXPECT_TRUE(postOrderFromAllVertices.empty());
    EXPECT_TRUE(reversePostOrderFromAllVertices.empty());
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

    VerticesForTest preOrderFromAVertex(vertexOrderingWithDfs.getVerticesInThisOrder(30U, VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAVertex(vertexOrderingWithDfs.getVerticesInThisOrder(30U, VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderAVertex(vertexOrderingWithDfs.getVerticesInThisOrder(30U, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest preOrderFromAllVertices(vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAllVertices(vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderFromAllVertices(vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderFromAVertex{30U, 20U, 10U, 40U, 31U, 21U, 11U, 32U, 22U, 12U, 33U, 23U, 13U};
    VerticesForTest expectedPostOrderFromAVertex{10U, 20U, 11U, 21U, 31U, 12U, 22U, 32U, 13U, 23U, 33U, 40U, 30U};
    VerticesForTest expectedReversePostOrderFromAVertex{30U, 40U, 33U, 23U, 13U, 32U, 22U, 12U, 31U, 21U, 11U, 20U, 10U};
    VerticesForTest expectedPreOrderFromAllVertices{10U, 20U, 30U, 40U, 31U, 21U, 11U, 32U, 22U, 12U, 33U, 23U, 13U};
    VerticesForTest expectedPostOrderFromAllVertices{11U, 21U, 31U, 12U, 22U, 32U, 13U, 23U, 33U, 40U, 30U, 20U, 10U};
    VerticesForTest expectedReversePostOrderFromAllVertices{10U, 20U, 30U, 40U, 33U, 23U, 13U, 32U, 22U, 12U, 31U, 21U, 11U};
    EXPECT_EQ(expectedPreOrderFromAVertex, preOrderFromAVertex);
    EXPECT_EQ(expectedPostOrderFromAVertex, postOrderFromAVertex);
    EXPECT_EQ(expectedReversePostOrderFromAVertex, reversePostOrderAVertex);
    EXPECT_EQ(expectedPreOrderFromAllVertices, preOrderFromAllVertices);
    EXPECT_EQ(expectedPostOrderFromAllVertices, postOrderFromAllVertices);
    EXPECT_EQ(expectedReversePostOrderFromAllVertices, reversePostOrderFromAllVertices);
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

    VerticesForTest preOrderFromAVertex(vertexOrderingWithDfs.getVerticesInThisOrder(4U, VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAVertex(vertexOrderingWithDfs.getVerticesInThisOrder(4U, VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderAVertex(vertexOrderingWithDfs.getVerticesInThisOrder(4U, VertexTraversalOrder::ReversePostOrder));
    VerticesForTest preOrderFromAllVertices(vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PreOrder));
    VerticesForTest postOrderFromAllVertices(vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::PostOrder));
    VerticesForTest reversePostOrderFromAllVertices(vertexOrderingWithDfs.getVerticesInThisOrder(VertexTraversalOrder::ReversePostOrder));

    VerticesForTest expectedPreOrderFromAVertex{4U, 3U, 5U, 0U, 1U, 2U, 6U};
    VerticesForTest expectedPostOrderFromAVertex{1U, 2U, 6U, 0U, 5U, 3U, 4U};
    VerticesForTest expectedReversePostOrderFromAVertex{4U, 3U, 5U, 0U, 6U, 2U, 1U};
    VerticesForTest expectedPreOrderFromAllVertices{0U, 1U, 2U, 5U, 3U, 4U, 6U, 7U, 8U, 9U, 10U, 11U, 12U};
    VerticesForTest expectedPostOrderFromAllVertices{1U, 2U, 6U, 4U, 3U, 5U, 0U, 8U, 7U, 10U, 12U, 11U, 9U};
    VerticesForTest expectedReversePostOrderFromAllVertices{9U, 11U, 12U, 10U, 7U, 8U, 0U, 5U, 3U, 4U, 6U, 2U, 1U};
    EXPECT_EQ(expectedPreOrderFromAVertex, preOrderFromAVertex);
    EXPECT_EQ(expectedPostOrderFromAVertex, postOrderFromAVertex);
    EXPECT_EQ(expectedReversePostOrderFromAVertex, reversePostOrderAVertex);
    EXPECT_EQ(expectedPreOrderFromAllVertices, preOrderFromAllVertices);
    EXPECT_EQ(expectedPostOrderFromAllVertices, postOrderFromAllVertices);
    EXPECT_EQ(expectedReversePostOrderFromAllVertices, reversePostOrderFromAllVertices);
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

    VerticesForTest pathFromAVertex(vertexOrderingWithDfs.getVerticesInTopologicalOrder(4U));
    VerticesForTest pathFromAllVertices(vertexOrderingWithDfs.getVerticesInTopologicalOrder());

    VerticesForTest expectedPathFromAVertex{4U, 3U, 5U, 0U, 6U, 2U, 1U};
    VerticesForTest expectedPathFromAllVertices{9U, 11U, 12U, 10U, 7U, 8U, 0U, 5U, 3U, 4U, 6U, 2U, 1U};
    EXPECT_EQ(expectedPathFromAVertex, pathFromAVertex);
    EXPECT_EQ(expectedPathFromAllVertices, pathFromAllVertices);
}

}

}
