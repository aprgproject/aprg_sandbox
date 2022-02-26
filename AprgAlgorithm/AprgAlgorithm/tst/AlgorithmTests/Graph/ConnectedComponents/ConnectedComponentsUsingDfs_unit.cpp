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
using SampleGraphForTest = UndirectedGraphWithListOfEdges;
}

TEST(ConnectedComponentsUsingDfsTest, IsConnectedWorksWhenEmpty)
{
    performIsConnectedTestWhenEmpty<ConnectedComponentsUsingDfs, SampleGraphForTest>();
}

TEST(ConnectedComponentsUsingDfsTest, IsConnectedWorksWhenNotEmpty)
{
    performIsConnectedTestWhenNotEmpty<ConnectedComponentsUsingDfs, SampleGraphForTest>();
}

}

}
