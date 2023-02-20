#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

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
    using VertexToVertexMap = typename GraphTypes<Vertex>::VertexToVertexMap;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    BasePathSearchWithBfsAndDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
    {}

    bool hasPathTo(Vertex const& endVertex) const
    {
        return m_processedVertices.isFound(endVertex);    }

    Path getPathTo(Vertex const& endVertex) const
    {        Path reversedPath;
        bool shouldAddCurrentVertexAndReverse(m_startVertices.isNotFound(endVertex));
        Vertex currentVertex = endVertex;
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
        Path result;
        if(shouldAddCurrentVertexAndReverse)
        {
            reversedPath.emplace_back(currentVertex);
            result.reserve(reversedPath.size());
            // Sedgewick uses stack for reversing but we use vector for Path
            std::copy(reversedPath.crbegin(), reversedPath.crend(), std::back_inserter(result));
        }
        return result;
    }

    Vertex getPreviousVertex(Vertex const& vertex) const
    {
        Vertex result{};
        auto it = m_vertexToPreviousVertexMap.find(vertex);
        if(it != m_vertexToPreviousVertexMap.cend())
        {
            result = it->second;
        }
        return result;
    }

    VertexToVertexMap const& getVertexToPreviousVertexMap() const
    {
        return m_vertexToPreviousVertexMap;
    }

protected:
    // No need for virtual destructor because this class is not destroyed polymorphically.
    // Guideline #4: A base class destructor should be either public and virtual, or protected and nonvirtual.
    // Source: http://www.gotw.ca/publications/mill18.htm
    ~BasePathSearchWithBfsAndDfs() = default;

    void clear()
    {        m_processedVertices.clear();
        m_startVertices.clear();
        m_vertexToPreviousVertexMap.clear();
    }
    void initializeWithStartVertices(Vertices const& startVertices)
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
