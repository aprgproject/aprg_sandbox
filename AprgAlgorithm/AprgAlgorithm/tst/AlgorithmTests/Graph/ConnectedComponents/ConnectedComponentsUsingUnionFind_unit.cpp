#include <Algorithm/Graph/ConnectedComponents/ConnectedComponentsUsingUnionFind.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/ConnectedComponents/Utilities/CommonTestsWithConnectedComponents.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithConnectedComponents;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = UndirectedGraphWithListOfEdges<unsigned int>;
using ConnectedComponentsForTest = ConnectedComponentsUsingUnionFind<unsigned int>;
}  // namespace

TEST(ConnectedComponentsUsingUnionFindTest, GetNumberOfComponentIdsWorksWhenEmpty) {
    testGetNumberOfComponentIdsWhenEmptyWithVertexAsUnsignedIntWithUndirectedGraph<
        ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingUnionFindTest, GetNumberOfComponentIdsWorksWhenNotEmpty) {
    testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsUnsignedIntWithUndirectedGraph<
        ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingUnionFindTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingUnionFindTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsUnsignedIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingUnionFindTest, GetComponentIdWorks) {
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    graph.connect(4U, 5U);
    graph.connect(6U, 7U);
    ConnectedComponentsForTest connectedComponents(graph);

    EXPECT_EQ(1U, connectedComponents.getComponentId(0U));
    EXPECT_EQ(1U, connectedComponents.getComponentId(1U));
    EXPECT_EQ(1U, connectedComponents.getComponentId(2U));
    EXPECT_EQ(1U, connectedComponents.getComponentId(3U));
    EXPECT_EQ(2U, connectedComponents.getComponentId(4U));
    EXPECT_EQ(2U, connectedComponents.getComponentId(5U));
    EXPECT_EQ(3U, connectedComponents.getComponentId(6U));
    EXPECT_EQ(3U, connectedComponents.getComponentId(7U));
}

}  // namespace algorithm

}  // namespace alba
