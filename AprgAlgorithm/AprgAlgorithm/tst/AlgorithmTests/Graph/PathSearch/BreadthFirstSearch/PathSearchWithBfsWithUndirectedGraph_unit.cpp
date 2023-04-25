#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/PathSearchUsingBfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = PathSearchUsingBfs<VertexForTest>;

void putConnectionsForTest(GraphForTest& graph) {
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
}
}  // namespace

TEST(PathSearchUsingBfsTest, HasPathToWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    EXPECT_TRUE(pathSearch.hasPathTo(0U));
    EXPECT_TRUE(pathSearch.hasPathTo(1U));
    EXPECT_TRUE(pathSearch.hasPathTo(2U));
    EXPECT_TRUE(pathSearch.hasPathTo(3U));
    EXPECT_TRUE(pathSearch.hasPathTo(4U));
    EXPECT_TRUE(pathSearch.hasPathTo(5U));
    EXPECT_FALSE(pathSearch.hasPathTo(6U));
}

TEST(PathSearchUsingBfsTest, GetShortestPathToWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(0U));
    EXPECT_EQ(PathForTest({0U, 1U}), pathSearch.getShortestPathTo(1U));
    EXPECT_EQ(PathForTest({0U, 2U}), pathSearch.getShortestPathTo(2U));
    EXPECT_EQ(PathForTest({0U, 2U, 3U}), pathSearch.getShortestPathTo(3U));
    EXPECT_EQ(PathForTest({0U, 2U, 4U}), pathSearch.getShortestPathTo(4U));
    EXPECT_EQ(PathForTest({0U, 5U}), pathSearch.getShortestPathTo(5U));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(6U));
}

TEST(PathSearchUsingBfsTest, GetShortestPathToWorksWithUndirectedGraphWithMultipleStartingPoints) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0U, 3U});

    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(0U));
    EXPECT_EQ(PathForTest({0U, 1U}), pathSearch.getShortestPathTo(1U));
    EXPECT_EQ(PathForTest({3U, 2U}), pathSearch.getShortestPathTo(2U));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(3U));
    EXPECT_EQ(PathForTest({3U, 4U}), pathSearch.getShortestPathTo(4U));
    EXPECT_EQ(PathForTest({3U, 5U}), pathSearch.getShortestPathTo(5U));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(6U));
}

TEST(PathSearchUsingBfsTest, GetPreviousVertexWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    EXPECT_EQ(0U, pathSearch.getPreviousVertex(0U));
    EXPECT_EQ(0U, pathSearch.getPreviousVertex(1U));
    EXPECT_EQ(0U, pathSearch.getPreviousVertex(2U));
    EXPECT_EQ(2U, pathSearch.getPreviousVertex(3U));
    EXPECT_EQ(2U, pathSearch.getPreviousVertex(4U));
    EXPECT_EQ(0U, pathSearch.getPreviousVertex(5U));
    EXPECT_EQ(0U, pathSearch.getPreviousVertex(6U));
}

TEST(PathSearchUsingBfsTest, ReinitializeStartingFromWorksWithUndirectedGraph) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    pathSearch.reinitializeStartingFrom({3U});

    EXPECT_EQ(PathForTest({3U, 2U, 0U}), pathSearch.getShortestPathTo(0U));
    EXPECT_EQ(PathForTest({3U, 2U, 1U}), pathSearch.getShortestPathTo(1U));
    EXPECT_EQ(PathForTest({3U, 2U}), pathSearch.getShortestPathTo(2U));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(3U));
    EXPECT_EQ(PathForTest({3U, 4U}), pathSearch.getShortestPathTo(4U));
    EXPECT_EQ(PathForTest({3U, 5U}), pathSearch.getShortestPathTo(5U));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(6U));
}

TEST(PathSearchUsingBfsTest, ReinitializeStartingFromWorksWithUndirectedGraphWithMultipleStartingPoints) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, 0U);

    pathSearch.reinitializeStartingFrom({0U, 3U});

    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(0U));
    EXPECT_EQ(PathForTest({0U, 1U}), pathSearch.getShortestPathTo(1U));
    EXPECT_EQ(PathForTest({3U, 2U}), pathSearch.getShortestPathTo(2U));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(3U));
    EXPECT_EQ(PathForTest({3U, 4U}), pathSearch.getShortestPathTo(4U));
    EXPECT_EQ(PathForTest({3U, 5U}), pathSearch.getShortestPathTo(5U));
    EXPECT_EQ(PathForTest(), pathSearch.getShortestPathTo(6U));
}

}  // namespace algorithm

}  // namespace alba
