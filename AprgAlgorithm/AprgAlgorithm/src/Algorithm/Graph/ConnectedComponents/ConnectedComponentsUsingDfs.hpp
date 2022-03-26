#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/Graph/Utilities/ProcessedVertices.hpp>

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
    using ProcessedVerticesWithVertex = ProcessedVertices<Vertex>;

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

    void initialize()
    {
        m_numberOfComponentIds = 0U;
        for(Vertex const& vertex : m_graph.getVertices())
        {
            if(m_processedVertices.isNotProcessed(vertex))
            {
                traverseUsingDfs(vertex);
                m_numberOfComponentIds++;
            }
        }
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertexAsProcessed(vertex);
        m_vertexToComponentIdMap[vertex] = m_numberOfComponentIds;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotProcessed(adjacentVertex))
            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    unsigned int m_numberOfComponentIds;
    ProcessedVerticesWithVertex m_processedVertices;
    VertexToUnsignedIntMap m_vertexToComponentIdMap;
};

}

}
