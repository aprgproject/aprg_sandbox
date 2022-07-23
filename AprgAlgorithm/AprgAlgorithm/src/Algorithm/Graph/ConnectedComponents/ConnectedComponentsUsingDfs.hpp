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
        , b_graph(BaseClass::m_graph)
        , b_numberOfComponentIds(BaseClass::m_numberOfComponentIds)
        , b_vertexToComponentIdMap(BaseClass::m_vertexToComponentIdMap)
    {
        initialize();
    }

private:

    void initialize()
    {
        b_numberOfComponentIds = 0U;
        for(Vertex const& vertex : b_graph.getVertices())
        {
            if(m_processedVertices.isNotFound(vertex))
            {
                traverseUsingDfs(vertex);
                b_numberOfComponentIds++;
            }
        }
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        b_vertexToComponentIdMap[vertex] = b_numberOfComponentIds+1;
        for(Vertex const& adjacentVertex : b_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traverseUsingDfs(adjacentVertex);
            }
        }
    }
    BaseUndirectedGraphWithVertex const& b_graph;
    unsigned int & b_numberOfComponentIds;
    VertexToUnsignedIntMap & b_vertexToComponentIdMap;
    CheckableVerticesWithVertex m_processedVertices;
};

}

}
