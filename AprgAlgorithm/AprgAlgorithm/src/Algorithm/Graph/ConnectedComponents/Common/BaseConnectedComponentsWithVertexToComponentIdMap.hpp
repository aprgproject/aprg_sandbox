#pragma once

#include <Algorithm/Graph/ConnectedComponents/Common/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Graph>
class BaseConnectedComponentsWithVertexToComponentIdMap : public BaseConnectedComponents<Vertex>
{
public:
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;

    BaseConnectedComponentsWithVertexToComponentIdMap(Graph const& graph)
        : m_graph(graph)
        , m_numberOfComponentIds(0U)
    {}

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

    unsigned int getComponentId(Vertex const& vertex) const override
    {
        unsigned int result(0);
        auto it = m_vertexToComponentIdMap.find(vertex);
        if(it != m_vertexToComponentIdMap.cend())
        {
            result = it->second;
        }
        return result;
    }

protected:
    Graph const& m_graph;
    unsigned int m_numberOfComponentIds;
    VertexToUnsignedIntMap m_vertexToComponentIdMap;
};

}

}
