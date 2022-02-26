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
using SampleGraphForTest = UndirectedGraphWithListOfEdges;
}

TEST(ConnectedComponentsUsingUnionFindTest, IsConnectedWorksWhenEmpty)
{
    performIsConnectedTestWhenEmpty<ConnectedComponentsUsingUnionFind, SampleGraphForTest>();
}

TEST(ConnectedComponentsUsingUnionFindTest, IsConnectedWorksWhenNotEmpty)
{
    performIsConnectedTestWhenNotEmpty<ConnectedComponentsUsingUnionFind, SampleGraphForTest>();
}

}

}
