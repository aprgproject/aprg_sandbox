#pragma once

#include <Algorithm/Graph/ConnectedComponents/Common/BaseConnectedComponentsWithVertexToComponentIdMap.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

#include <map>
namespace alba
{
namespace algorithm
{

template <typename Vertex>
class ConnectedComponentsUsingDfs : public BaseConnectedComponentsWithVertexToComponentIdMap<Vertex, BaseUndirectedGraph<Vertex>>
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using BaseClass = BaseConnectedComponentsWithVertexToComponentIdMap<Vertex, BaseUndirectedGraphWithVertex>;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    ConnectedComponentsUsingDfs(BaseUndirectedGraphWithVertex const& graph)
        : BaseClass(graph)
        , m_graph(BaseClass::m_graph)
        , m_numberOfComponentIds(BaseClass::m_numberOfComponentIds)
        , m_vertexToComponentIdMap(BaseClass::m_vertexToComponentIdMap)
    {
        initialize();
    }

private:

    void initialize()    {
        m_numberOfComponentIds = 0U;
        for(Vertex const& vertex : m_graph.getVertices())
        {            if(m_processedVertices.isNotFound(vertex))
            {
                traverseUsingDfs(vertex);
                m_numberOfComponentIds++;
            }
        }
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        m_vertexToComponentIdMap[vertex] = m_numberOfComponentIds+1;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }
    BaseUndirectedGraphWithVertex const& m_graph;
    unsigned int & m_numberOfComponentIds;
    VertexToUnsignedIntMap & m_vertexToComponentIdMap;
    CheckableVerticesWithVertex m_processedVertices;
};

}
}