#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparisonTemplateType>
class BasePathSearchWithRelax
{
public:
    using Graph = EdgeWeightedGraph;
    using ComparisonClass=ComparisonTemplateType<Weight>;
    using Path = typename GraphTypes<Vertex>::Path;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using VertexToEdgeWithWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToEdgeWithWeightMap;
    using AdditionalRelaxationStepsOnLowerWeight = std::function<void(Vertex const&, Vertex const&, Weight const&)>;
    using AdditionalRelaxationSteps = std::function<void(void)>;

    BasePathSearchWithRelax(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
    {}

    virtual ~BasePathSearchWithRelax()
    {}

    bool hasPathTo(Vertex const& endVertex) const
    {
        return m_vertexToEdgeWithUpdatedWeightMap.find(endVertex) != m_vertexToEdgeWithUpdatedWeightMap.cend();    }

    Path getPathTo(Vertex const& endVertex) const
    {        bool shouldAddStartVertexAndReverse(endVertex != m_startVertex);
        Vertex currentVertex = endVertex;
        Path reversedPath;
        while(currentVertex != m_startVertex)
        {
            reversedPath.emplace_back(currentVertex);
            auto it = m_vertexToEdgeWithUpdatedWeightMap.find(currentVertex);
            if(it != m_vertexToEdgeWithUpdatedWeightMap.cend())
            {
                currentVertex = it->second.first;
            }
            else
            {
                shouldAddStartVertexAndReverse = false;
                break;
            }
        }
        Path result;
        if(shouldAddStartVertexAndReverse)
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
        return m_vertexToEdgeWithUpdatedWeightMap.find(vertex) == m_vertexToEdgeWithUpdatedWeightMap.cend();
    }

    Weight getSavedWeightAt(Vertex const& vertex) const
    {
        Weight result{};
        auto it = m_vertexToEdgeWithUpdatedWeightMap.find(vertex);
        if(it != m_vertexToEdgeWithUpdatedWeightMap.cend())
        {
            result = it->second.weight;
        }
        return result;
    }

    void setStartVertexWeightToZero()
    {
        m_vertexToEdgeWithUpdatedWeightMap[m_startVertex] = EdgeWithWeight(m_startVertex, m_startVertex, Weight{});
    }

    void relaxAt(
            Vertex const& vertex,
            AdditionalRelaxationStepsOnLowerWeight const& additionalRelaxationStepsOnLowerWeight = getNoStepsOnLowerWeight(),
            AdditionalRelaxationSteps const& additionalRelaxationSteps = getNoSteps())
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
                m_vertexToEdgeWithUpdatedWeightMap[adjacentVertex] = EdgeWithWeight(vertex, adjacentVertex, newWeight);
                additionalRelaxationStepsOnLowerWeight(vertex, adjacentVertex, newWeight);
            }
        }
        additionalRelaxationSteps();
    }

    static AdditionalRelaxationStepsOnLowerWeight getNoStepsOnLowerWeight()
    {
        static AdditionalRelaxationStepsOnLowerWeight noRelaxationSteps
                = [](Vertex const&, Vertex const&, Weight const&){};
        return noRelaxationSteps;
    }

    static AdditionalRelaxationSteps getNoSteps()
    {
        static AdditionalRelaxationSteps noRelaxationSteps = [](){};
        return noRelaxationSteps;
    }

    Graph const& m_graph;
    Vertex m_startVertex;
    ComparisonClass m_comparisonObject;
    VertexToEdgeWithWeightMap m_vertexToEdgeWithUpdatedWeightMap;
};

}

}
