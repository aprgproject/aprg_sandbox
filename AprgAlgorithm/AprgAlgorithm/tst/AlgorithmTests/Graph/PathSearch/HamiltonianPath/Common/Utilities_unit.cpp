#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/PathSearch/HamiltonianPath/Common/Utilities.hpp>
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

TEST(HamiltonianPathUtilitiesTest, HasHamiltonianPathBecauseItsCompleteWorks)
{
    UndirectedGraphForTest nonCompleteGraph;
    nonCompleteGraph.connect(0U, 1U);
    nonCompleteGraph.connect(0U, 2U);
    UndirectedGraphForTest completeGraph;
    completeGraph.connect(0U, 1U);
    completeGraph.connect(0U, 2U);
    completeGraph.connect(1U, 2U);

    EXPECT_FALSE(hasHamiltonianPathBecauseItsComplete(nonCompleteGraph));
    EXPECT_TRUE(hasHamiltonianPathBecauseItsComplete(completeGraph));
}

TEST(HamiltonianPathUtilitiesTest, HasHamiltonianPathBecauseOfDiracTheoremWorks)
{
    UndirectedGraphForTest graphWithNoPath; // Has min degree of 1 but half or number of vertices is 2
    graphWithNoPath.connect(0U, 1U);
    graphWithNoPath.connect(0U, 2U);
    graphWithNoPath.connect(0U, 3U);
    UndirectedGraphForTest graphWithPathButNotSatisfied;
    graphWithPathButNotSatisfied.connect(1U, 2U);
    graphWithPathButNotSatisfied.connect(2U, 3U);
    graphWithPathButNotSatisfied.connect(3U, 4U);
    graphWithPathButNotSatisfied.connect(4U, 5U);
    graphWithPathButNotSatisfied.connect(5U, 1U);
    UndirectedGraphForTest graphWithPathAndSatisfied;
    graphWithNoPath.connect(0U, 1U);
    graphWithNoPath.connect(0U, 2U);

    EXPECT_FALSE(hasHamiltonianPathBecauseOfDiracTheorem(graphWithNoPath));
    EXPECT_FALSE(hasHamiltonianPathBecauseOfDiracTheorem(graphWithPathButNotSatisfied));
    EXPECT_TRUE(hasHamiltonianPathBecauseOfDiracTheorem(graphWithPathAndSatisfied));
}

TEST(HamiltonianPathUtilitiesTest, HasHamiltonianPathBecauseOfOreTheoremWorks)
{
    UndirectedGraphForTest graphWithNoPath;
    graphWithNoPath.connect(1U, 2U);
    graphWithNoPath.connect(1U, 4U);
    graphWithNoPath.connect(2U, 3U);
    graphWithNoPath.connect(2U, 5U);
    graphWithNoPath.connect(3U, 5U);
    graphWithNoPath.connect(4U, 5U);
    UndirectedGraphForTest graphWithPathButNotSatisfied;
    graphWithPathButNotSatisfied.connect(1U, 2U);
    graphWithPathButNotSatisfied.connect(2U, 3U);
    graphWithPathButNotSatisfied.connect(3U, 4U);
    graphWithPathButNotSatisfied.connect(4U, 5U);
    graphWithPathButNotSatisfied.connect(5U, 1U);
    UndirectedGraphForTest graphWithPathAndSatisfied;
    graphWithPathAndSatisfied.connect(1U, 2U);
    graphWithPathAndSatisfied.connect(2U, 3U);
    graphWithPathAndSatisfied.connect(3U, 4U);
    graphWithPathAndSatisfied.connect(4U, 1U);

    EXPECT_FALSE(hasHamiltonianPathBecauseOfOreTheorem(graphWithNoPath));
    EXPECT_FALSE(hasHamiltonianPathBecauseOfOreTheorem(graphWithPathButNotSatisfied));
    EXPECT_TRUE(hasHamiltonianPathBecauseOfOreTheorem(graphWithPathAndSatisfied));
}

}

}