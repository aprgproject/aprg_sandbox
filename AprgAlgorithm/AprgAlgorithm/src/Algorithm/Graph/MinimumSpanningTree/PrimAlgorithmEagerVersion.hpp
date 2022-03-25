#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

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
    using SetOfVertices = typename GraphTypes<Vertex>::SetOfVertices;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using Edges = typename GraphTypes<Vertex>::Edges;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using VertexWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::VertexWithWeight;
    using SetOfVerticesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::SetOfVerticesWithWeight;
    using VertexToEdgeWithWeight = std::map<Vertex, EdgeWithWeight>;

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

    bool isNotProcessed(Vertex const& vertex) const
    {
        return m_processedVertices.find(vertex) == m_processedVertices.cend();
    }

    bool hasNoWeightSaved(Vertex const& vertex) const
    {
        return m_vertexToEdgeWithMinimumWeight.find(vertex) == m_vertexToEdgeWithMinimumWeight.cend();
    }

    EdgeWithWeight createSortedEdgeWithWeight(Vertex const& vertex1, Vertex const& vertex2, Weight const& weight) const
    {
        if(vertex1 <= vertex2)
        {
            return EdgeWithWeight(vertex1, vertex2, weight);
        }
        else
        {
            return EdgeWithWeight(vertex2, vertex1, weight);
        }
    }

    void searchForMinimumSpanningTree()
    {
        m_verticesAdjacentToTree.emplace(m_startVertex, Weight{}); // start vertex with weight zero for start
        while(!m_verticesAdjacentToTree.empty())
        {
            auto nearestVertexIt(m_verticesAdjacentToTree.cbegin());
            auto nearestVertex(*nearestVertexIt);
            m_verticesAdjacentToTree.erase(nearestVertexIt);
            searchTheAdjacentVerticesAt(nearestVertex.vertex);
        }
    }

    void searchTheAdjacentVerticesAt(Vertex const& vertex)
    {
        m_processedVertices.emplace(vertex);
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            if(isNotProcessed(adjacentVertex))
            {
                Weight weightForAdjacentVertex(m_graph.getWeight(vertex, adjacentVertex));
                if(hasNoWeightSaved(adjacentVertex)
                        || weightForAdjacentVertex < m_vertexToEdgeWithMinimumWeight.at(adjacentVertex).weight)
                {
                    m_vertexToEdgeWithMinimumWeight[adjacentVertex] = createSortedEdgeWithWeight(vertex, adjacentVertex, weightForAdjacentVertex);
                    m_verticesAdjacentToTree.emplace(adjacentVertex, weightForAdjacentVertex);
                }
            }
        }

    }

    Graph const& m_graph;
    Vertex m_startVertex;
    SetOfVertices m_processedVertices;
    VertexToEdgeWithWeight m_vertexToEdgeWithMinimumWeight;
    SetOfVerticesWithWeight m_verticesAdjacentToTree;

};

}

}
