#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/ProcessedVertices.hpp>
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
    using VertexToEdgeWithWeight = std::map<Vertex, EdgeWithWeight>;
    using ProcessedVerticesWithVertex = ProcessedVertices<Vertex>;

    PrimAlgorithmEagerVersion(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
    {
        searchForMinimumSpanningTree();
    }

    Edges getMinimumSpanningTreeEdges() const
    {
        Edges result;
        std::transform(m_vertexToEdgeWithMinimumWeight.cbegin(), m_vertexToEdgeWithMinimumWeight.cend(), std::back_inserter(result),
                       [](auto const& vertexToEdgeWithWeightPair)
        {
            return static_cast<Edge>(vertexToEdgeWithWeightPair.second);
        });
        return result;
    }

private:

    bool hasNoWeightSaved(Vertex const& vertex) const
    {
        return m_vertexToEdgeWithMinimumWeight.find(vertex) == m_vertexToEdgeWithMinimumWeight.cend();
    }

    void searchForMinimumSpanningTree()
    {
        m_verticesAdjacentToTreeOrderedByWeight.emplace(m_startVertex, Weight{}); // start vertex with weight zero for start
        while(!m_verticesAdjacentToTreeOrderedByWeight.empty())
        {
            auto nearestVertexIt(m_verticesAdjacentToTreeOrderedByWeight.cbegin());
            auto nearestVertex(*nearestVertexIt);
            m_verticesAdjacentToTreeOrderedByWeight.erase(nearestVertexIt);
            checkAdjacentVerticesWithLowestWeightOfVertex(nearestVertex.vertex);
        }
    }

    void checkAdjacentVerticesWithLowestWeightOfVertex(
            Vertex const& vertex)
    {
        m_processedVertices.putVertexAsProcessed(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(m_processedVertices.isNotProcessed(adjacentVertex))
            {
                Weight weightForAdjacentVertex(m_graph.getWeight(vertex, adjacentVertex));
                if(hasNoWeightSaved(adjacentVertex)
                        || weightForAdjacentVertex < m_vertexToEdgeWithMinimumWeight.at(adjacentVertex).weight)
                {
                    saveVertexAndEdgeOfLowestWeight(vertex, adjacentVertex, weightForAdjacentVertex);
                }
            }
        }
    }

    void saveVertexAndEdgeOfLowestWeight(
            Vertex const& vertex,
            Vertex const& adjacentVertex,
            Weight const& lowestWeight)
    {
        m_vertexToEdgeWithMinimumWeight[adjacentVertex]
                = createSortedEdgeWithWeight<Vertex, Weight, EdgeWithWeight>(vertex, adjacentVertex, lowestWeight);
        m_verticesAdjacentToTreeOrderedByWeight.emplace(adjacentVertex, lowestWeight);
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    ProcessedVerticesWithVertex m_processedVertices;
    VertexToEdgeWithWeight m_vertexToEdgeWithMinimumWeight;
    SetOfVerticesWithWeight m_verticesAdjacentToTreeOrderedByWeight;

};

}

}
