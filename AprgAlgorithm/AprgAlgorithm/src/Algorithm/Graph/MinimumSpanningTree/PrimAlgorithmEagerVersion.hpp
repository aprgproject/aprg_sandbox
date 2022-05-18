#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/CheckableVertices.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>

#include <algorithm>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class PrimAlgorithmEagerVersion
{
public:
    using Graph = EdgeWeightedGraph;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using SetOfVerticesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::SetOfVerticesWithWeight;
    using VertexToEdgeWithWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToEdgeWithWeightMap;
    using CheckableVerticesWithVertex = CheckableVertices<Vertex>;

    PrimAlgorithmEagerVersion(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
    {
        searchForMinimumSpanningTree();
    }

    Edges getMinimumSpanningTreeEdges() const
    {
        Edges result;
        result.reserve(m_vertexToEdgeWithMinimumWeightMap.size());
        std::transform(m_vertexToEdgeWithMinimumWeightMap.cbegin(), m_vertexToEdgeWithMinimumWeightMap.cend(), std::back_inserter(result),
                       [](auto const& vertexToEdgeWithWeightPair)
        {            return static_cast<Edge>(vertexToEdgeWithWeightPair.second);
        });
        return result;
    }
private:

    bool hasNoWeightSaved(Vertex const& vertex) const
    {
        return m_vertexToEdgeWithMinimumWeightMap.find(vertex) == m_vertexToEdgeWithMinimumWeightMap.cend();
    }

    void searchForMinimumSpanningTree()
    {
        m_verticesAdjacentToTreeOrderedByWeight.emplace(m_startVertex, Weight{}); // start vertex with weight zero for start
        while(!m_verticesAdjacentToTreeOrderedByWeight.empty())
        {
            // continue to grow the MST by processing the current nearest edge and only adding only edges with minimum weight
            auto nearestVertexIt(m_verticesAdjacentToTreeOrderedByWeight.cbegin());
            auto nearestVertex(*nearestVertexIt);
            m_verticesAdjacentToTreeOrderedByWeight.erase(nearestVertexIt);            checkAdjacentVerticesWithLowestWeightOfVertex(nearestVertex.vertex);
        }
    }

    void checkAdjacentVerticesWithLowestWeightOfVertex(
            Vertex const& vertex)
    {
        // DFS traversal
        m_processedVertices.putVertex(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotFound(adjacentVertex)) // only add vertices and edges from vertices not yet processed
            {
                Weight weightForAdjacentVertex(m_graph.getWeight(vertex, adjacentVertex));
                // check for vertex is not yet included or edge weight is smaller
                if(hasNoWeightSaved(adjacentVertex)
                        || weightForAdjacentVertex < m_vertexToEdgeWithMinimumWeightMap.at(adjacentVertex).weight)
                {                    saveVertexAndEdgeOfLowestWeight(vertex, adjacentVertex, weightForAdjacentVertex);
                }
            }
        }    }

    void saveVertexAndEdgeOfLowestWeight(
            Vertex const& vertex,
            Vertex const& adjacentVertex,
            Weight const& lowestWeight)
    {
        m_vertexToEdgeWithMinimumWeightMap[adjacentVertex]
                = createSortedEdgeWithWeight<Vertex, Weight, EdgeWithWeight>(vertex, adjacentVertex, lowestWeight);
        m_verticesAdjacentToTreeOrderedByWeight.emplace(adjacentVertex, lowestWeight);
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    CheckableVerticesWithVertex m_processedVertices;
    VertexToEdgeWithWeightMap m_vertexToEdgeWithMinimumWeightMap;
    SetOfVerticesWithWeight m_verticesAdjacentToTreeOrderedByWeight;

};

}

}
