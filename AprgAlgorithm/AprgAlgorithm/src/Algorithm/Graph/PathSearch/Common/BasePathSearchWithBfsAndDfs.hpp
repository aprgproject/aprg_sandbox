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
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    BasePathSearchWithBfsAndDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    virtual ~BasePathSearchWithBfsAndDfs()
    {}

    bool hasPathTo(Vertex const& endVertex) const
    {
        return m_processedVertices.isFound(endVertex);
    }

    Path getPathTo(Vertex const& endVertex) const
    {
        Path result;
        if(m_startVertices.isNotFound(endVertex))
        {
            bool shouldAddCurrentVertexAndReverse(true);
            Vertex currentVertex = endVertex;
            Path reversedPath;
            while(m_startVertices.isNotFound(currentVertex))
            {
                reversedPath.emplace_back(currentVertex);
                auto it = m_vertexToPreviousVertexMap.find(currentVertex);
                if(it != m_vertexToPreviousVertexMap.cend())
                {
                    currentVertex = it->second;
                }
                else
                {
                    shouldAddCurrentVertexAndReverse = false;
                    break;
                }
            }
            if(shouldAddCurrentVertexAndReverse)
            {
                reversedPath.emplace_back(currentVertex);
                result.reserve(reversedPath.size());
                // Sedgewick uses stack for reversing but we use vector for Path
                std::copy(reversedPath.crbegin(), reversedPath.crend(), std::back_inserter(result));
            }
        }
        return result;
    }

    virtual void reinitializeStartingFrom(Vertices const& startVertices) = 0;

protected:

    void clear()
    {
        m_processedVertices.clear();
        m_startVertices.clear();
        m_vertexToPreviousVertexMap.clear();
    }

    void addStartVertices(Vertices const& startVertices)
    {
        m_startVertices.putVertices(startVertices);
    }

    BaseGraphWithVertex const& m_graph;
    CheckableVerticesWithVertex m_startVertices;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToVertexMap m_vertexToPreviousVertexMap;
};

}

}
