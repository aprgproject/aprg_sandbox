#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparisonTemplateType>
class BasePathSearchForDijkstraAndDag
{
public:
    using Graph = EdgeWeightedGraph;
    using ComparisonClass=ComparisonTemplateType<Weight>;
    using Path = typename GraphTypes<Vertex>::Path;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using VertexToEdgeWithWeight = std::map<Vertex, EdgeWithWeight>;
    using AdditionalRelaxationSteps = std::function<void(Vertex const&, Vertex const&, Weight const&)>;

    BasePathSearchForDijkstraAndDag(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
    {}

    bool hasPathTo(Vertex const& endVertex) const
    {
        return m_vertexToEdgeWithUpdatedWeight.find(endVertex) != m_vertexToEdgeWithUpdatedWeight.cend();
    }

    Path getPathTo(Vertex const& endVertex) const
    {
        bool shouldReverse(endVertex != m_startVertex);
        Vertex currentVertex = endVertex;
        Path reversedPath;
        while(currentVertex != m_startVertex)
        {
            reversedPath.emplace_back(currentVertex);
            auto it = m_vertexToEdgeWithUpdatedWeight.find(currentVertex);
            if(it != m_vertexToEdgeWithUpdatedWeight.cend())
            {
                currentVertex = it->second.first;
            }
            else
            {
                shouldReverse = false;
                break;
            }
        }
        Path result;
        if(shouldReverse)
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
        return m_vertexToEdgeWithUpdatedWeight.find(vertex) == m_vertexToEdgeWithUpdatedWeight.cend();
    }

    Weight getSavedWeightAt(Vertex const& vertex) const
    {
        Weight result{};
        auto it = m_vertexToEdgeWithUpdatedWeight.find(vertex);
        if(it != m_vertexToEdgeWithUpdatedWeight.cend())
        {
            result = it->second.weight;
        }
        return result;
    }

    static AdditionalRelaxationSteps getNoRelaxationSteps()
    {
        static AdditionalRelaxationSteps noRelaxationSteps = [](Vertex const&, Vertex const&, Weight const&){};
        return noRelaxationSteps;
    }

    void setStartVertexWeightToZero()
    {
        m_vertexToEdgeWithUpdatedWeight[m_startVertex] = EdgeWithWeight(m_startVertex, m_startVertex, Weight{});
    }

    void relaxAt(
            Vertex const& vertex,
            AdditionalRelaxationSteps const& additionalRelaxationSteps = getNoRelaxationSteps())
    {
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            Weight weightOfCurrentEdge(m_graph.getWeight(vertex, adjacentVertex));
            Weight currentLowestWeightAtVertex(getSavedWeightAt(vertex));
            Weight currentWeightAtAdjacentVertex(getSavedWeightAt(adjacentVertex));
            if(hasNoWeightSaved(adjacentVertex)
                    || m_comparisonObject(currentLowestWeightAtVertex + weightOfCurrentEdge, currentWeightAtAdjacentVertex))
            {
                Weight newWeight(currentLowestWeightAtVertex + weightOfCurrentEdge);
                m_vertexToEdgeWithUpdatedWeight[adjacentVertex] = EdgeWithWeight(vertex, adjacentVertex, newWeight);
                additionalRelaxationSteps(vertex, adjacentVertex, newWeight);
            }
        }
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    ComparisonClass m_comparisonObject;
    VertexToEdgeWithWeight m_vertexToEdgeWithUpdatedWeight;
};

}

}
