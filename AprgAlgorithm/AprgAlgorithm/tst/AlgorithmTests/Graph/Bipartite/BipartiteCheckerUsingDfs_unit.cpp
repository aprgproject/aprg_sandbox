#include <Algorithm/Graph/Bipartite/BipartiteCheckerUsingDfs.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using Vertices = typename GraphTypes<VertexForTest>::Vertices;
using GraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using BipartiteCheckerForTest = BipartiteCheckerUsingDfs<VertexForTest>;
}  // namespace

TEST(BipartiteCheckerUsingDfsTest, IsBipartiteWorksforNonBarpartiteGraph) {
    GraphForTest nonBipartiteGraph;
    nonBipartiteGraph.connect(0, 1);
    nonBipartiteGraph.connect(0, 2);
    nonBipartiteGraph.connect(0, 3);
    nonBipartiteGraph.connect(3, 4);
    nonBipartiteGraph.connect(3, 5);
    nonBipartiteGraph.connect(4, 5);
    Vertices verticesWithFirstColor;
    Vertices verticesWithSecondColor;
    BipartiteCheckerForTest bipartiteChecker(nonBipartiteGraph);

    bipartiteChecker.retrieveVerticesWithColor(verticesWithFirstColor, verticesWithSecondColor);

    Vertices expectedWithFirstColor{0, 4};
    Vertices expectedWithSecondColor{1, 2, 3, 5};
    EXPECT_FALSE(bipartiteChecker.isBipartite());
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(0));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(1));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(2));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(3));
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(4));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(5));
    EXPECT_EQ(expectedWithFirstColor, verticesWithFirstColor);
    EXPECT_EQ(expectedWithSecondColor, verticesWithSecondColor);
}

TEST(BipartiteCheckerUsingDfsTest, IsBipartiteWorksforBarpartiteGraph) {
    GraphForTest bipartiteGraph;
    bipartiteGraph.connect(0, 1);
    bipartiteGraph.connect(0, 2);
    bipartiteGraph.connect(0, 3);
    bipartiteGraph.connect(3, 4);
    bipartiteGraph.connect(3, 6);
    bipartiteGraph.connect(4, 5);
    bipartiteGraph.connect(5, 6);
    Vertices verticesWithFirstColor;
    Vertices verticesWithSecondColor;
    BipartiteCheckerForTest bipartiteChecker(bipartiteGraph);

    bipartiteChecker.retrieveVerticesWithColor(verticesWithFirstColor, verticesWithSecondColor);

    Vertices expectedWithFirstColor{0, 4, 6};
    Vertices expectedWithSecondColor{1, 2, 3, 5};
    EXPECT_TRUE(bipartiteChecker.isBipartite());
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(0));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(1));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(2));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(3));
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(4));
    EXPECT_FALSE(bipartiteChecker.hasFirstColor(5));
    EXPECT_TRUE(bipartiteChecker.hasFirstColor(6));
    EXPECT_EQ(expectedWithFirstColor, verticesWithFirstColor);
    EXPECT_EQ(expectedWithSecondColor, verticesWithSecondColor);
}

}  // namespace algorithm

}  // namespace alba
