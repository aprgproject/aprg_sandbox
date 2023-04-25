#include <Algorithm/Graph/Tree/LongestPathsInTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = unsigned int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using LongestPathsForTest = LongestPathsInTree<VertexForTest>;
using EndPointPairsForTest = typename LongestPathsForTest::EndPointPairs;

void putConnectionsForTest(GraphForTest& graph) {
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(2U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 7U);
}
}  // namespace

TEST(LongestPathsInTreeTest, GetEndPointPairsOfLongestPathsWorks) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    LongestPathsForTest longestPath(graph);
    longestPath.searchForAllEndPointPairs();

    EndPointPairsForTest endPointPairsToVerify(longestPath.getEndPointPairsOfLongestPaths());

    EndPointPairsForTest endPointPairsToExpect{{5U, 7U}, {6U, 7U}, {7U, 5U}, {7U, 6U}};
    EXPECT_EQ(endPointPairsToExpect, endPointPairsToVerify);
}

TEST(LongestPathsInTreeTest, GetLongestDistanceWorks) {
    // This function is coupled with search function
    GraphForTest graph;
    putConnectionsForTest(graph);
    LongestPathsForTest longestPath(graph);
    longestPath.searchForAllEndPointPairs();

    EXPECT_EQ(4U, longestPath.getLongestDistance());
}

TEST(LongestPathsInTreeTest, SearchForAtLeastOneEndPointPairWorks) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    LongestPathsForTest longestPath(graph);

    longestPath.searchForAtLeastOneEndPointPair();

    EndPointPairsForTest endPointPairsToVerify(longestPath.getEndPointPairsOfLongestPaths());

    EndPointPairsForTest endPointPairsToExpect{{5U, 7U}};
    EXPECT_EQ(endPointPairsToExpect, endPointPairsToVerify);
}

TEST(LongestPathsInTreeTest, SearchForAllEndPointPairsWorks) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    LongestPathsForTest longestPath(graph);

    longestPath.searchForAllEndPointPairs();

    EndPointPairsForTest endPointPairsToVerify(longestPath.getEndPointPairsOfLongestPaths());
    EndPointPairsForTest endPointPairsToExpect{{5U, 7U}, {6U, 7U}, {7U, 5U}, {7U, 6U}};
    EXPECT_EQ(endPointPairsToExpect, endPointPairsToVerify);
}

}  // namespace algorithm

}  // namespace alba
