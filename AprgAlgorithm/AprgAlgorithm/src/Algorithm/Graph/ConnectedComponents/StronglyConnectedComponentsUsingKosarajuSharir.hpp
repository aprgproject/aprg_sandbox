#pragma once

#include <Algorithm/Graph/ConnectedComponents/Common/BaseConnectedComponentsWithVertexToComponentIdMap.hpp>
#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

#include <map>

namespace alba {

namespace algorithm {

template <typename Vertex>
class StronglyConnectedComponentsUsingKosarajuSharir
    : public BaseConnectedComponentsWithVertexToComponentIdMap<Vertex, BaseDirectedGraph<Vertex>> {
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using BaseClass = BaseConnectedComponentsWithVertexToComponentIdMap<Vertex, BaseDirectedGraphWithVertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using DirectedGraphWithListOfEdgesWithVertex = DirectedGraphWithListOfEdges<Vertex>;
    using VertexToIntMap = typename GraphTypes<Vertex>::VertexToIntMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    StronglyConnectedComponentsUsingKosarajuSharir(BaseDirectedGraphWithVertex const& graph)
        : BaseClass(graph),
          b_graph(BaseClass::m_graph),
          b_numberOfComponentIds(BaseClass::m_numberOfComponentIds),
          b_vertexToComponentIdMap(BaseClass::m_vertexToComponentIdMap) {
        initialize();
    }

private:
    void initialize() {
        // Kosaraju Sharir algorithm works on reversing directions and iterating vertices in topological order
        // and iterating that vertices using DFS on the original graph with original directions

        // This works because:
        // -> reversing the edges -> reverses the dependency of the vertices in the graph
        // -> traversing the vertices in topological order -> means that vertices in a connected component is traversed
        // only once
        // -> this means contracting each strong component into a single vertex
        // and we can increment the id when one vertex finishes DFS (in the original graph)

        b_numberOfComponentIds = 0;
        DirectedGraphWithListOfEdgesWithVertex graphWithReversedDirections(getGraphWithReversedDirections(b_graph));
        VertexOrderingUsingDfs<Vertex> vertexOrdering(graphWithReversedDirections);
        for (Vertex const& vertex : vertexOrdering.getVerticesInTopologicalOrder()) {
            if (m_processedVertices.isNotFound(vertex)) {
                ++b_numberOfComponentIds;
                traverseUsingDfs(vertex);
            }
        }
    }

    void traverseUsingDfs(Vertex const& vertex) {
        m_processedVertices.putVertex(vertex);
        b_vertexToComponentIdMap[vertex] = b_numberOfComponentIds;
        for (Vertex const& adjacentVertex : b_graph.getAdjacentVerticesAt(vertex)) {
            if (m_processedVertices.isNotFound(adjacentVertex)) {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    DirectedGraphWithListOfEdgesWithVertex getGraphWithReversedDirections(
        BaseDirectedGraphWithVertex const& graph) const {
        DirectedGraphWithListOfEdgesWithVertex result;
        for (auto const& [startVertexOfEdge, endVertexOfEdge] : graph.getEdges()) {
            result.connect(endVertexOfEdge, startVertexOfEdge);
        }
        return result;
    }

    BaseDirectedGraphWithVertex const& b_graph;
    int& b_numberOfComponentIds;
    VertexToIntMap& b_vertexToComponentIdMap;
    CheckableVerticesWithVertex m_processedVertices;
};

// Algorithm in short terms:
// Perform two DFS.
// First DFS: Reverse directions of the graph and get topological sort ordered vertices.
// Second DFS: Perform DFS starting at topological sorted vertices(from first DFS),
// and add a new component ID every time a new (and unprocessed) start vertex is processed

// Linear time because DFS.

// Strong components in a graph is the same with the graph with reversed directions
// Contract each strong component into a single vertex

// Simple algorithm for computing strong components.
// -> Phase 1: run DFS on GR(graph with reversed directions) to compute reverse postorder.
// -> Phase 2: run DFS on G(original graph), traversing vertices in the order determined in the first phase

// Kosaraju-Sharir algorithm
// Proposition: Kosaraju-Sharir algorithm computes the strong components of a digraph in time proportional to E+V.
// Proof:
// -> running time: bottleneck is running DFS twice
// -> correctness: tricky
// -> implementation: easy

// Other discussions:
// Kosaraju’s algorithm is an efficient method for finding the strongly connected components of a directed graph.
// The algorithm performs two depth-first searches:
// the first search constructs a list of nodes according to the structure of the graph,
// and the second search forms the strongly connected components.

// Other analysis:
// The time complexity of the algorithm is O(n + m), because the algorithm performs two depth-first searches.
// Note: n is the number of nodes and m is the number of edges.

}  // namespace algorithm

}  // namespace alba
