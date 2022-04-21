#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class CheckableVertices
{
public:
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;

    CheckableVertices()
    {}

    bool isFound(Vertex const& vertex) const
    {
        return m_vertices.find(vertex) != m_vertices.cend();
    }

    bool isNotFound(Vertex const& vertex) const
    {
        return m_vertices.find(vertex) == m_vertices.cend();
    }

    void putVertex(Vertex const& vertex)
    {
        m_vertices.emplace(vertex);
    }

    void removeVertex(Vertex const& vertex)
    {
        m_vertices.erase(vertex);
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
