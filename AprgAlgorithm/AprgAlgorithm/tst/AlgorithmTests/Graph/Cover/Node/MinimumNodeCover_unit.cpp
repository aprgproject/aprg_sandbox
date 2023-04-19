#include <Algorithm/Graph/Cover/Node/MinimumNodeCover.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using Edges = typename GraphTypes<VertexForTest>::Edges;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using MinimumNodeCoverForTest = MinimumNodeCover<VertexForTest>;

VertexForTest newSourceVertex = 0xFFFFFFFEU;
VertexForTest newSinkVertex = 0xFFFFFFFFU;
}

TEST(MinimumNodeCoverTest, GetMinimumNodeCoverSizeWorksOnExample1)
{
    GraphForTest graph;
    graph.connect(1U, 5U);
    graph.connect(2U, 7U);
    graph.connect(3U, 5U);
    graph.connect(3U, 6U);
    graph.connect(3U, 8U);
    graph.connect(4U, 7U);
    MinimumNodeCoverForTest minimumNodeCover(graph);

    EXPECT_EQ(3U, minimumNodeCover.getMinimumNodeCoverSize(newSourceVertex, newSinkVertex));
}

TEST(MinimumNodeCoverTest, GetMaximumIndependentSetSizeWorksOnExample1){
    GraphForTest graph;
    graph.connect(1U, 5U);
    graph.connect(2U, 7U);
    graph.connect(3U, 5U);
    graph.connect(3U, 6U);
    graph.connect(3U, 8U);
    graph.connect(4U, 7U);
    MinimumNodeCoverForTest minimumNodeCover(graph);

    EXPECT_EQ(5U, minimumNodeCover.getMaximumIndependentSetSize(newSourceVertex, newSinkVertex));
}

}
}
