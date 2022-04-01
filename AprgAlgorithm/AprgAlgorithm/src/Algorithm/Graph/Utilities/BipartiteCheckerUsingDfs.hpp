#pragma once

#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
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
        , m_hasTwoColors(true)
    {
        initialize();
    }

    bool isBipartite() const
    {
        return m_hasTwoColors;
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
            m_vertexToColorMap[vertex] = false;
        }
        for(Vertex const& vertex : vertices)
        {
            if(m_processedVertices.isNotFound(vertex))
            {
                checkUsingDfs(vertex);
            }
        }
    }

    void checkUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(!m_hasTwoColors)
            {
                break;
            }
            else if(m_processedVertices.isNotFound(adjacentVertex))
            {
                m_vertexToColorMap[adjacentVertex] = getTheOtherColor(m_vertexToColorMap.at(vertex));
                checkUsingDfs(adjacentVertex);
            }
            else if(areColorsEqualOnVertices(vertex, adjacentVertex))
            {
                m_hasTwoColors = false;
                break;
            }
        }
    }

    bool getTheOtherColor(bool const color)
    {
        return !color;
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    bool m_hasTwoColors;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToColorMap m_vertexToColorMap;
};

}

}
