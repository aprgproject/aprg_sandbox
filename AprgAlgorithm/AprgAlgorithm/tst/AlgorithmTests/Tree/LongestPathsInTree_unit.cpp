#include <Algorithm/Graph/Tree/LongestPathsInTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>
namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using PathForTest = GraphTypes<VertexForTest>::Path;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = LongestPathsInTree<VertexForTest>;
using EndPointPairsForTest = typename LongestPathsInTree<VertexForTest>::EndPointPairs;

void putConnectionsForTest(GraphForTest & graph)
{
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(2U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 7U);
}
}

TEST(LongestPathsInTreeTest, GetEndPointPairsOfLongestPathsWorks)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph);
    pathSearch.searchForAllEndPointPairs();

    EndPointPairsForTest endPointPairsToVerify(pathSearch.getEndPointPairsOfLongestPaths());

    EndPointPairsForTest endPointPairsToExpect{{5U, 7U}, {6U, 7U}, {7U, 5U}, {7U, 6U}};
    EXPECT_EQ(endPointPairsToExpect, endPointPairsToVerify);
}

TEST(LongestPathsInTreeTest, GetLongestDistanceWorks)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph);
    pathSearch.searchForAllEndPointPairs();

    EXPECT_EQ(4U, pathSearch.getLongestDistance());
}

TEST(LongestPathsInTreeTest, SearchForAtLeastOneEndPointPairWorks)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph);

    pathSearch.searchForAtLeastOneEndPointPair();

    EndPointPairsForTest endPointPairsToVerify(pathSearch.getEndPointPairsOfLongestPaths());

    EndPointPairsForTest endPointPairsToExpect{{5U, 7U}};
    EXPECT_EQ(endPointPairsToExpect, endPointPairsToVerify);
}

TEST(LongestPathsInTreeTest, SearchForAllEndPointPairsWorks)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph);

    pathSearch.searchForAllEndPointPairs();

    EndPointPairsForTest endPointPairsToVerify(pathSearch.getEndPointPairsOfLongestPaths());
    EndPointPairsForTest endPointPairsToExpect{{5U, 7U}, {6U, 7U}, {7U, 5U}, {7U, 6U}};
    EXPECT_EQ(endPointPairsToExpect, endPointPairsToVerify);
}

}

}
