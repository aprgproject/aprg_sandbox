#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class BasePathSearchForDijkstraAndDag
{
public:
    using Graph = EdgeWeightedGraph;
    using Path = typename GraphTypes<Vertex>::Path;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using SetOfVerticesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::SetOfVerticesWithWeight;
    using VertexToEdgeWithWeight = std::map<Vertex, EdgeWithWeight>;

    BasePathSearchForDijkstraAndDag(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
    {}

    bool hasPathTo(Vertex const& endVertex) const
    {
        return m_vertexToEdgeWithLowestWeight.find(endVertex) != m_vertexToEdgeWithLowestWeight.cend();
    }

    Path getPathTo(Vertex const& endVertex) const
    {
        bool isSuccessful(true);
        Vertex currentVertex = endVertex;
        Path reversedPath;
        while(currentVertex != m_startVertex)
        {
            reversedPath.emplace_back(currentVertex);
            auto it = m_vertexToEdgeWithLowestWeight.find(currentVertex);
            if(it != m_vertexToEdgeWithLowestWeight.cend())
            {
                currentVertex = it->second.first;
            }
            else
            {
                isSuccessful = false;
                break;
            }
        }
        Path result;
        if(isSuccessful)
        {
            reversedPath.emplace_back(m_startVertex);
            result.reserve(reversedPath.size());
            std::copy(reversedPath.crbegin(), reversedPath.crend(), std::back_inserter(result));
        }
        return result;
    }

protected:

    bool hasNoWeightSaved(Vertex const& vertex) const
    {
        return m_vertexToEdgeWithLowestWeight.find(vertex) == m_vertexToEdgeWithLowestWeight.cend();
    }

    Weight getSavedWeightAt(Vertex const& vertex) const
    {
        Weight result{};
        auto it = m_vertexToEdgeWithLowestWeight.find(vertex);
        if(it != m_vertexToEdgeWithLowestWeight.cend())
        {
            result = it->second.weight;
        }
        return result;
    }

    void relaxAt(Vertex const& vertex)
    {
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            Weight weightOfCurrentEdge(m_graph.getWeight(vertex, adjacentVertex));
            Weight currentLowestWeightAtVertex(getSavedWeightAt(vertex));
            Weight currentWeightAtAdjacentVertex(getSavedWeightAt(adjacentVertex));
            if(hasNoWeightSaved(adjacentVertex)
                    || currentWeightAtAdjacentVertex > currentLowestWeightAtVertex + weightOfCurrentEdge)
            {
                Weight newLowestWeight(currentLowestWeightAtVertex + weightOfCurrentEdge);
                m_vertexToEdgeWithLowestWeight[adjacentVertex] = EdgeWithWeight(vertex, adjacentVertex, newLowestWeight);
                m_foundVerticesOrderedByWeight.emplace(adjacentVertex, newLowestWeight);
            }
        }
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    VertexToEdgeWithWeight m_vertexToEdgeWithLowestWeight;
    SetOfVerticesWithWeight m_foundVerticesOrderedByWeight;

};

}

}
