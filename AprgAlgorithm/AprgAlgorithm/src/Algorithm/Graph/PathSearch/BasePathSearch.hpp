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
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using VertexToBoolMap = typename GraphTypes<Vertex>::VertexToBoolMap;

    BasePathSearch(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
        , m_vertexToPreviousVertexMap()
        , m_isProcessed()
    {}

    bool hasPathTo(Vertex const& endVertex) const
    {
        bool result(false);
        auto it = m_isProcessed.find(endVertex);
        if(it != m_isProcessed.cend())
        {
            result = it->second;
        }
        return result;
    }

    Path getPathTo(Vertex const& endVertex) const
    {
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

    VertexToBoolMap const& getIsProcessedMap()
    {
        return m_isProcessed;
    }

    virtual void reinitializeStartingFrom(Vertex const& startVertex) = 0;

protected:
    void clear()
    {
        m_vertexToPreviousVertexMap.clear();
        Vertices vertices(m_graph.getVertices());
        for(Vertex const& vertex : vertices)
        {
            m_isProcessed[vertex] = false;
        }
    }

    BaseGraphWithVertex const& m_graph;
    Vertex m_startVertex;
    VertexToVertexMap m_vertexToPreviousVertexMap;
    VertexToBoolMap m_isProcessed;
};

}

}
