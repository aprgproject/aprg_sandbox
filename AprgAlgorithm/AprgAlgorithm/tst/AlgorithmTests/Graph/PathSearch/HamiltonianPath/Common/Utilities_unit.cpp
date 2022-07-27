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
    UndirectedGraphForTest graph1; // Has min degree of 1 but half or number of vertices is 2
    graph1.connect(0U, 1U);
    graph1.connect(0U, 2U);
    graph1.connect(0U, 3U);
    UndirectedGraphForTest graph2; // Has min degree of 1 and half or number of vertices is 1 (Note: this has no hamiltonian path)
    graph1.connect(0U, 1U);
    graph1.connect(0U, 2U);

    EXPECT_FALSE(hasHamiltonianPathBecauseOfDiracTheorem(graph1));
    EXPECT_TRUE(hasHamiltonianPathBecauseOfDiracTheorem(graph2));
}
}

}
