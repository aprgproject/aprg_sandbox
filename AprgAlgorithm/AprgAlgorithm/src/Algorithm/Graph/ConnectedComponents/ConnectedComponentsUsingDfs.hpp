#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class ConnectedComponentsUsingDfs : public BaseConnectedComponents<Vertex>
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;

    ConnectedComponentsUsingDfs(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
        , m_numberOfComponentIds(0U)
    {
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

    bool isNotProcessed(Vertex const& vertex) const
    {
        return m_processedVertices.find(vertex)== m_processedVertices.cend();
    }

    void initialize()
    {
        m_numberOfComponentIds = 0U;
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if(isNotProcessed(vertex))
            {
                traverseUsingDfs(vertex);
                m_numberOfComponentIds++;
            }
        }
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.emplace(vertex);
        m_vertexToComponentIdMap[vertex] = m_numberOfComponentIds;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(isNotProcessed(adjacentVertex))
            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    unsigned int m_numberOfComponentIds;
    SetOfVertices m_processedVertices;
    VertexToUnsignedIntMap m_vertexToComponentIdMap;
};

}

}
