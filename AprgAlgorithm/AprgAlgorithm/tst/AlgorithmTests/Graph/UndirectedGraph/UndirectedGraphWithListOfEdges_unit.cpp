#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithBaseUndirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseUndirectedGraph;

namespace alba
{

namespace algorithm
{

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetNumberOfVerticesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetNumberOfVerticesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetNumberOfEdgesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetNumberOfEdgesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetAdjacentVerticesAtTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetAdjacentVerticesAtTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetVerticesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenNotEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetVerticesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetEdgesTestWhenEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenNotEmpty)
{
    UndirectedGraphWithListOfEdges graph;
    performGetEdgesTestWhenNotEmpty(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, ConnectWorks)
{
    UndirectedGraphWithListOfEdges graph;
    performConnectTest(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, DisonnectWorks)
{
    UndirectedGraphWithListOfEdges graph;
    performDisconnectTest(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, ComplicatedTestWorks)
{
    UndirectedGraphWithListOfEdges graph;
    performComplicatedTest(graph);
}

TEST(UndirectedGraphWithListOfEdgesTest, GetDisplayableStringWorks)
{
    UndirectedGraphWithListOfEdges graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_EQ("Edges: {0<->1, 0<->2, 1<->0, 2<->0, }", graph.getDisplayableString());
}

}

}
