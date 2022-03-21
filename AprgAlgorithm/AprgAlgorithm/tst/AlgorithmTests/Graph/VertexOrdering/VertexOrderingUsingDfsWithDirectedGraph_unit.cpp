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
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using VertexOrderingForTest = VertexOrderingUsingDfs<VertexForTest>;
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksWhenGraphIsEmptyWithDirectedGraph)
{
    GraphForTest graph;
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    PathForTest preOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::PreOrder));
    PathForTest postOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::PostOrder));
    PathForTest reversePostOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    EXPECT_TRUE(preOrderPathToVerify.empty());
    EXPECT_TRUE(postOrderPathToVerify.empty());
    EXPECT_TRUE(reversePostOrderPathToVerify.empty());
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample1WithDirectedGraph)
{
    GraphForTest graph;
    graph.connect(2U, 0U);
    graph.connect(2U, 1U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    VertexOrderingForTest vertexOrderingWithDfs(graph);

    PathForTest preOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::PreOrder));
    PathForTest postOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::PostOrder));
    PathForTest reversePostOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    PathForTest expectedPreOrderPath{2U, 0U, 1U, 3U, 4U};
    PathForTest expectedPostOrderPath{0U, 1U, 3U, 4U, 2U};
    PathForTest expectedReversePostOrderPath{2U, 4U, 3U, 1U, 0U};
    EXPECT_EQ(expectedPreOrderPath, preOrderPathToVerify);
    EXPECT_EQ(expectedPostOrderPath, postOrderPathToVerify);
    EXPECT_EQ(expectedReversePostOrderPath, reversePostOrderPathToVerify);
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

    PathForTest preOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::PreOrder));
    PathForTest postOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::PostOrder));
    PathForTest reversePostOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    PathForTest expectedPreOrderPath{0U, 1U, 5U, 4U, 6U, 9U, 10U, 11U, 12U, 2U, 3U, 7U, 8U};
    PathForTest expectedPostOrderPath{1U, 4U, 5U, 10U, 12U, 11U, 9U, 6U, 0U, 3U, 2U, 7U, 8U};
    PathForTest expectedReversePostOrderPath{8U, 7U, 2U, 3U, 0U, 6U, 9U, 11U, 12U, 10U, 5U, 4U, 1U};
    EXPECT_EQ(expectedPreOrderPath, preOrderPathToVerify);
    EXPECT_EQ(expectedPostOrderPath, postOrderPathToVerify);
    EXPECT_EQ(expectedReversePostOrderPath, reversePostOrderPathToVerify);
}

TEST(VertexOrderingUsingDfsTest, GetPathInTopologicalOrderWorksAsInReversePostOrderWithDirectedGraph)
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

    PathForTest pathToVerify(vertexOrderingWithDfs.getPathInTopologicalOrder());

    PathForTest expectedPath{8U, 7U, 2U, 3U, 0U, 6U, 9U, 11U, 12U, 10U, 5U, 4U, 1U};
    EXPECT_EQ(expectedPath, pathToVerify);
}

}

}
