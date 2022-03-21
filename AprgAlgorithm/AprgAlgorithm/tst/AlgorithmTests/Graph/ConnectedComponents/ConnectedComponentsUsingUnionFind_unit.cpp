#include <Algorithm/Graph/ConnectedComponents/ConnectedComponentsUsingUnionFind.hpp>
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
using ConnectedComponentsForTest = ConnectedComponentsUsingUnionFind<unsigned int>;
}

TEST(ConnectedComponentsUsingUnionFindTest, GetNumberOfComponentIdsWorksWhenEmpty)
{
    testGetNumberOfComponentIdsWhenEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingUnionFindTest, GetNumberOfComponentIdsWorksWhenNotEmpty)
{
    testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingUnionFindTest, IsConnectedWorksWhenEmpty)
{
    testIsConnectedWhenEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingUnionFindTest, IsConnectedWorksWhenNotEmpty)
{
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

}

}
