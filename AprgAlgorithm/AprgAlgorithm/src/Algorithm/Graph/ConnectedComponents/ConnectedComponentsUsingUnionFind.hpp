#pragma once

#include <Algorithm/Graph/ConnectedComponents/Common/BaseConnectedComponentsWithVertexToComponentIdMap.hpp>
#include <Algorithm/Graph/UndirectedGraph/BaseUndirectedGraph.hpp>
#include <Algorithm/UnionFind/UnionFindUsingMap.hpp>
namespace alba
{
namespace algorithm
{

template <typename Vertex>
class ConnectedComponentsUsingUnionFind : public BaseConnectedComponentsWithVertexToComponentIdMap<Vertex, BaseUndirectedGraph<Vertex>>
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using BaseClass = BaseConnectedComponentsWithVertexToComponentIdMap<Vertex, BaseUndirectedGraphWithVertex>;
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using VertexToUnsignedIntMap = typename GraphTypes<Vertex>::VertexToUnsignedIntMap;
    using UnionFind = UnionFindUsingMap<Vertex>;

    ConnectedComponentsUsingUnionFind(BaseUndirectedGraphWithVertex const& graph)
        : BaseClass(graph)
        , m_graph(BaseClass::m_graph)
        , m_numberOfComponentIds(BaseClass::m_numberOfComponentIds)
        , m_vertexToComponentIdMap(BaseClass::m_vertexToComponentIdMap)
    {
        initialize();
    }

private:
    void initialize()
    {
        UnionFind unionFind;
        for(Edge const& edge : m_graph.getEdges())
        {
            unionFind.connect(edge.first, edge.second);
        }
        SetOfVertices roots;
        for(Vertex const& vertex : m_graph.getVertices())
        {
            unsigned int componentId{};
            Vertex root(unionFind.getRoot(vertex));
            auto it=roots.find(root);
            if(it != roots.cend())
            {
                componentId = std::distance(roots.cbegin(), it);
            }
            else
            {
                componentId = roots.size();
                roots.emplace(root);
            }
            m_vertexToComponentIdMap[vertex] = componentId+1;
        }
        m_numberOfComponentIds = roots.size();
    }
    BaseUndirectedGraphWithVertex const& m_graph;
    unsigned int & m_numberOfComponentIds;
    VertexToUnsignedIntMap & m_vertexToComponentIdMap;
};

}
}