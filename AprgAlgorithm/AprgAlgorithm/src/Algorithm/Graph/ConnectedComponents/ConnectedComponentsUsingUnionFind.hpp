#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>
#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class ConnectedComponentsUsingUnionFind : public BaseConnectedComponents<Vertex>
{
public:
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Edge = typename GraphTypes<Vertex>::Edge;

    ConnectedComponentsUsingUnionFind(BaseGraphWithVertex const& graph)
        : m_graph(graph)
        , m_unionFind()
    {
        initialize();
    }

    bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const override
    {
        return m_unionFind.isConnected(vertex1, vertex2);
    }

private:
    void initialize()
    {
        for(Edge const& edge : m_graph.getEdges())
        {
            m_unionFind.connect(edge.first, edge.second);
        }
    }
    BaseGraphWithVertex const& m_graph;
    UnionFindUsingMap<Vertex> m_unionFind;
};

}

}
