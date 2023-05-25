#pragma once

#include <Algorithm/Graph/Bipartite/MaximumMatchings.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class MinimumNodeCover {
public:
    // Node cover are set of nodes that covers edges.

    // A minimum node cover of a graph is a minimum set of nodes such that each edge of the graph has at least one
    // endpoint in the set.

    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using MaximumMatchingsWithVertex = MaximumMatchings<Vertex>;

    MinimumNodeCover(BaseUndirectedGraphWithVertex const& graph) : m_graph(graph), m_maximumMatchings(m_graph) {}

    int getMinimumNodeCoverSize(Vertex const& newSourceVertex, Vertex const& newSinkVertex) const {
        // Using Konig's theorem:
        // A minimum node cover of a graph is a minimum set of nodes such that each edge of the graph has at least one
        // endpoint in the set. In a general graph, finding a minimum node cover is a NP-hard problem. However, if the
        // graph is bipartite, Konig’s theorem tells us that the size of a minimum node cover and the size of a maximum
        // matching are always equal.

        return m_maximumMatchings.getMaximumMatchings(newSourceVertex, newSinkVertex).size();
    }

    int getMaximumIndependentSetSize(Vertex const& newSourceVertex, Vertex const& newSinkVertex) const {
        // The nodes that do not belong to a minimum node cover form a maximum independent set.
        // This is the largest possible set of nodes such that no two nodes in the set are connected with an edge.
        // Once again, finding a maximum independent set in a general graph is a NP-hard problem,
        // but in a bipartite graph we can use Konig’s theorem to solve the problem efficiently.

        return m_graph.getNumberOfVertices() -
               m_maximumMatchings.getMaximumMatchings(newSourceVertex, newSinkVertex).size();
    }

private:
    BaseUndirectedGraphWithVertex const& m_graph;
    MaximumMatchingsWithVertex m_maximumMatchings;
};

}  // namespace algorithm

}  // namespace alba
