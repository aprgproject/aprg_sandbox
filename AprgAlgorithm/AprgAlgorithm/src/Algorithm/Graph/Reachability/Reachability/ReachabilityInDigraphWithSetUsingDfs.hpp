#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/Reachability/Reachability/BaseReachabilityInDigraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class ReachabilityInDigraphWithSetUsingDfs : public BaseReachabilityInDigraph<Vertex>
{
public:    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    ReachabilityInDigraphWithSetUsingDfs(BaseDirectedGraphWithVertex const& graph, Vertex const& sourceVertex)
        : m_graph(graph)
        , m_sourceVertex(sourceVertex)
    {
        initialize();
    }

    bool isReachable(Vertex const& destinationVertex) const override
    {
        return m_processedVertices.isFound(destinationVertex);
    }

private:

    void initialize()
    {
        traverseUsingDfs(m_sourceVertex);
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseDirectedGraphWithVertex const& m_graph;
    Vertex m_sourceVertex;
    CheckableVerticesWithVertex m_processedVertices;
};

}

}
