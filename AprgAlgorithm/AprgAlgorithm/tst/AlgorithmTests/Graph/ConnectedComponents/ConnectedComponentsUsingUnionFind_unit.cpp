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
using ConnectedComponentsForTest = ConnectedComponentsUsingUnionFind<unsigned int>;
using GraphForTest = UndirectedGraphWithListOfEdges<unsigned int>;
}

TEST(ConnectedComponentsUsingUnionFindTest, IsConnectedWorksWhenEmpty)
{
    performIsConnectedTestWhenEmpty<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingUnionFindTest, IsConnectedWorksWhenNotEmpty)
{
    performIsConnectedTestWhenNotEmpty<ConnectedComponentsForTest, GraphForTest>();
}

}
}