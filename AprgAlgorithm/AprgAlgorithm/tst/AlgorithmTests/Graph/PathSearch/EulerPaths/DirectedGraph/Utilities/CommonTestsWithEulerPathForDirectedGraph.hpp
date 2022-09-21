#pragma once

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace CommonTestsWithEulerPathForDirectedGraph
{

template <typename PathSearch, typename Graph>
void testHasEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 0U);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerCycle());
}

template <typename PathSearch, typename Graph>
void testHasEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearch pathSearch(graph);

    EXPECT_FALSE(pathSearch.hasEulerCycle());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithAllInDegreesEqualsOutDegrees()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 0U);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerPath());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerPath());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees()
{
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
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
void testGetEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees()
{
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 0U);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerCycle());

    Path pathToExpect{0U, 1U, 2U, 0U};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees()
{
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerCycle());

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
void testGetEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees()
{
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());

    Path pathToExpect{0U, 1U, 2U};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

template <typename PathSearch, typename Graph>
void testGetEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees()
{
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerCycle());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleAndPathWorksOnExample1()
{
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(1U, 2U);
    graph.connect(2U, 3U);
    graph.connect(2U, 5U);
    graph.connect(3U, 5U);
    graph.connect(4U, 1U);
    graph.connect(5U, 4U);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());
    Path cycleToVerify(pathSearch.getEulerCycle());

    Path pathToExpect{1U, 2U, 3U, 5U, 5U, 4U, 1U};
    EXPECT_EQ(pathToExpect, pathToVerify);
    EXPECT_TRUE(cycleToVerify.empty());
}

}

}

}
