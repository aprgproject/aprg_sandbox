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
using Vertices = typename GraphTypes<VertexForTest>::Vertices;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using BipartiteCheckerForTest = BipartiteCheckerUsingDfs<VertexForTest>;
}
TEST(BipartiteCheckerUsingDfsTest, IsBipartiteWorksforNonBarpartiteGraph)
{
    GraphForTest nonBipartiteGraph;    nonBipartiteGraph.connect(0U, 1U);
    nonBipartiteGraph.connect(0U, 2U);
    nonBipartiteGraph.connect(0U, 3U);
    nonBipartiteGraph.connect(3U, 4U);
    nonBipartiteGraph.connect(3U, 5U);
    nonBipartiteGraph.connect(4U, 5U);
    Vertices verticesWithFirstColor;
    Vertices verticesWithSecondColor;
    BipartiteCheckerForTest bipartiteChecker(nonBipartiteGraph);

    bipartiteChecker.retrieveVerticesWithColor(verticesWithFirstColor, verticesWithSecondColor);

    Vertices expectedWithFirstColor{0U, 4U};
    Vertices expectedWithSecondColor{1U, 2U, 3U, 5U};
    EXPECT_FALSE(bipartiteChecker.isBipartite());
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(0U));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(1U));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(2U));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(3U));
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(4U));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(5U));
    EXPECT_EQ(expectedWithFirstColor, verticesWithFirstColor);
    EXPECT_EQ(expectedWithSecondColor, verticesWithSecondColor);
}

TEST(BipartiteCheckerUsingDfsTest, IsBipartiteWorksforBarpartiteGraph){
    GraphForTest bipartiteGraph;
    bipartiteGraph.connect(0U, 1U);
    bipartiteGraph.connect(0U, 2U);    bipartiteGraph.connect(0U, 3U);
    bipartiteGraph.connect(3U, 4U);
    bipartiteGraph.connect(3U, 6U);
    bipartiteGraph.connect(4U, 5U);
    bipartiteGraph.connect(5U, 6U);
    Vertices verticesWithFirstColor;
    Vertices verticesWithSecondColor;
    BipartiteCheckerForTest bipartiteChecker(bipartiteGraph);

    bipartiteChecker.retrieveVerticesWithColor(verticesWithFirstColor, verticesWithSecondColor);

    Vertices expectedWithFirstColor{0U, 4U, 6U};
    Vertices expectedWithSecondColor{1U, 2U, 3U, 5U};
    EXPECT_TRUE(bipartiteChecker.isBipartite());
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(0U));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(1U));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(2U));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(3U));
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(4U));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(5U));
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(6U));
    EXPECT_EQ(expectedWithFirstColor, verticesWithFirstColor);
    EXPECT_EQ(expectedWithSecondColor, verticesWithSecondColor);
}

}
}