#pragma once

#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class LowestCommonAncestors
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using Depths = std::vector<unsigned int>;
    using VertexToIndexMap = std::map<Vertex, unsigned int>;

    LowestCommonAncestors(BaseUndirectedGraphWithVertex const& graph, Vertex const& rootOfTree)
        : m_graph(graph)
        , m_rootOfTree(rootOfTree)
    {
        initializeIfNeeded();
    }

    Vertices const& getVerticesInDfsPreOrder() const
    {
        return m_verticesInTreeOrder;
    }

    Depths const& getDepths() const
    {
        return m_depths;
    }

    Vertex getLowestCommonAnscestor(Vertex const& vertex1, Vertex const& vertex2) const
    {
        Vertex result{};
        auto it1 = m_vertexToIndexMap.find(vertex1);
        auto it2 = m_vertexToIndexMap.find(vertex2);
        if(it1!=m_vertexToIndexMap.cend() && it2!=m_vertexToIndexMap.cend())
        {
            unsigned int vertexIndex1 = it1->second;
            unsigned int vertexIndex2 = it2->second;
            unsigned int lowestCommonAnscestorIndex(getLowestCommonAnscestorIndex(vertexIndex1, vertexIndex2));
            result = m_verticesInTreeOrder.at(lowestCommonAnscestorIndex);
        }
        return result;
    }

    unsigned int getDistanceBetweenVertices(Vertex const& vertex1, Vertex const& vertex2) const
    {
        unsigned int result{};
        auto it1 = m_vertexToIndexMap.find(vertex1);
        auto it2 = m_vertexToIndexMap.find(vertex2);
        if(it1!=m_vertexToIndexMap.cend() && it2!=m_vertexToIndexMap.cend())
        {
            unsigned int vertexIndex1 = it1->second;
            unsigned int vertexIndex2 = it2->second;
            unsigned int lowestCommonAnscestorIndex(getLowestCommonAnscestorIndex(vertexIndex1, vertexIndex2));
            result = m_depths.at(vertexIndex1) + m_depths.at(vertexIndex2) - 2*m_depths.at(lowestCommonAnscestorIndex);
        }
        return result;
    }

protected:

    unsigned int getLowestCommonAnscestorIndex(unsigned int const vertexIndex1, unsigned int const vertexIndex2) const
    {
        unsigned int resultIndex = vertexIndex1;
        unsigned int minimumDepth(m_depths.at(vertexIndex1));
        for(unsigned int i=vertexIndex1+1; i<=vertexIndex2; i++)
        {
            unsigned int currentDepth(m_depths.at(i));
            if(minimumDepth > currentDepth)
            {
                minimumDepth = currentDepth;
                resultIndex = i;
            }
        }
        return resultIndex;
    }

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
            unsigned int index(0);
            unsigned int depth(0);
            traverseUsingDfs(index, depth, startVertex);

            m_verticesInTreeOrder.shrink_to_fit();
            m_depths.shrink_to_fit();
        }
    }

    void traverseUsingDfs(unsigned int & index, unsigned int & depth, Vertex const& vertex)
    {
        depth++;
        m_processedVertices.putVertex(vertex);
        m_vertexToIndexMap[vertex] = index;
        addVertex(index, depth, vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                traverseUsingDfs(index, depth, adjacentVertex);
                addVertex(index, depth, vertex); // add vertex for tree traversaval
            }
        }
        depth--;
    }

    void addVertex(unsigned int & index, unsigned int const depth, Vertex const& vertex)
    {
        m_verticesInTreeOrder.emplace_back(vertex);
        m_depths.emplace_back(depth);
        index++;
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertex m_rootOfTree;
    CheckableVerticesWithVertex m_processedVertices;
    Vertices m_verticesInTreeOrder;
    Depths m_depths;
    VertexToIndexMap m_vertexToIndexMap;
};

}

}
