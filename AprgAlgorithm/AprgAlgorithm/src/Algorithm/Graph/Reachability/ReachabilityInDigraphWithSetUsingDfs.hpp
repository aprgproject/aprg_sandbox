#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>

namespace alba
{
namespace algorithm
{

template<typename Vertex>
class ReachabilityInDigraphWithSetUsingDfs
{
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;

    ReachabilityInDigraphWithSetUsingDfs(BaseDirectedGraphWithVertex const& graph, Vertex const& sourceVertex)
        : m_graph(graph)
        , m_sourceVertex(sourceVertex)
    {        initialize();
    }

    bool isReachable(Vertex const& destinationVertex) const
    {
        return m_processedVertices.find(destinationVertex) != m_processedVertices.cend();
    }

private:

    bool isNotProcessed(Vertex const& vertex) const
    {
        return m_processedVertices.find(vertex) == m_processedVertices.cend();
    }

    void initialize()
    {
        traverseUsingDfs(m_sourceVertex);
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.emplace(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(isNotProcessed(adjacentVertex))
            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseDirectedGraphWithVertex const& m_graph;
    Vertex m_sourceVertex;
    SetOfVertices m_processedVertices;
};
}

}
