#pragma once

#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class SubTreeQuery
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using Counts = std::vector<unsigned int>;

    SubTreeQuery(BaseUndirectedGraphWithVertex const& graph, Vertex const& rootOfTree)
        : m_graph(graph)
        , m_rootOfTree(rootOfTree)
    {
        initializeIfNeeded();
    }

    Vertices const& getVerticesInDfsPreOrder() const
    {
        return m_verticesInDfsPreOrder;
    }

    Counts const& getSubTreeSize() const
    {
        return m_subTreeSize;
    }

private:

    void initializeIfNeeded()
    {
        if(GraphUtilities::isATree(m_graph))
        {
            initialize();
        }
    }

    void initialize()
    {
        traverseStartingFromAVertex(m_rootOfTree);
    }

    void traverseStartingFromAVertex(Vertex const& startVertex)
    {
        if(m_processedVertices.isNotFound(startVertex) && !m_graph.getAdjacentVerticesAt(startVertex).empty()) // dont include invalid vertex
        {
            unsigned int treeSize(0);
            traverseUsingDfs(treeSize, startVertex);
        }
    }

    void traverseUsingDfs(unsigned int & treeSize, Vertex const& vertex)
    {
        treeSize++;
        m_verticesInDfsPreOrder.emplace_back(vertex);
        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traverseUsingDfs(treeSize, adjacentVertex);
            }
        }
        m_subTreeSize.emplace_back(vertex);
        treeSize--;

    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertex m_rootOfTree;
    Vertices m_verticesInDfsPreOrder;
    Counts m_subTreeSize;
    CheckableVerticesWithVertex m_processedVertices;
};

}

}
