#include <Algorithm/Graph/Tree/SpanningTree/CountSpanningTrees.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using CountTrees = CountSpanningTrees<VertexForTest>;
}

TEST(CountSpanningTreesTest, GetCountWorks)
{
    UndirectedGraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(1U, 4U);
    graph.connect(3U, 4U);

    EXPECT_EQ(3U, CountTrees::getCount<5U>(graph));
}

}

}
