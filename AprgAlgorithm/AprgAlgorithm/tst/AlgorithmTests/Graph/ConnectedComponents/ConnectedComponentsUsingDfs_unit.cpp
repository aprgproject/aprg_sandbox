#include <Algorithm/Graph/ConnectedComponents/ConnectedComponentsUsingDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>
#include <AlgorithmTests/Graph/ConnectedComponents/Utilities/CommonTestsWithConnectedComponents.hpp>

#include <gtest/gtest.h>

using namespace alba::algorithm::CommonTestsWithConnectedComponents;

namespace alba {

namespace algorithm {

namespace {
using GraphForTest = UndirectedGraphWithListOfEdges<int>;
using ConnectedComponentsForTest = ConnectedComponentsUsingDfs<int>;
}  // namespace

TEST(ConnectedComponentsUsingDfsTest, GetNumberOfComponentIdsWorksWhenEmpty) {
    testGetNumberOfComponentIdsWhenEmptyWithVertexAsIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingDfsTest, GetNumberOfComponentIdsWorksWhenNotEmpty) {
    testGetNumberOfComponentIdsWhenNotEmptyWithVertexAsIntWithUndirectedGraph<
        ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingDfsTest, IsConnectedWorksWhenEmpty) {
    testIsConnectedWhenEmptyWithVertexAsIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingDfsTest, IsConnectedWorksWhenNotEmpty) {
    testIsConnectedWhenNotEmptyWithVertexAsIntWithUndirectedGraph<ConnectedComponentsForTest, GraphForTest>();
}

TEST(ConnectedComponentsUsingDfsTest, GetComponentIdWorks) {
    GraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    graph.connect(4, 5);
    graph.connect(6, 7);
    ConnectedComponentsForTest connectedComponents(graph);

    EXPECT_EQ(1, connectedComponents.getComponentId(0));
    EXPECT_EQ(1, connectedComponents.getComponentId(1));
    EXPECT_EQ(1, connectedComponents.getComponentId(2));
    EXPECT_EQ(1, connectedComponents.getComponentId(3));
    EXPECT_EQ(2, connectedComponents.getComponentId(4));
    EXPECT_EQ(2, connectedComponents.getComponentId(5));
    EXPECT_EQ(3, connectedComponents.getComponentId(6));
    EXPECT_EQ(3, connectedComponents.getComponentId(7));
}

}  // namespace algorithm

}  // namespace alba
