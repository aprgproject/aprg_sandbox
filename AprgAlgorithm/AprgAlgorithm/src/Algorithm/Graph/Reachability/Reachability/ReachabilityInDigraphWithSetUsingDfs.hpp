#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/Reachability/Reachability/BaseReachabilityInDigraph.hpp>
#include <Algorithm/Graph/Utilities/ProcessedVertices.hpp>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class ReachabilityInDigraphWithSetUsingDfs : public BaseReachabilityInDigraph<Vertex>
{
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using ProcessedVerticesWithVertex = ProcessedVertices<Vertex>;

    ReachabilityInDigraphWithSetUsingDfs(BaseDirectedGraphWithVertex const& graph, Vertex const& sourceVertex)
        : m_graph(graph)
        , m_sourceVertex(sourceVertex)
    {
        initialize();
    }

    bool isReachable(Vertex const& destinationVertex) const override
    {
        return m_processedVertices.isProcessed(destinationVertex);
    }

private:

    void initialize()
    {
        traverseUsingDfs(m_sourceVertex);
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertexAsProcessed(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotProcessed(adjacentVertex))
            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseDirectedGraphWithVertex const& m_graph;
    Vertex m_sourceVertex;
    ProcessedVerticesWithVertex m_processedVertices;
};

}

}
