#pragma once

#include <Algorithm/Graph/ConnectedComponents/BaseConnectedComponents.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class ConnectedComponentsUsingUnionFind : public BaseConnectedComponents<Vertex>
{
public:    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    ConnectedComponentsUsingUnionFind(BaseUndirectedGraphWithVertex const& graph)
        : m_graph(graph)
    {
        initialize();
    }

    bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const override
    {
        return m_unionFind.isConnected(vertex1, vertex2);
    }

    unsigned int getNumberOfComponentIds() const override
    {
        SetOfVertices uniqueRoots;
        for(Vertex const& vertex : m_graph.getVertices())
        {
            uniqueRoots.emplace(m_unionFind.getRoot(vertex));
        }
        return uniqueRoots.size();
    }

private:
    void initialize()
    {
        for(Edge const& edge : m_graph.getEdges())
        {
            m_unionFind.connect(edge.first, edge.second);
        }
    }
    BaseUndirectedGraphWithVertex const& m_graph;
    UnionFindUsingMap<Vertex> m_unionFind;
};

}

}
