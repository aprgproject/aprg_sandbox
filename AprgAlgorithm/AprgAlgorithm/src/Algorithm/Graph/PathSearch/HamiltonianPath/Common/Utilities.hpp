#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
bool hasHamiltonianPathBecauseItsComplete(BaseGraph<Vertex> const& graph)
{
    // A simple observation is that if the graph is complete, i.e., there is an edge between all pairs of nodes, it also contains a Hamiltonian path.

    return GraphUtilities::isACompleteGraph(graph);
}

template <typename Vertex>
bool hasHamiltonianPathBecauseOfDiracTheorem(BaseGraph<Vertex> const& graph)
{
    // Dirac’s theorem: If the degree of each node is at least n/2, the graph contains a Hamiltonian path.

    return GraphUtilities::getMinDegree(graph) >= graph.getNumberOfVertices()/2;
}

template <typename Vertex>
bool hasHamiltonianPathBecauseOfOreTheorem(BaseGraph<Vertex> const& graph)
{
    // Ore’s theorem: If the sum of degrees of each non-adjacent pair of nodes is at least n, the graph contains a Hamiltonian path.

    return GraphUtilities::isACompleteGraph(graph);
}

}

}
