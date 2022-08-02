#include <Algorithm/Graph/Bipartite/BipartiteCheckerUsingDfs.hpp>
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
using BipartiteCheckerForTest = BipartiteCheckerUsingDfs<VertexForTest>;
}

TEST(BipartiteCheckerUsingDfsTest, IsBipartiteWorksforNonBarpartiteGraph)
{
    GraphForTest nonBipartiteGraph;
    nonBipartiteGraph.connect(0U, 1U);
    nonBipartiteGraph.connect(0U, 2U);
    nonBipartiteGraph.connect(0U, 3U);
    nonBipartiteGraph.connect(3U, 4U);
    nonBipartiteGraph.connect(3U, 5U);
    nonBipartiteGraph.connect(4U, 5U);
    BipartiteCheckerForTest bipartiteChecker(nonBipartiteGraph);

    EXPECT_FALSE(bipartiteChecker.isBipartite());
    EXPECT_FALSE(bipartiteChecker.getColor(0U));
    EXPECT_TRUE(bipartiteChecker.getColor(1U));
    EXPECT_TRUE(bipartiteChecker.getColor(2U));
    EXPECT_TRUE(bipartiteChecker.getColor(3U));
    EXPECT_FALSE(bipartiteChecker.getColor(4U));
    EXPECT_TRUE(bipartiteChecker.getColor(5U));
}

TEST(BipartiteCheckerUsingDfsTest, IsBipartiteWorksforBarpartiteGraph)
{
    GraphForTest bipartiteGraph;
    bipartiteGraph.connect(0U, 1U);
    bipartiteGraph.connect(0U, 2U);
    bipartiteGraph.connect(0U, 3U);
    bipartiteGraph.connect(3U, 4U);
    bipartiteGraph.connect(3U, 6U);
    bipartiteGraph.connect(4U, 5U);
    bipartiteGraph.connect(5U, 6U);
    BipartiteCheckerForTest bipartiteChecker(bipartiteGraph);

    EXPECT_TRUE(bipartiteChecker.isBipartite());
    EXPECT_FALSE(bipartiteChecker.getColor(0U));
    EXPECT_TRUE(bipartiteChecker.getColor(1U));
    EXPECT_TRUE(bipartiteChecker.getColor(2U));
    EXPECT_TRUE(bipartiteChecker.getColor(3U));
    EXPECT_FALSE(bipartiteChecker.getColor(4U));
    EXPECT_TRUE(bipartiteChecker.getColor(5U));
    EXPECT_FALSE(bipartiteChecker.getColor(6U));
}

}

}
