#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/UndirectedGraph/Utilities/CommonTestsWithBaseUndirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseUndirectedGraph;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = UndirectedGraphWithListOfEdges<unsigned int>;
}

TEST(UndirectedGraphWithListOfEdgesTest, HasAnyConnectionWorksWhenEmpty)
{
    performHasAnyConnectionOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, HasAnyConnectionWorksWhenNotEmpty)
{
    performHasAnyConnectionOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, IsConnectedWorksWhenEmpty)
{
    performIsConnectedOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, IsConnectedWorksWhenNotEmpty)
{
    performIsConnectedOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenEmpty)
{
    performGetNumberOfVerticesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    performGetNumberOfVerticesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenEmpty)
{
    performGetNumberOfEdgesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    performGetNumberOfEdgesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    performGetAdjacentVerticesAtOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenEmpty)
{
    performGetVerticesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenNotEmpty)
{
    performGetVerticesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenEmpty)
{
    performGetEdgesOnUnsignedIntVertexTestWhenEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenNotEmpty)
{
    performGetEdgesOnUnsignedIntVertexTestWhenNotEmpty<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, ConnectWorks)
{
    performConnectOnUnsignedIntVertexTest<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, DisonnectWorks)
{
    performDisconnectOnUnsignedIntVertexTest<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, ComplicatedTestWorks)
{
    performUnsignedIntVertexComplicatedTest<GraphForTest>();
}

TEST(UndirectedGraphWithListOfEdgesTest, GetDisplayableStringWorks)
{
    GraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    EXPECT_EQ("Edges: {0<->1, 0<->2, 1<->0, 2<->0, }", graph.getDisplayableString());
}
}

}
