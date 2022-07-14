#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class StronglyConnectedComponentsUsingKosarajuSharir : public BaseConnectedComponents<Vertex>
{
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using DirectedGraphWithListOfEdgesWithVertex = DirectedGraphWithListOfEdges<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    StronglyConnectedComponentsUsingKosarajuSharir(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
        , m_numberOfComponentIds(0U)    {
        initialize();
    }

    bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const override
    {
        // Two vertices v and w are strongly connected if they are mutually reachable (so there is a v to w and w to v)
        auto it1 = m_vertexToComponentIdMap.find(vertex1);
        auto it2 = m_vertexToComponentIdMap.find(vertex2);
        bool result(false);
        if(it1 != m_vertexToComponentIdMap.cend()
                && it2 != m_vertexToComponentIdMap.cend())
        {
            result = it1->second == it2->second;
        }
        return result;
    }

    unsigned int getNumberOfComponentIds() const override
    {
        return m_numberOfComponentIds;
    }

private:

    DirectedGraphWithListOfEdgesWithVertex getGraphWithReversedDirections(BaseDirectedGraphWithVertex const& graph) const
    {
        DirectedGraphWithListOfEdgesWithVertex result;
        for(Edge const& edge : graph.getEdges())
        {
            result.connect(edge.second, edge.first);
        }
        return result;
    }

    void initialize()
    {
        // Kosaraju Sharir algorithm works on reversing directions and iterating vertices in topological order
        // and iterating that vertices using DFS on the original graph with orginial directions

        // This works because:
        // -> reversing the edges -> reverses the dependency of the vertices in the graph
        // -> traversing the vertices in topological order -> means that vertices in a connected component is traversed only once
        // -> this means contracting each strong component into a single vertex
        // and we can increment the id when one vertex finishes DFS (in the original graph)

        m_numberOfComponentIds = 0U;
        DirectedGraphWithListOfEdgesWithVertex graphWithReversedDirections(getGraphWithReversedDirections(m_graph));
        VertexOrderingUsingDfs<Vertex> vertexOrdering(graphWithReversedDirections);
        for(Vertex const& vertex : vertexOrdering.getVerticesInTopologicalOrder())
        {
            if(m_processedVertices.isNotFound(vertex))
            {
                traverseUsingDfs(vertex);
                m_numberOfComponentIds++;
            }
        }
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        m_vertexToComponentIdMap[vertex] = m_numberOfComponentIds;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseDirectedGraphWithVertex const& m_graph;
    unsigned int m_numberOfComponentIds;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToUnsignedIntMap m_vertexToComponentIdMap;
};

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


// Other analysis:
// The time complexity of the algorithm is O(n + m), because the algorithm performs two depth-first searches.
// Note: n is the number of nodes and m is the number of edges.

}

}