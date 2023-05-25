#include <Algorithm/Graph/Tree/LongestPathsInTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using LongestPathsForTest = LongestPathsInTree<VertexForTest>;
using EndPointPairsForTest = typename LongestPathsForTest::EndPointPairs;

void putConnectionsForTest(GraphForTest& graph) {
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(1, 4);
    graph.connect(2, 5);
    graph.connect(2, 6);
    graph.connect(4, 7);
}
}  // namespace

TEST(LongestPathsInTreeTest, GetEndPointPairsOfLongestPathsWorks) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    LongestPathsForTest longestPath(graph);
    longestPath.searchForAllEndPointPairs();

    EndPointPairsForTest endPointPairsToVerify(longestPath.getEndPointPairsOfLongestPaths());

    EndPointPairsForTest endPointPairsToExpect{{5, 7}, {6, 7}, {7, 5}, {7, 6}};
    EXPECT_EQ(endPointPairsToExpect, endPointPairsToVerify);
}

TEST(LongestPathsInTreeTest, GetLongestDistanceWorks) {
    // This function is coupled with search function
    GraphForTest graph;
    putConnectionsForTest(graph);
    LongestPathsForTest longestPath(graph);
    longestPath.searchForAllEndPointPairs();

    EXPECT_EQ(4, longestPath.getLongestDistance());
}

TEST(LongestPathsInTreeTest, SearchForAtLeastOneEndPointPairWorks) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    LongestPathsForTest longestPath(graph);

    longestPath.searchForAtLeastOneEndPointPair();

    EndPointPairsForTest endPointPairsToVerify(longestPath.getEndPointPairsOfLongestPaths());

    EndPointPairsForTest endPointPairsToExpect{{5, 7}};
    EXPECT_EQ(endPointPairsToExpect, endPointPairsToVerify);
}

TEST(LongestPathsInTreeTest, SearchForAllEndPointPairsWorks) {
    GraphForTest graph;
    putConnectionsForTest(graph);
    LongestPathsForTest longestPath(graph);

    longestPath.searchForAllEndPointPairs();

    EndPointPairsForTest endPointPairsToVerify(longestPath.getEndPointPairsOfLongestPaths());
    EndPointPairsForTest endPointPairsToExpect{{5, 7}, {6, 7}, {7, 5}, {7, 6}};
    EXPECT_EQ(endPointPairsToExpect, endPointPairsToVerify);
}

}  // namespace algorithm

}  // namespace alba
