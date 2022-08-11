#pragma once

#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/GraphUtilitiesHeaders.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class SubTreeQueryWithPathAccumulator
{
public:
    using BaseUndirectedGraphWithVertex = BaseUndirectedGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;
    using Counts = std::vector<unsigned int>;
    using VertexToIndexMap = std::map<Vertex, unsigned int>;
    using AccumulatorFunction = std::function<Vertex(Vertex const&, Vertex const&)>;

    SubTreeQueryWithPathAccumulator(
            BaseUndirectedGraphWithVertex const& graph,
            Vertex const& rootOfTree,
            AccumulatorFunction const& accumulator)
        : m_graph(graph)
        , m_rootOfTree(rootOfTree)
        , m_accumulator(accumulator)
    {
        initializeIfNeeded();
    }

    Vertices const& getVerticesInDfsPreOrder() const
    {
        return m_verticesInDfsPreOrder;
    }

    Vertices const& getPathResults() const
    {
        return m_pathResults;
    }

    Vertex getPathResult(Vertex const& vertex)
    {
        Vertex result;
        auto it = m_vertexToIndexMap.find(vertex);
        if(it!=m_vertexToIndexMap.cend())
        {
            result = m_pathResults.at(it->second);
        }
        return result;
    }

protected:

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
            Vertex pathResult(startVertex);
            traverseUsingDfs(treeSize, pathResult, startVertex);

            m_verticesInDfsPreOrder.shrink_to_fit();
            m_pathResults.shrink_to_fit();
        }
    }

    void traverseUsingDfs(unsigned int & treeSize, Vertex & pathResult, Vertex const& vertex)
    {
        m_processedVertices.putVertex(vertex);
        m_verticesInDfsPreOrder.emplace_back(vertex);
        m_pathResults.emplace_back(pathResult);
        Vertex pathResultAtVertex = pathResult;
        unsigned int index = treeSize++;
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex))
            {
                pathResult = m_accumulator(pathResultAtVertex, adjacentVertex);
                traverseUsingDfs(treeSize, pathResult, adjacentVertex);
            }
        }
        m_vertexToIndexMap[vertex] = index;
    }

    BaseUndirectedGraphWithVertex const& m_graph;
    Vertex m_rootOfTree;
    AccumulatorFunction m_accumulator;
    CheckableVerticesWithVertex m_processedVertices;
    Vertices m_verticesInDfsPreOrder;
    Vertices m_pathResults;
    VertexToIndexMap m_vertexToIndexMap;
};

}

}
