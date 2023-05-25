#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = PathSearchUsingDfs<VertexForTest>;

void putConnectionsForTest(GraphForTest& graph) {
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 5);
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(2, 4);
    graph.connect(3, 4);
    graph.connect(3, 5);
}
}  // namespace

TEST(PathSearchUsingDfsTest, HasPathToWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    EXPECT_TRUE(pathSearch.hasPathTo(0));
    EXPECT_TRUE(pathSearch.hasPathTo(1));
    EXPECT_TRUE(pathSearch.hasPathTo(2));
    EXPECT_TRUE(pathSearch.hasPathTo(3));
    EXPECT_TRUE(pathSearch.hasPathTo(4));
    EXPECT_TRUE(pathSearch.hasPathTo(5));
    EXPECT_FALSE(pathSearch.hasPathTo(6));
}

TEST(PathSearchUsingDfsTest, GetOrderedPathToWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getOrderedPathTo(1));
    EXPECT_EQ(PathForTest({0, 1, 2}), pathSearch.getOrderedPathTo(2));
    EXPECT_EQ(PathForTest({0, 1, 2, 3}), pathSearch.getOrderedPathTo(3));
    EXPECT_EQ(PathForTest({0, 1, 2, 3, 4}), pathSearch.getOrderedPathTo(4));
    EXPECT_EQ(PathForTest({0, 1, 2, 3, 5}), pathSearch.getOrderedPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6));
}

TEST(PathSearchUsingDfsTest, GetOrderedPathToWorksWithUndirectedGraphWithMultipleStartingPoints) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0, 3});

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getOrderedPathTo(1));
    EXPECT_EQ(PathForTest({0, 1, 2}), pathSearch.getOrderedPathTo(2));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(3));
    EXPECT_EQ(PathForTest({3, 4}), pathSearch.getOrderedPathTo(4));
    EXPECT_EQ(PathForTest({3, 5}), pathSearch.getOrderedPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6));
}

TEST(PathSearchUsingDfsTest, GetPreviousVertexWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    EXPECT_EQ(0, pathSearch.getPreviousVertex(0));
    EXPECT_EQ(0, pathSearch.getPreviousVertex(1));
    EXPECT_EQ(1, pathSearch.getPreviousVertex(2));
    EXPECT_EQ(2, pathSearch.getPreviousVertex(3));
    EXPECT_EQ(3, pathSearch.getPreviousVertex(4));
    EXPECT_EQ(3, pathSearch.getPreviousVertex(5));
    EXPECT_EQ(0, pathSearch.getPreviousVertex(6));
}

TEST(PathSearchUsingDfsTest, ReinitializeStartingFromWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    pathSearch.reinitializeStartingFrom({3});

    EXPECT_EQ(PathForTest({3, 2, 0}), pathSearch.getOrderedPathTo(0));
    EXPECT_EQ(PathForTest({3, 2, 0, 1}), pathSearch.getOrderedPathTo(1));
    EXPECT_EQ(PathForTest({3, 2}), pathSearch.getOrderedPathTo(2));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(3));
    EXPECT_EQ(PathForTest({3, 2, 4}), pathSearch.getOrderedPathTo(4));
    EXPECT_EQ(PathForTest({3, 2, 0, 5}), pathSearch.getOrderedPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6));
}

TEST(PathSearchUsingDfsTest, ReinitializeStartingFromWorksWithUndirectedGraphWithMultipleStartingPoints) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    pathSearch.reinitializeStartingFrom({0, 3});

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getOrderedPathTo(1));
    EXPECT_EQ(PathForTest({0, 1, 2}), pathSearch.getOrderedPathTo(2));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(3));
    EXPECT_EQ(PathForTest({3, 4}), pathSearch.getOrderedPathTo(4));
    EXPECT_EQ(PathForTest({3, 5}), pathSearch.getOrderedPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6));
}

}  // namespace algorithm

}  // namespace alba
