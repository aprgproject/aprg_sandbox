#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph, template<class> class ComparatorTemplateType>
class BasePathSearchWithRelax
{
public:
    using Graph = EdgeWeightedGraph;
    using Comparator=ComparatorTemplateType<Weight>;
    using Path = typename GraphTypes<Vertex>::Path;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using VertexToEdgeWithWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToEdgeWithWeightMap;
    using AdditionalRelaxationStepsWithNewWeight = std::function<void(Vertex const&, Vertex const&, Weight const&)>;
    using AdditionalRelaxationSteps = std::function<void(void)>;

    BasePathSearchWithRelax(EdgeWeightedGraph const& graph, Vertex const& startVertex)
        : m_graph(graph)
        , m_startVertex(startVertex)
    {}

    virtual ~BasePathSearchWithRelax()
    {}

    bool hasPathTo(Vertex const& endVertex) const
    {
        return m_vertexToEdgeWithBestWeightMap.find(endVertex) != m_vertexToEdgeWithBestWeightMap.cend();
    }

    Path getPathTo(Vertex const& endVertex) const
    {
        Path reversedPath;
        bool shouldAddStartVertexAndReverse(endVertex != m_startVertex);
        Vertex currentVertex = endVertex;
        while(currentVertex != m_startVertex)
        {
            reversedPath.emplace_back(currentVertex);
            auto it = m_vertexToEdgeWithBestWeightMap.find(currentVertex);
            if(it != m_vertexToEdgeWithBestWeightMap.cend())
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
        return m_vertexToEdgeWithBestWeightMap.find(vertex) == m_vertexToEdgeWithBestWeightMap.cend();
    }

    Weight getSavedWeightAt(Vertex const& vertex) const
    {
        Weight result{};
        auto it = m_vertexToEdgeWithBestWeightMap.find(vertex);
        if(it != m_vertexToEdgeWithBestWeightMap.cend())
        {
            result = it->second.weight;
        }
        return result;
    }

    void setStartVertexWeightToZero()
    {
        m_vertexToEdgeWithBestWeightMap[m_startVertex] = EdgeWithWeight(m_startVertex, m_startVertex, Weight{});
    }

    void relaxAt(
            Vertex const& vertex,
            AdditionalRelaxationStepsWithNewWeight const& additionalRelaxationStepsWithNewWeight = getNoStepsWithNewWeight(),
            AdditionalRelaxationSteps const& additionalRelaxationSteps = getNoSteps())
    {
        // Relaxing means recalculating the shortest/longest path (there might be a new way with better weight)
        // Here all the information from the given vertex to its adjacent vertices are updated
        for(Vertex const& adjacentVertex : m_graph.getAdjacentVerticesAt(vertex))
        {
            Weight weightOfCurrentEdge(m_graph.getWeight(vertex, adjacentVertex));
            Weight savedWeightAtVertex(getSavedWeightAt(vertex));
            Weight savedWeightAtAdjacentVertex(getSavedWeightAt(adjacentVertex));
            if(hasNoWeightSaved(adjacentVertex)
                    || m_comparator(savedWeightAtVertex + weightOfCurrentEdge, savedWeightAtAdjacentVertex))
            {
                Weight newWeight(savedWeightAtVertex + weightOfCurrentEdge);
                m_vertexToEdgeWithBestWeightMap[adjacentVertex] = EdgeWithWeight(vertex, adjacentVertex, newWeight);
                additionalRelaxationStepsWithNewWeight(vertex, adjacentVertex, newWeight);
            }
        }
        additionalRelaxationSteps();
    }

    static AdditionalRelaxationStepsWithNewWeight getNoStepsWithNewWeight()
    {
        static AdditionalRelaxationStepsWithNewWeight noRelaxationSteps
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
    Comparator m_comparator;
    VertexToEdgeWithWeightMap m_vertexToEdgeWithBestWeightMap;
};

}

}
