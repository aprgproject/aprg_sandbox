#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/DepthFirstSearch.hpp>
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
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using VertexToBoolMap = typename GraphTypes<Vertex>::VertexToBoolMap;

    ConnectedComponentsUsingDfs(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {
        initialize();
    }

    bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const
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

private:
    void initialize()
    {
        Vertices vertices(m_graph.getVertices());
        for(Vertex const& vertex : vertices)
        {
            m_isProcessed[vertex] = false;
        }
        unsigned int componentId(0U);
        for(Vertex const& vertex : vertices)
        {
            if(!m_isProcessed.at(vertex))
            {
                DepthFirstSearch<Vertex> dfsAtVertex(m_graph, vertex);
                VertexToBoolMap const& isProcessedMap(dfsAtVertex.getIsProcessedMap());
                for(auto const& vertexAndIsProcessedPair : isProcessedMap)
                {
                    if(vertexAndIsProcessedPair.second)
                    {
                        m_vertexToComponentIdMap[vertexAndIsProcessedPair.first] = componentId;
                        m_isProcessed[vertexAndIsProcessedPair.first] = true;
                    }
                }
                componentId++;
            }
        }
    }
    BaseUndirectedGraphWithVertex const& m_graph;
    VertexToUnsignedIntMap m_vertexToComponentIdMap;
    VertexToBoolMap m_isProcessed;
};

}

}
