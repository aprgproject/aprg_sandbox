#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = PathSearchUsingDfs<VertexForTest>;

void putConnectionsForTest(GraphForTest& graph) {
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 5);
    graph.connect(2, 1);
    graph.connect(2, 3);
    graph.connect(2, 4);
    graph.connect(3, 4);
    graph.connect(3, 5);
}
}  // namespace

TEST(PathSearchUsingDfsTest, HasPathToWorksWithDirectedGraph) {
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

TEST(PathSearchUsingDfsTest, GetOrderedPathToWorksWithDirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getOrderedPathTo(1));
    EXPECT_EQ(PathForTest({0, 2}), pathSearch.getOrderedPathTo(2));
    EXPECT_EQ(PathForTest({0, 2, 3}), pathSearch.getOrderedPathTo(3));
    EXPECT_EQ(PathForTest({0, 2, 3, 4}), pathSearch.getOrderedPathTo(4));
    EXPECT_EQ(PathForTest({0, 2, 3, 5}), pathSearch.getOrderedPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6));
}

TEST(PathSearchUsingDfsTest, GetOrderedPathToWorksWithDirectedGraphWithMultipleStartingPoints) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0, 2});

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getOrderedPathTo(1));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(2));
    EXPECT_EQ(PathForTest({2, 3}), pathSearch.getOrderedPathTo(3));
    EXPECT_EQ(PathForTest({2, 3, 4}), pathSearch.getOrderedPathTo(4));
    EXPECT_EQ(PathForTest({2, 3, 5}), pathSearch.getOrderedPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6));
}

TEST(PathSearchUsingDfsTest, GetPreviousVertexWorksWithDirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    EXPECT_EQ(0, pathSearch.getPreviousVertex(0));
    EXPECT_EQ(0, pathSearch.getPreviousVertex(1));
    EXPECT_EQ(0, pathSearch.getPreviousVertex(2));
    EXPECT_EQ(2, pathSearch.getPreviousVertex(3));
    EXPECT_EQ(3, pathSearch.getPreviousVertex(4));
    EXPECT_EQ(3, pathSearch.getPreviousVertex(5));
    EXPECT_EQ(0, pathSearch.getPreviousVertex(6));
}

TEST(PathSearchUsingDfsTest, ReinitializeStartingFromWorksWithDirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    pathSearch.reinitializeStartingFrom({2});

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0));
    EXPECT_EQ(PathForTest({2, 1}), pathSearch.getOrderedPathTo(1));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(2));
    EXPECT_EQ(PathForTest({2, 3}), pathSearch.getOrderedPathTo(3));
    EXPECT_EQ(PathForTest({2, 3, 4}), pathSearch.getOrderedPathTo(4));
    EXPECT_EQ(PathForTest({2, 3, 5}), pathSearch.getOrderedPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6));
}

TEST(PathSearchUsingDfsTest, ReinitializeStartingFromWorksWithDirectedGraphWithMultipleStartingPoints) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    pathSearch.reinitializeStartingFrom({0, 2});

    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getOrderedPathTo(1));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(2));
    EXPECT_EQ(PathForTest({2, 3}), pathSearch.getOrderedPathTo(3));
    EXPECT_EQ(PathForTest({2, 3, 4}), pathSearch.getOrderedPathTo(4));
    EXPECT_EQ(PathForTest({2, 3, 5}), pathSearch.getOrderedPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getOrderedPathTo(6));
}

}  // namespace algorithm

}  // namespace alba
