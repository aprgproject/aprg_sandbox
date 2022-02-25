#include "CommonTestsWithBaseUndirectedGraph.hpp"

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithBaseUndirectedGraph
{

void performGetNumberOfVerticesTestWhenEmpty(BaseUndirectedGraph & graph)
{
    EXPECT_EQ(0U, graph.getNumberOfVertices());
}

void performGetNumberOfVerticesTestWhenNotEmpty(BaseUndirectedGraph & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(3U, graph.getNumberOfVertices());
}

void performGetNumberOfEdgesTestWhenEmpty(BaseUndirectedGraph & graph)
{
    EXPECT_EQ(0U, graph.getNumberOfVertices());
}

void performGetNumberOfEdgesTestWhenNotEmpty(BaseUndirectedGraph & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(2U, graph.getNumberOfEdges());
}

void performGetAdjacentVerticesAtTestWhenEmpty(BaseUndirectedGraph & graph)
{
    Vertices adjacentVerticesToVerify(graph.getAdjacentVerticesAt(0));
    EXPECT_TRUE(adjacentVerticesToVerify.empty());
}

void performGetAdjacentVerticesAtTestWhenNotEmpty(BaseUndirectedGraph & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    Vertices adjacentVerticesToVerify(graph.getAdjacentVerticesAt(0));

    ASSERT_EQ(2U, adjacentVerticesToVerify.size());
    EXPECT_EQ(1U, adjacentVerticesToVerify.at(0));
    EXPECT_EQ(2U, adjacentVerticesToVerify.at(1));
}

void performGetVerticesTestWhenEmpty(BaseUndirectedGraph & graph)
{
    Vertices verticesToVerify(graph.getVertices());
    EXPECT_TRUE(verticesToVerify.empty());
}

void performGetVerticesTestWhenNotEmpty(BaseUndirectedGraph & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    Vertices verticesToVerify(graph.getVertices());

    Vertices verticesToExpect{0U, 1U, 2U};
    EXPECT_EQ(verticesToExpect, verticesToVerify);
}

void performGetEdgesTestWhenEmpty(BaseUndirectedGraph & graph)
{
    Edges edgesToVerify(graph.getEdges());
    EXPECT_TRUE(edgesToVerify.empty());
}

void performGetEdgesTestWhenNotEmpty(BaseUndirectedGraph & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    Edges edgesToVerify(graph.getEdges());

    Edges edgesToExpect{{0U, 1U}, {0U, 2U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

void performConnectTest(BaseUndirectedGraph & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ(3U, graph.getNumberOfVertices());
    EXPECT_EQ(2U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{0U, 1U}, {0U, 2U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

void performDisconnectTest(BaseUndirectedGraph & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    graph.disconnect(0U, 1U);

    EXPECT_EQ(2U, graph.getNumberOfVertices());
    EXPECT_EQ(1U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect{{0U, 2U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

void performComplicatedTest(BaseUndirectedGraph & graph)
{
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

    EXPECT_EQ(13U, graph.getNumberOfVertices());
    EXPECT_EQ(13U, graph.getNumberOfEdges());
    Edges edgesToVerify(graph.getEdges());
    Edges edgesToExpect
    {{0U, 1U}, {0U, 2U}, {0U, 5U}, {0U, 6U}, {3U, 4U}, {3U, 5U}, {4U, 5U}, {4U, 6U}, {7U, 8U}, {9U, 10U}, {9U, 11U}, {9U, 12U}, {11U, 12U}};
    EXPECT_EQ(edgesToExpect, edgesToVerify);
}

}

}

}
