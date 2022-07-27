#pragma once

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithEulerPathForUndirectedGraph
{

template <typename PathSearch, typename Graph>
void testHasEulerCycleWorksOnGraphWithAllEvenDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerCycle());
}

template <typename PathSearch, typename Graph>
void testHasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearch pathSearch(graph);

    EXPECT_FALSE(pathSearch.hasEulerCycle());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithOneOddDegreeVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerPath());
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
void testGetEulerCycleWorksOnEmptyGraph()
{
    using Path = typename PathSearch::Path;
    Graph graph;
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerCycle());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleWorksOnGraphWithAllEvenDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(1U, 2U);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerCycle());

    typename PathSearch::Path pathToExpect{0U, 1U, 2U, 0U};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerCycle());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerPathWorksOnEmptyGraph()
{
    using Path = typename PathSearch::Path;
    Graph graph;
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());

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

    typename PathSearch::Path pathToVerify(pathSearch.getEulerCycle());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleAndPathWorksOnExample1()
{
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 4U);
    graph.connect(2U, 3U);
    graph.connect(2U, 5U);
    graph.connect(3U, 5U);
    graph.connect(5U, 4U);
    graph.connect(4U, 1U);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());
    Path cycleToVerify(pathSearch.getEulerCycle());

    Path pathToExpect{2U, 1U, 4U, 5U, 2U, 3U, 5U};
    EXPECT_EQ(pathToExpect, pathToVerify);
    EXPECT_TRUE(cycleToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleAndPathWorksOnExample2()
{
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(1U, 2U);
    graph.connect(1U, 3U);
    graph.connect(2U, 3U);
    graph.connect(2U, 5U);
    graph.connect(2U, 6U);
    graph.connect(3U, 4U);
    graph.connect(3U, 6U);
    graph.connect(4U, 7U);
    graph.connect(5U, 6U);
    graph.connect(6U, 7U);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());
    Path cycleToVerify(pathSearch.getEulerCycle());

    Path pathToExpect{1U, 2U, 3U, 4U, 7U, 6U, 2U, 5U, 6U, 3U, 1U};
    Path cycleToExpect{1U, 2U, 3U, 4U, 7U, 6U, 2U, 5U, 6U, 3U, 1U};
    EXPECT_EQ(pathToExpect, pathToVerify);
    EXPECT_EQ(cycleToExpect, cycleToVerify);
}

}

}

}
