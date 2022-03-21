#include <Algorithm/Graph/ConnectedComponents/ConnectedComponentsUsingDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/ConnectedComponents/Utilities/CommonTestsWithBaseConnectedComponents.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithBaseConnectedComponents;

namespace alba
{

namespace algorithm
{

namespace
{
using GraphForTest = UndirectedGraphWithListOfEdges<unsigned int>;
using ConnectedComponentsForTest = ConnectedComponentsUsingDfs<unsigned int>;
}

TEST(ConnectedComponentsUsingDfsTest, GetNumberOfComponentIdsWorksWhenEmpty)
{
    testGetNumberOfComponentIdsWhenEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingDfsTest, GetNumberOfComponentIdsWorksWhenNotEmpty)
{
    testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingDfsTest, IsConnectedWorksWhenEmpty)
{
    testIsConnectedWhenEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingDfsTest, IsConnectedWorksWhenNotEmpty)
{
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

}

}
