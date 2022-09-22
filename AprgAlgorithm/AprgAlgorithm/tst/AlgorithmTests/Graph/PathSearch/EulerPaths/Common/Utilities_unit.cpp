#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/EulerPaths/Common/Utilities.hpp>
#include <Algorithm/Graph/UndirectedGraph/UndirectedGraphWithListOfEdges.hpp>

#include <gtest/gtest.h>

namespace alba
{

namespace algorithm
{

namespace
{
using VertexForTest = unsigned int;
using UndirectedGraphForTest = UndirectedGraphWithListOfEdges<VertexForTest>;
using DirectedGraphForTest = DirectedGraphWithListOfEdges<VertexForTest>;
}

TEST(EulerPathUtilitiesTest, HasEulerCycleForUndirectedGraphWorksOnGraphWithAllEvenDegreesVertices)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(1U, 2U);

    EXPECT_TRUE(hasEulerCycleForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerCycleForUndirectedGraphWorksOnGraphWithNotAllEvenDegreesVertices)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_FALSE(hasEulerCycleForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForUndirectedGraphWorksOnGraphWithOneOddDegreeVertices)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);

    EXPECT_TRUE(hasEulerPathForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForUndirectedGraphWorksOnGraphWithTwoOddDegreesVertices)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    EXPECT_TRUE(hasEulerPathForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForUndirectedGraphWorksOnGraphWithThreeOddDegreesVertices)
{
    UndirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);
    graph.connect(0U, 3U);

    EXPECT_FALSE(hasEulerPathForUndirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerCycleForDirectedGraphWorksWithAllInDegreesEqualsOutDegrees)
{
    DirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 0U);

    EXPECT_TRUE(hasEulerCycleForDirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerCycleForDirectedGraphWorksOnGraphWithAllInDegreesNotEqualToOutDegrees)
{
    DirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_FALSE(hasEulerCycleForDirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForDirectedGraphWorksOnGraphWithAllInDegreesEqualsOutDegrees)
{
    DirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);
    graph.connect(2U, 0U);

    EXPECT_TRUE(hasEulerPathForDirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForDirectedGraphWorksOnGraphWithOneLesserAndGreaterInAndOutDegrees)
{
    DirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(1U, 2U);

    EXPECT_TRUE(hasEulerPathForDirectedGraph(graph));
}

TEST(EulerPathUtilitiesTest, HasEulerPathForDirectedGraphWorksWithMoreThanOneLesserAndGreaterInAndOutDegrees)
{
    DirectedGraphForTest graph;
    graph.connect(0U, 1U);
    graph.connect(0U, 2U);

    EXPECT_FALSE(hasEulerPathForDirectedGraph(graph));
}

}

}
