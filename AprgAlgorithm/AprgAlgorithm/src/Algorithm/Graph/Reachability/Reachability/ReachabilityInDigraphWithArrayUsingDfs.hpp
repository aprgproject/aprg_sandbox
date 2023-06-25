#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/Reachability/Reachability/BaseReachabilityInDigraph.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex, int MAX_VERTEX_VALUE>
class ReachabilityInDigraphWithArrayUsingDfs : public BaseReachabilityInDigraph<Vertex> {
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using ArrayOfBool = std::array<bool, MAX_VERTEX_VALUE>;

    ReachabilityInDigraphWithArrayUsingDfs(BaseDirectedGraphWithVertex const& graph, Vertex const& sourceVertex)
        : m_graph(graph), m_sourceVertex(sourceVertex), m_isReachableArray{} {
        initialize();
    }

    bool isReachable(Vertex const& destinationVertex) const override {
        return m_isReachableArray[destinationVertex];
    }

private:
    bool isNotFound(Vertex const& vertex) const { return !m_isReachableArray[vertex]; }

    void initialize() {
        // no clearing because array is brace initialized        traverseUsingDfs(m_sourceVertex);
    }

    void traverseUsingDfs(Vertex const& vertex) {        m_isReachableArray[vertex] = true;
        for (Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex)) {
            if (isNotFound(adjacentVertex)) {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseDirectedGraphWithVertex const& m_graph;
    Vertex m_sourceVertex;
    ArrayOfBool m_isReachableArray;  // array for constant time query
};

}  // namespace algorithm

}  // namespace alba
