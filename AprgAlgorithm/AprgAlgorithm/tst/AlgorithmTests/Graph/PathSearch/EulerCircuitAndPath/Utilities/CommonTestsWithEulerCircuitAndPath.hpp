#pragma once

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithEulerCircuitAndPath
{

template <typename PathSearch, typename Graph>
void testHasEulerCircuitWorksOnGraphWithAllEvenDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerCircuit());
}

template <typename PathSearch, typename Graph>
void testHasEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearch pathSearch(graph);

    EXPECT_FALSE(pathSearch.hasEulerCircuit());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithTwoOddDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerPath());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithThreeOddDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    PathSearch pathSearch(graph);

    EXPECT_FALSE(pathSearch.hasEulerPath());
}

template <typename PathSearch, typename Graph>
void testGetEulerCircuitWorksOnGraphWithAllEvenDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerCircuit());

    typename PathSearch::Path pathToExpect{0U, 1U, 2U, 0U};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

template <typename PathSearch, typename Graph>
void testGetEulerCircuitWorksOnGraphWithNotAllEvenDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerCircuit());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerPathWorksOnGraphWithTwoOddDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerPath());

    typename PathSearch::Path pathToExpect{1U, 0U, 2U};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

template <typename PathSearch, typename Graph>
void testGetEulerPathWorksOnGraphWithThreeOddDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerCircuit());

    EXPECT_TRUE(pathToVerify.empty());
}

}

}

}
