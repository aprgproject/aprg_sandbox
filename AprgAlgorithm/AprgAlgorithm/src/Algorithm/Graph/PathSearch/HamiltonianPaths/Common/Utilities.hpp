#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
bool hasHamiltonianPathBecauseItsComplete(BaseGraph<Vertex> const& graph) {
    // A simple observation is that if the graph is complete, i.e., there is an edge between all pairs of nodes, it also
    // contains a Hamiltonian path.

    return GraphUtilities::isACompleteGraph(graph);
}

template <typename Vertex>
bool hasHamiltonianPathBecauseOfDiracTheorem(BaseGraph<Vertex> const& graph) {
    // Dirac’s theorem: If the degree of each node is at least n/2, the graph contains a Hamiltonian path.

    bool result(true);
    for (Vertex const& vertex : graph.getVertices()) {
        result = GraphUtilities::getDegreeAt(graph, vertex) * 2 >= graph.getNumberOfVertices();
        if (!result) {
            break;
        }
    }
    return result;
}

template <typename Vertex>
bool hasHamiltonianPathBecauseOfOreTheorem(BaseGraph<Vertex> const& graph) {
    // Ore’s theorem: If the sum of degrees of each non-adjacent pair of nodes is at least n, the graph contains a
    // Hamiltonian path. Formal statement:
    // -> Let G be a (finite and simple) graph with n ≥ 3 vertices.
    // ->  We denote by deg v the degree of a vertex v in G, i.e. the number of incident edges in G to v.
    // -> Then, Ore's theorem states that if:
    // ---> deg v + deg w ≥ n for every pair of distinct non-adjacent vertices v and w of G
    // -> then G is Hamiltonian.

    std::map<Vertex, unsigned int> vertexToDegreeMap;
    for (Vertex const& vertex : graph.getVertices()) {
        vertexToDegreeMap.emplace(vertex, GraphUtilities::getDegreeAt(graph, vertex));
    }

    unsigned int numberOfVertices(graph.getNumberOfVertices());
    for (Vertex const& vertex1 : graph.getVertices()) {
        for (Vertex const& vertex2 : graph.getVertices()) {
            if (vertex1 != vertex2 && !graph.isDirectlyConnected(vertex1, vertex2)) {
                bool isOreSatisfied = vertexToDegreeMap.at(vertex1) + vertexToDegreeMap.at(vertex2) >= numberOfVertices;
                if (!isOreSatisfied) {
                    return false;
                }
            }
        }
    }
    return true;
}

// A common property in these theorems and other results is that they guarantee the existence of a Hamiltonian path if
// the graph has a large number of edges. This makes sense, because the more edges the graph contains, the more
// possibilities there is to construct a Hamiltonian path.

}  // namespace algorithm

}  // namespace alba
