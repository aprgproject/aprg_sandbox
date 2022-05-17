#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BasePathSearchWithBfsAndDfs
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Path = typename GraphTypes<Vertex>::Path;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    BasePathSearchWithBfsAndDfs(BaseGraphWithVertex const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
    {}

    virtual ~BasePathSearchWithBfsAndDfs()
    {}

    bool hasPathTo(Vertex const& endVertex) const
    {
        return m_processedVertices.isFound(endVertex);
    }

    Path getPathTo(Vertex const& endVertex) const
    {
        bool shouldAddStartVertexAndReverse(endVertex != m_startVertex);
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
                shouldAddStartVertexAndReverse = false;
                break;
            }
        }
        Path result;
        if(shouldAddStartVertexAndReverse)
        {
            reversedPath.emplace_back(m_startVertex);
            result.reserve(reversedPath.size());
            // Sedgewick uses stack for reversing but we use vector for Path
            std::copy(reversedPath.crbegin(), reversedPath.crend(), std::back_inserter(result));
        }
        return result;    }

    virtual void reinitializeStartingFrom(Vertex const& startVertex) = 0;
protected:

    void clear()
    {
        m_vertexToPreviousVertexMap.clear();
        m_processedVertices.clear();
    }

    BaseGraphWithVertex const& m_graph;
    Vertex m_startVertex;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToVertexMap m_vertexToPreviousVertexMap;
};

}

}
