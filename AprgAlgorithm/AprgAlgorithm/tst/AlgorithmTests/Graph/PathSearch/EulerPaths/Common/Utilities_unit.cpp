#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/EulerPaths/Common/Utilities.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba {

namespace algorithm {

namespace {
using VertexForTest = int;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
}  // namespace

TEST(EulerPathUtilitiesTest, HasEulerCycleForUndirectedGraphWorksOnGraphWithAllEvenDegreesVertices) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(1, 2);

    EXPECT_TRUE(hasEulerCycleForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerCycleForUndirectedGraphWorksOnGraphWithNotAllEvenDegreesVertices) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_FALSE(hasEulerCycleForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForUndirectedGraphWorksOnGraphWithOneOddDegreeVertices) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);

    EXPECT_TRUE(hasEulerPathForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForUndirectedGraphWorksOnGraphWithTwoOddDegreesVertices) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    EXPECT_TRUE(hasEulerPathForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForUndirectedGraphWorksOnGraphWithThreeOddDegreesVertices) {
    UndirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);
    graph.connect(0, 3);

    EXPECT_FALSE(hasEulerPathForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerCycleForDirectedGraphWorksWithAllInDegreesEqualsOutDegrees) {
    DirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 0);

    EXPECT_TRUE(hasEulerCycleForDirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerCycleForDirectedGraphWorksOnGraphWithAllInDegreesNotEqualToOutDegrees) {
    DirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_FALSE(hasEulerCycleForDirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForDirectedGraphWorksOnGraphWithAllInDegreesEqualsOutDegrees) {
    DirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);
    graph.connect(2, 0);

    EXPECT_TRUE(hasEulerPathForDirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForDirectedGraphWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees) {
    DirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(1, 2);

    EXPECT_TRUE(hasEulerPathForDirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForDirectedGraphWorksWithMoreThanOneLesserAndGreaterInAndOutDegrees) {
    DirectedGraphForTest graph;
    graph.connect(0, 1);
    graph.connect(0, 2);

    EXPECT_FALSE(hasEulerPathForDirectedGraph(graph));
}

}  // namespace algorithm

}  // namespace alba
