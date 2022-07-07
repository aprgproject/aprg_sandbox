#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class ConnectedComponentsUsingDfs : public BaseConnectedComponents<Vertex>
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    ConnectedComponentsUsingDfs(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
        , m_numberOfComponentIds(0U)    {
        initialize();
    }

    bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const override
    {
        auto it1 = m_vertexToComponentIdMap.find(vertex1);
        auto it2 = m_vertexToComponentIdMap.find(vertex2);
        bool result(false);
        if(it1 != m_vertexToComponentIdMap.cend()
                && it2 != m_vertexToComponentIdMap.cend())
        {
            result = it1->second == it2->second;
        }
        return result;
    }

    unsigned int getNumberOfComponentIds() const override
    {
        return m_numberOfComponentIds;
    }

private:

    void initialize()
    {
        m_numberOfComponentIds = 0U;
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if(m_processedVertices.isNotFound(vertex))
            {
                traverseUsingDfs(vertex);
                m_numberOfComponentIds++;
            }
        }
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        m_vertexToComponentIdMap[vertex] = m_numberOfComponentIds;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    unsigned int m_numberOfComponentIds;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToUnsignedIntMap m_vertexToComponentIdMap;
};

}

}
