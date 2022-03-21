#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/DirectedGraph/Utilities/CommonTestsWithDirectedGraph.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithDirectedGraph;

namespace alba
{
namespace algorithm
{

namespace
{
using GraphForTest = DirectedGraphWithListOfEdges<unsigned int>;
}

TEST(DirectedGraphWithListOfEdgesTest, GetGraphDirectionTypeWorks)
{
    testGetGraphDirectionTypeWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, IsConnectedWorksWhenEmpty)
{
    testIsConnectedWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, IsConnectedWorksWhenNotEmpty)
{
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenEmpty)
{
    testGetNumberOfVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetNumberOfVerticesWorksWhenNotEmpty)
{
    testGetNumberOfVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenEmpty)
{
    testGetNumberOfEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetNumberOfEdgesWorksWhenNotEmpty)
{
    testGetNumberOfEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenEmpty)
{
    testGetAdjacentVerticesAtWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetAdjacentVerticesAtWorksWhenNotEmpty)
{
    testGetAdjacentVerticesAtWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenEmpty)
{
    testGetVerticesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetVerticesWorksWhenNotEmpty)
{
    testGetVerticesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenEmpty)
{
    testGetEdgesWhenEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetEdgesWorksWhenNotEmpty)
{
    testGetEdgesWhenNotEmptyWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, ConnectWorks)
{
    testConnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, DisconnectWorks)
{
    testDisconnectWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, ClearWorks)
{
    testClearWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, ReverseDirectionsWorks)
{
    testReverseDirectionsWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, ComplicatedTestWorks)
{
    testWithComplicatedExampleWithVertexAsUnsignedInt<GraphForTest>();
}

TEST(DirectedGraphWithListOfEdgesTest, GetDisplayableStringWorks)
{
    GraphForTest graph;

    graph.connect(0U, 1U);
    graph.connect(2U, 0U);

    EXPECT_EQ("Edges: {0->1, 2->0, }", graph.getDisplayableString());
}

}

}
