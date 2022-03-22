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
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using VertexOrderingForTest = VertexOrderingUsingDfs<VertexForTest>;
}

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksWhenGraphIsEmptyWithUndirectedGraph)
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

TEST(VertexOrderingUsingDfsTest, VertexOrderingWorksUsingExample1WithUndirectedGraph)
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

    PathForTest expectedPreOrderPath{0U, 2U, 1U, 3U, 4U};
    PathForTest expectedPostOrderPath{1U, 3U, 4U, 2U, 0U};
    PathForTest expectedReversePostOrderPath{0U, 2U, 4U, 3U, 1U};
    EXPECT_EQ(expectedPreOrderPath, preOrderPathToVerify);
    EXPECT_EQ(expectedPostOrderPath, postOrderPathToVerify);
    EXPECT_EQ(expectedReversePostOrderPath, reversePostOrderPathToVerify);
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

    PathForTest preOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::PreOrder));
    PathForTest postOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::PostOrder));
    PathForTest reversePostOrderPathToVerify(vertexOrderingWithDfs.traverseAndGetPath(VertexOrderingForTest::TraverseOrder::ReversePostOrder));

    PathForTest expectedPreOrderPath{0U, 1U, 2U, 5U, 3U, 4U, 6U, 7U, 8U, 9U, 10U, 11U, 12U};
    PathForTest expectedPostOrderPath{1U, 2U, 6U, 4U, 3U, 5U, 0U, 8U, 7U, 10U, 12U, 11U, 9U};
    PathForTest expectedReversePostOrderPath{9U, 11U, 12U, 10U, 7U, 8U, 0U, 5U, 3U, 4U, 6U, 2U, 1U};
    EXPECT_EQ(expectedPreOrderPath, preOrderPathToVerify);
    EXPECT_EQ(expectedPostOrderPath, postOrderPathToVerify);
    EXPECT_EQ(expectedReversePostOrderPath, reversePostOrderPathToVerify);
}

TEST(VertexOrderingUsingDfsTest, GetPathInTopologicalOrderWorksAsInReversePostOrderWithUndirectedGraph)
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

    PathForTest pathToVerify(vertexOrderingWithDfs.getPathInTopologicalOrder());

    PathForTest expectedPath{9U, 11U, 12U, 10U, 7U, 8U, 0U, 5U, 3U, 4U, 6U, 2U, 1U};
    EXPECT_EQ(expectedPath, pathToVerify);
}

}

}
