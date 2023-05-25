#pragma once

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace CommonTestsWithEulerPathForDirectedGraph {

template <typename PathSearch, typename Graph>
void testHasEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 0);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerCycle());
}

template <typename PathSearch, typename Graph>
void testHasEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    PathSearch pathSearch(graph);

    EXPECT_FALSE(pathSearch.hasEulerCycle());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithAllInDegreesEqualsOutDegrees() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 0);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerPath());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerPath());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    PathSearch pathSearch(graph);

    EXPECT_FALSE(pathSearch.hasEulerPath());
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleWorksOnEmptyGraph() {
    using Path = typename PathSearch::Path;
    Graph graph;
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerCycle());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleWorksOnGraphWithAllInDegreesEqualsOutDegrees() {
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 0);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerCycle());

    Path pathToExpect{0, 1, 2, 0};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleWorksOnGraphWithAllInDegreesNotEqualToOutDegrees() {
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerCycle());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerPathWorksOnEmptyGraph() {
    using Path = typename PathSearch::Path;
    Graph graph;
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerPathWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees() {
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());

    Path pathToExpect{0, 1, 2};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

template <typename PathSearch, typename Graph>
void testGetEulerPathWorksOnGraphWithMoreThanOneLesserAndGreaterInAndOutDegrees() {
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerCycle());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleAndPathWorksOnExample1() {
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(1, 2);
    graph.connect(2, 3);
    graph.connect(2, 5);
    graph.connect(3, 5);
    graph.connect(4, 1);
    graph.connect(5, 4);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());
    Path cycleToVerify(pathSearch.getEulerCycle());

    Path pathToExpect{1, 2, 3, 5, 5, 4, 1};
    EXPECT_EQ(pathToExpect, pathToVerify);
    EXPECT_TRUE(cycleToVerify.empty());
}

}  // namespace CommonTestsWithEulerPathForDirectedGraph

}  // namespace algorithm

}  // namespace alba
