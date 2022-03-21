#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class BasePathSearch
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;

    BasePathSearch(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
    {}

    bool hasPathTo(Vertex const& endVertex) const
    {
        return m_processedVertices.find(endVertex) != m_processedVertices.cend();
    }

    Path getPathTo(Vertex const& endVertex) const    {
        bool isSuccessful(true);
        Vertex currentVertex = endVertex;
        Path reversedPath;
        while(currentVertex != m_startVertex)
        {
            reversedPath.emplace_back(currentVertex);
            auto it = m_vertexToPreviousVertexMap.find(currentVertex);
            if(it != m_vertexToPreviousVertexMap.cend())
            {
                currentVertex = it->second;
            }
            else
            {
                isSuccessful = false;
                break;
            }
        }
        Path result;
        if(isSuccessful)
        {
            reversedPath.emplace_back(m_startVertex);
            result.reserve(reversedPath.size());
            std::copy(reversedPath.crbegin(), reversedPath.crend(), std::back_inserter(result));
        }
        return result;
    }

    virtual void reinitializeStartingFrom(Vertex const& startVertex) = 0;

protected:
    bool isNotProcessed(Vertex const& vertex) const
    {
        return m_processedVertices.find(vertex) == m_processedVertices.cend();
    }

    void clear()
    {
        m_vertexToPreviousVertexMap.clear();
        m_processedVertices.clear();
    }

    BaseGraphWithVertex const& m_graph;
    Vertex m_startVertex;
    SetOfVertices m_processedVertices;
    VertexToVertexMap m_vertexToPreviousVertexMap;
};
}

}
