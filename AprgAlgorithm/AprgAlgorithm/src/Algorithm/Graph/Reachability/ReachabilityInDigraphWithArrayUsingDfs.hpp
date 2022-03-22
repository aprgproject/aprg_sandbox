#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>

namespace alba
{
namespace algorithm
{

template<typename Vertex, unsigned int MAX_VERTEX_VALUE>
class ReachabilityInDigraphWithArrayUsingDfs
{
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using ArrayOfBool = std::array<bool, MAX_VERTEX_VALUE>;

    ReachabilityInDigraphWithArrayUsingDfs(BaseDirectedGraphWithVertex const& graph, Vertex const& sourceVertex)
        : m_graph(graph)
        , m_sourceVertex(sourceVertex)
        , m_isReachableArray{}    {
        initialize();
    }

    bool isReachable(Vertex const& destinationVertex) const
    {
        return m_isReachableArray.at(destinationVertex);
    }

private:

    bool isNotProcessed(Vertex const& vertex) const
    {
        return !m_isReachableArray.at(vertex);
    }

    void initialize()
    {
        // no clearing because array is brace initialized
        traverseUsingDfs(m_sourceVertex);
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_isReachableArray[vertex] = true;
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
    ArrayOfBool m_isReachableArray; // array for constant time query
};
}

}
