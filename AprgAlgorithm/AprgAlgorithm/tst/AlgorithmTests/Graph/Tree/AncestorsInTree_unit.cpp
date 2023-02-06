#include <Algorithm/Graph/Tree/AncestorsInTree.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using QueryForTest = AncestorsInTree<VertexForTest>;
}

TEST(AncestorsInTreeTest, GetAncestorWorks)
{
    GraphForTest graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 4U);
    graph.connect(1U, 5U);
    graph.connect(2U, 6U);
    graph.connect(4U, 3U);
    graph.connect(4U, 7U);
    graph.connect(7U, 8U);
    QueryForTest query(graph, 1U);

    EXPECT_EQ(1U, query.getAncestor(2U, 1U));
    EXPECT_EQ(7U, query.getAncestor(8U, 1U));
    EXPECT_EQ(4U, query.getAncestor(8U, 2U));
    EXPECT_EQ(1U, query.getAncestor(8U, 3U));
}

}

}
