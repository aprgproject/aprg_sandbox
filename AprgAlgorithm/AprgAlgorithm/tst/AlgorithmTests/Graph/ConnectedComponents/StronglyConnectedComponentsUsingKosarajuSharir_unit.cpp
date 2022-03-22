#include <Algorithm/Graph/ConnectedComponents/StronglyConnectedComponentsUsingKosarajuSharir.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/ConnectedComponents/Utilities/CommonTestsWithConnectedComponents.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithConnectedComponents;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = DirectedGraphWithListOfEdges<unsigned int>;
using ConnectedComponentsForTest = StronglyConnectedComponentsUsingKosarajuSharir<unsigned int>;
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, GetNumberOfComponentIdsWorksWhenEmpty)
{
    testGetNumberOfComponentIdsWhenEmptyWithVertexAsUnsignedIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, GetNumberOfComponentIdsWorksWhenNotEmpty)
{
    testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsUnsignedIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, IsConnectedWorksWhenEmpty)
{
    testIsConnectedWhenEmptyWithVertexAsUnsignedIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(StronglyConnectedComponentsUsingKosarajuSharirTest, IsConnectedWorksWhenNotEmpty)
{
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedIntWithDirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

}

}
