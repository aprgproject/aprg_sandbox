#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/DirectedGraph/DirectedGraphWithListOfEdges.hpp>
#include <Algorithm/Graph/Utilities/ProcessedVertices.hpp>
#include <Algorithm/Graph/VertexOrdering/VertexOrderingUsingDfs.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class StronglyConnectedComponentsUsingKosarajuSharir : public BaseConnectedComponents<Vertex>
{
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using DirectedGraphWithListOfEdgesWithVertex = DirectedGraphWithListOfEdges<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using ProcessedVerticesWithVertex = ProcessedVertices<Vertex>;

    StronglyConnectedComponentsUsingKosarajuSharir(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
        , m_numberOfComponentIds(0U)
    {
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

    DirectedGraphWithListOfEdgesWithVertex getReversedGraph(BaseDirectedGraphWithVertex const& graph) const
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

        m_numberOfComponentIds = 0U;
        DirectedGraphWithListOfEdgesWithVertex reversedGraph(getReversedGraph(m_graph));
        VertexOrderingUsingDfs<Vertex> vertexOrdering(reversedGraph);
        for(Vertex const& vertex : vertexOrdering.getVerticesInTopologicalOrder())
        {
            if(m_processedVertices.isNotProcessed(vertex))
            {                traverseUsingDfs(vertex);
                m_numberOfComponentIds++;
            }
        }    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertexAsProcessed(vertex);
        m_vertexToComponentIdMap[vertex] = m_numberOfComponentIds;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotProcessed(adjacentVertex))
            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseDirectedGraphWithVertex const& m_graph;
    unsigned int m_numberOfComponentIds;
    ProcessedVerticesWithVertex m_processedVertices;
    VertexToUnsignedIntMap m_vertexToComponentIdMap;
};

}

}
