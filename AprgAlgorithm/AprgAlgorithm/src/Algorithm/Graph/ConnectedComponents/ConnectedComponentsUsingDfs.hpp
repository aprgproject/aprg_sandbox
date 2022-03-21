#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class ConnectedComponentsUsingDfs : public BaseConnectedComponents<Vertex>
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using VertexToBoolMap = typename GraphTypes<Vertex>::VertexToBoolMap;

    ConnectedComponentsUsingDfs(BaseGraphWithVertex const& graph)
        : m_graph(graph)
        , m_isProcessedMap()
        , m_vertexToComponentIdMap()
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

private:
    void initialize()
    {
        Vertices vertices(m_graph.getVertices());
        for(Vertex const& vertex : vertices)
        {
            m_isProcessedMap[vertex] = false;
        }
        unsigned int componentId(0U);
        for(Vertex const& vertex : vertices)
        {
            if(!m_isProcessedMap.at(vertex))
            {
                PathSearchUsingDfs<Vertex> dfsAtVertex(m_graph, vertex);
                VertexToBoolMap const& isProcessedMap(dfsAtVertex.getIsProcessedMap());
                for(auto const& vertexAndIsProcessedPair : isProcessedMap)
                {
                    if(vertexAndIsProcessedPair.second)
                    {
                        m_vertexToComponentIdMap[vertexAndIsProcessedPair.first] = componentId;
                        m_isProcessedMap[vertexAndIsProcessedPair.first] = true;
                    }
                }
                componentId++;
            }
        }
    }
    BaseGraphWithVertex const& m_graph;
    VertexToBoolMap m_isProcessedMap;
    VertexToUnsignedIntMap m_vertexToComponentIdMap;
};

}

}
