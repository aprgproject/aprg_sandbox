#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BipartiteCheckerUsingDfs
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Path = typename GraphTypes<Vertex>::Path;
    using VertexToColorMap = std::map<Vertex, bool>;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    BipartiteCheckerUsingDfs(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
        , m_isBipartite(true)
    {
        initialize();
    }

    bool isBipartite() const
    {
        return m_isBipartite;
    }

private:

    bool areColorsEqualOnVertices(Vertex const& vertex1, Vertex const& vertex2) const
    {
        bool result(false);
        auto it1 = m_vertexToColorMap.find(vertex1);
        auto it2 = m_vertexToColorMap.find(vertex2);
        if(it1 != m_vertexToColorMap.cend() && it2 != m_vertexToColorMap.cend())
        {
            result = it1->second == it2->second;
        }
        return result;
    }

    void initialize()
    {
        Vertices vertices(m_graph.getVertices());
        for(Vertex const& vertex : vertices)
        {
            m_vertexToColorMap[vertex] = false; // set all colors to one color
        }
        for(Vertex const& vertex : vertices)
        {
            if(m_processedVertices.isNotFound(vertex))
            {
                checkUsingDfs(vertex);
                if(!m_isBipartite) // if not bipartite, stop (no use continuing on it)
                {
                    break;
                }
            }
        }
    }

    void checkUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        Vertex vertexColor(m_vertexToColorMap.at(vertex));
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                m_vertexToColorMap[adjacentVertex] = getTheOtherColor(vertexColor); // assign the other color for unprocessed adjacent vertices
                checkUsingDfs(adjacentVertex);
            }
            else if(vertexColor == m_vertexToColorMap.at(adjacentVertex))
            {
                m_isBipartite = false; // two adjacent vertices can't be in the same color to be bipartite (colors needs to be alternating)
                break;
            }
        }
    }

    bool getTheOtherColor(bool const color)
    {
        return !color;
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    bool m_isBipartite;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToColorMap m_vertexToColorMap;
};

}

}
