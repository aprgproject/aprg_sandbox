#pragma once

#include <Algorithm/Graph/DirectedGraph/BaseDirectedGraph.hpp>
#include <Algorithm/Graph/Reachability/ReachabilityInDigraphWithSetUsingDfs.hpp>

#include <map>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class TransitiveClosureWithMap
{
public:
    using BaseDirectedGraphWithVertex = BaseDirectedGraph<Vertex>;
    using VertexToReachabilityMap = typename std::map<Vertex, ReachabilityInDigraphWithSetUsingDfs<Vertex>>;

    TransitiveClosureWithMap(BaseDirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {
        initialize();
    }

    bool isReachable(Vertex const& sourceVertex, Vertex const& destinationVertex) const
    {
        bool result(false);
        auto it = m_vertexToReachabilityMap.find(sourceVertex);
        if(it != m_vertexToReachabilityMap.cend())
        {
            result = it->second.isReachable(destinationVertex);
        }
        return result;
    }

private:

    void initialize()
    {
        for(Vertex const& vertex : m_graph.getVertices())
        {
            m_vertexToReachabilityMap.emplace(vertex, ReachabilityInDigraphWithSetUsingDfs<Vertex>(m_graph, vertex));
        }
    }

    BaseDirectedGraphWithVertex const& m_graph;
    VertexToReachabilityMap m_vertexToReachabilityMap;
};

}

}
