#pragma once

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace CommonTestsWithEulerPathForUndirectedGraph {

template <typename PathSearch, typename Graph>
void testHasEulerCycleWorksOnGraphWithAllEvenDegreesVertices() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerCycle());
}

template <typename PathSearch, typename Graph>
void testHasEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    PathSearch pathSearch(graph);

    EXPECT_FALSE(pathSearch.hasEulerCycle());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithOneOddDegreeVertices() {
    Graph graph;
    graph.connect(0, 1);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerPath());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithTwoOddDegreesVertices() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    PathSearch pathSearch(graph);

    EXPECT_TRUE(pathSearch.hasEulerPath());
}

template <typename PathSearch, typename Graph>
void testHasEulerPathWorksOnGraphWithThreeOddDegreesVertices() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
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
void testGetEulerCycleWorksOnGraphWithAllEvenDegreesVertices() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerCycle());

    typename PathSearch::Path pathToExpect{0, 1, 2, 0};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleWorksOnGraphWithNotAllEvenDegreesVertices() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerCycle());

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
void testGetEulerPathWorksOnGraphWithTwoOddDegreesVertices() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerPath());

    typename PathSearch::Path pathToExpect{1, 0, 2};
    EXPECT_EQ(pathToExpect, pathToVerify);
}

template <typename PathSearch, typename Graph>
void testGetEulerPathWorksOnGraphWithThreeOddDegreesVertices() {
    Graph graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);
    PathSearch pathSearch(graph);

    typename PathSearch::Path pathToVerify(pathSearch.getEulerCycle());

    EXPECT_TRUE(pathToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleAndPathWorksOnExample1() {
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(1, 2);
    graph.connect(1, 4);
    graph.connect(2, 3);
    graph.connect(2, 5);
    graph.connect(3, 5);
    graph.connect(5, 4);
    graph.connect(4, 1);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());
    Path cycleToVerify(pathSearch.getEulerCycle());

    Path pathToExpect{2, 1, 4, 5, 2, 3, 5};
    EXPECT_EQ(pathToExpect, pathToVerify);
    EXPECT_TRUE(cycleToVerify.empty());
}

template <typename PathSearch, typename Graph>
void testGetEulerCycleAndPathWorksOnExample2() {
    using Path = typename PathSearch::Path;
    Graph graph;
    graph.connect(1, 2);
    graph.connect(1, 3);
    graph.connect(2, 3);
    graph.connect(2, 5);
    graph.connect(2, 6);
    graph.connect(3, 4);
    graph.connect(3, 6);
    graph.connect(4, 7);
    graph.connect(5, 6);
    graph.connect(6, 7);
    PathSearch pathSearch(graph);

    Path pathToVerify(pathSearch.getEulerPath());
    Path cycleToVerify(pathSearch.getEulerCycle());

    Path pathToExpect{1, 2, 3, 4, 7, 6, 2, 5, 6, 3, 1};
    Path cycleToExpect{1, 2, 3, 4, 7, 6, 2, 5, 6, 3, 1};
    EXPECT_EQ(pathToExpect, pathToVerify);
    EXPECT_EQ(cycleToExpect, cycleToVerify);
}

}  // namespace CommonTestsWithEulerPathForUndirectedGraph

}  // namespace algorithm

}  // namespace alba
