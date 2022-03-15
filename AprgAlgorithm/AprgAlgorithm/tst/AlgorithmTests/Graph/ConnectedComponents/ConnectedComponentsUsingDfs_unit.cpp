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
using ConnectedComponentsForTest = ConnectedComponentsUsingDfs<unsigned int>;
using GraphForTest = UndirectedGraphWithListOfEdges<unsigned int>;
}

TEST(ConnectedComponentsUsingDfsTest, IsConnectedWorksWhenEmpty)
{
    performIsConnectedTestWhenEmpty<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingDfsTest, IsConnectedWorksWhenNotEmpty)
{
    performIsConnectedTestWhenNotEmpty<ConnectedComponentsForTest, GraphForTest>();
}

}
}