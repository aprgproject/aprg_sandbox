#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class ProcessedVertices
{
public:
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;

    ProcessedVertices()
    {}

    bool isProcessed(Vertex const& vertex) const
    {
        return m_vertices.find(vertex) != m_vertices.cend();
    }

    bool isNotProcessed(Vertex const& vertex) const
    {
        return m_vertices.find(vertex) == m_vertices.cend();
    }

    void putVertexAsProcessed(Vertex const& vertex)
    {
        m_vertices.emplace(vertex);
    }

    void clear()
    {
        m_vertices.clear();
    }

private:
    SetOfVertices m_vertices;
};

}

}
