#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfsWithDistanceCount.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using ContentMapForTest = GraphTypes<VertexForTest>::VertexToUnsignedIntMap;
using GraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
using PathSearchForTest = PathSearchUsingDfsWithDistanceCount<VertexForTest>;

void putConnectionsForTest(GraphForTest & graph)
{
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 5U);
    graph.connect(2U, 1U);
    graph.connect(2U, 3U);
    graph.connect(2U, 4U);
    graph.connect(3U, 4U);
    graph.connect(3U, 5U);
}
}

TEST(PathSearchUsingDfsWithDistanceCountTest, GetDistanceToWorksWithDirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0U});

    EXPECT_EQ(0U, pathSearch.getDistanceTo(0U));
    EXPECT_EQ(1U, pathSearch.getDistanceTo(1U));
    EXPECT_EQ(1U, pathSearch.getDistanceTo(2U));
    EXPECT_EQ(2U, pathSearch.getDistanceTo(3U));
    EXPECT_EQ(3U, pathSearch.getDistanceTo(4U));
    EXPECT_EQ(3U, pathSearch.getDistanceTo(5U));
    EXPECT_EQ(0U, pathSearch.getDistanceTo(6U));
}

TEST(PathSearchUsingDfsWithDistanceCountTest, GetEndVertexToDistanceCountMapWorksWithDirectedGraph)
{
    GraphForTest graph;
    putConnectionsForTest(graph);
    PathSearchForTest pathSearch(graph, {0U});

    ContentMapForTest expectedMap{{1U, 1U}, {2U, 1U}, {3U, 2U}, {4U, 3U}, {5U, 3U}};
    EXPECT_EQ(expectedMap, pathSearch.getEndVertexToDistanceCountMap());
}

}

}
