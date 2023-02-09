#pragma once

#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilities.hpp>

namespace alba
{
namespace algorithm
{
template <typename Vertex>
class ChildrenInTree
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using ParentVertexToChildren = std::map<Vertex, Vertices>;

    ChildrenInTree(BaseUndirectedGraphWithVertex const& graph, Vertex const& rootOfTree)
        : m_graph(graph)
        , m_rootOfTree(rootOfTree)
    {
        initializeIfNeeded();
    }

    Vertices getChildren(Vertex const& parent) const
    {
        Vertices result;
        auto it = m_parentVertexToChildren.find(parent);
        if(it!=m_parentVertexToChildren.cend())
        {
            result = it->second;
        }
        return result;
    }

private:
    void initializeIfNeeded()
    {
        if(GraphUtilities::isATree(m_graph))        {
            initialize();
        }
    }

    void initialize()
    {
        traverseUsingDfs(m_rootOfTree);
    }

    void traverseUsingDfs(Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                m_parentVertexToChildren[vertex].emplace_back(adjacentVertex);
                traverseUsingDfs(adjacentVertex);
            }
        }
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertex m_rootOfTree;
    CheckableVerticesWithVertex m_processedVertices;
    ParentVertexToChildren m_parentVertexToChildren;
};

}

}
