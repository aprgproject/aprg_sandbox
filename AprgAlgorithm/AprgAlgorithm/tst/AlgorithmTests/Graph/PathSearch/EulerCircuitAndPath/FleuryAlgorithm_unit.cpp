#include <Algorithm/Graph/PathSearch/EulerCircuitAndPath/FleuryAlgorithm.hpp>
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
using PathSearchForTest = FleuryAlgorithm<VertexForTest>;
}

TEST(FleuryAlgorithmTest, HasEulerCircuitWorksOnGraphWithAllEvenDegreesVertices)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    PathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerCircuit());
}

TEST(FleuryAlgorithmTest, HasEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearchForTest pathSearch(graph);

    EXPECT_FALSE(pathSearch.hasEulerCircuit());
}

TEST(FleuryAlgorithmTest, HasEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearchForTest pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerPath());
}

TEST(FleuryAlgorithmTest, HasEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    PathSearchForTest pathSearch(graph);

    EXPECT_FALSE(pathSearch.hasEulerPath());
}

TEST(FleuryAlgorithmTest, GetEulerCircuitWorksOnGraphWithAllEvenDegreesVertices)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    PathSearchForTest pathSearch(graph);

    PathForTest pathToVerify(pathSearch.getEulerCircuit());

    PathForTest pathToExpect{0U, 1U, 2U, 0U};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

TEST(FleuryAlgorithmTest, GetEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearchForTest pathSearch(graph);

    PathForTest pathToVerify(pathSearch.getEulerCircuit());

    EXPECT_TRUE(pathToVerify.empty());
}

TEST(FleuryAlgorithmTest, GetEulerPathWorksOnGraphWithTwoOddDegreesVertices)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearchForTest pathSearch(graph);

    PathForTest pathToVerify(pathSearch.getEulerPath());

    PathForTest pathToExpect{1U, 0U, 2U};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

TEST(FleuryAlgorithmTest, GetEulerPathWorksOnGraphWithThreeOddDegreesVertices)
{
    GraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    PathSearchForTest pathSearch(graph);

    PathForTest pathToVerify(pathSearch.getEulerCircuit());

    EXPECT_TRUE(pathToVerify.empty());
}

}

}
