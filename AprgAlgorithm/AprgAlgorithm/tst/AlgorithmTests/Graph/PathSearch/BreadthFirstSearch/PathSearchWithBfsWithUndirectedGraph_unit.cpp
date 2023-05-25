#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/PathSearchUsingBfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = PathSearchUsingBfs<VertexForTest>;

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

TEST(PathSearchUsingBfsTest, HasPathToWorksWithUndirectedGraph) {
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

TEST(PathSearchUsingBfsTest, GetShortestPathToWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getShortestPathTo(1));
    EXPECT_EQ(PathForTest({0, 2}), pathSearch.getShortestPathTo(2));
    EXPECT_EQ(PathForTest({0, 2, 3}), pathSearch.getShortestPathTo(3));
    EXPECT_EQ(PathForTest({0, 2, 4}), pathSearch.getShortestPathTo(4));
    EXPECT_EQ(PathForTest({0, 5}), pathSearch.getShortestPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(6));
}

TEST(PathSearchUsingBfsTest, GetShortestPathToWorksWithUndirectedGraphWithMultipleStartingPoints) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0, 3});

    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getShortestPathTo(1));
    EXPECT_EQ(PathForTest({3, 2}), pathSearch.getShortestPathTo(2));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(3));
    EXPECT_EQ(PathForTest({3, 4}), pathSearch.getShortestPathTo(4));
    EXPECT_EQ(PathForTest({3, 5}), pathSearch.getShortestPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(6));
}

TEST(PathSearchUsingBfsTest, GetPreviousVertexWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    EXPECT_EQ(0, pathSearch.getPreviousVertex(0));
    EXPECT_EQ(0, pathSearch.getPreviousVertex(1));
    EXPECT_EQ(0, pathSearch.getPreviousVertex(2));
    EXPECT_EQ(2, pathSearch.getPreviousVertex(3));
    EXPECT_EQ(2, pathSearch.getPreviousVertex(4));
    EXPECT_EQ(0, pathSearch.getPreviousVertex(5));
    EXPECT_EQ(0, pathSearch.getPreviousVertex(6));
}

TEST(PathSearchUsingBfsTest, ReinitializeStartingFromWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    pathSearch.reinitializeStartingFrom({3});

    EXPECT_EQ(PathForTest({3, 2, 0}), pathSearch.getShortestPathTo(0));
    EXPECT_EQ(PathForTest({3, 2, 1}), pathSearch.getShortestPathTo(1));
    EXPECT_EQ(PathForTest({3, 2}), pathSearch.getShortestPathTo(2));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(3));
    EXPECT_EQ(PathForTest({3, 4}), pathSearch.getShortestPathTo(4));
    EXPECT_EQ(PathForTest({3, 5}), pathSearch.getShortestPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(6));
}

TEST(PathSearchUsingBfsTest, ReinitializeStartingFromWorksWithUndirectedGraphWithMultipleStartingPoints) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0);

    pathSearch.reinitializeStartingFrom({0, 3});

    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(0));
    EXPECT_EQ(PathForTest({0, 1}), pathSearch.getShortestPathTo(1));
    EXPECT_EQ(PathForTest({3, 2}), pathSearch.getShortestPathTo(2));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(3));
    EXPECT_EQ(PathForTest({3, 4}), pathSearch.getShortestPathTo(4));
    EXPECT_EQ(PathForTest({3, 5}), pathSearch.getShortestPathTo(5));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(6));
}

}  // namespace algorithm

}  // namespace alba
