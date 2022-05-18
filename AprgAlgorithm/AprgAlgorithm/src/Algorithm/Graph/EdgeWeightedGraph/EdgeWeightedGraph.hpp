#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>
#include <Algorithm/Graph/Utilities/SortedEdge.hpp>

#include <algorithm>
#include <sstream>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename Graph>
class EdgeWeightedGraph : public Graph
{
public:
    using BaseClass = Graph;
    using Edge = typename GraphTypes<Vertex>::Edge;
    using EdgeToWeightMap = std::map<Edge, Weight>;
    using EdgeWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgeWithWeight;
    using EdgesWithWeight = typename GraphTypesWithWeights<Vertex, Weight>::EdgesWithWeight;
    using Weights = std::vector<Weight>;
    EdgeWeightedGraph()
        : BaseClass()
    {}
    bool hasAUniqueMinimumSpanningTree() const
    {
        return hasNoDuplicateWeights(getSortedWeights());
    }

    Weight getWeight(Vertex const& vertex1, Vertex const& vertex2) const
    {
        Weight result{};
        auto it = m_edgeToWeightMap.find(createEdgeInMap(vertex1, vertex2));
        if(it != m_edgeToWeightMap.cend())
        {
            result = it->second;
        }
        return result;
    }

    Weights getSortedWeights() const
    {
        Weights weights(getAllWeights());
        std::sort(weights.begin(), weights.end());
        return weights;
    }

    EdgeToWeightMap const& getEdgeToWeightMap() const
    {
        return m_edgeToWeightMap;
    }

    EdgesWithWeight getEdgesWithWeight() const
    {
        EdgesWithWeight result;
        std::transform(m_edgeToWeightMap.cbegin(), m_edgeToWeightMap.cend(), std::back_inserter(result), [](auto const& edgeAndWeightPair)
        {
            return EdgeWithWeight(edgeAndWeightPair.first.first, edgeAndWeightPair.first.second, edgeAndWeightPair.second);
        });
        return result;
    }

    std::string getDisplayableString() const override
    {
        std::string firstPart(BaseClass::getDisplayableString());
        std::stringstream ss;
        ss << "Edges with weight: {";
        for(auto const& edgeWithWeight : m_edgeToWeightMap)
        {
            ss << edgeWithWeight.first.first << "<->" << edgeWithWeight.first.second << "("<< edgeWithWeight.second << "), ";
        }
        ss << "}";
        return firstPart + ss.str();
    }

    void connect(Vertex const& vertex1, Vertex const& vertex2, Weight const& weight)
    {
        connect(vertex1, vertex2);
        m_edgeToWeightMap[createEdgeInMap(vertex1, vertex2)] = weight;
    }

    void disconnect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        BaseClass::disconnect(vertex1, vertex2);
        m_edgeToWeightMap.erase(createEdgeInMap(vertex1, vertex2));
    }

private:

    void connect(Vertex const& vertex1, Vertex const& vertex2) override
    {
        BaseClass::connect(vertex1, vertex2);
    }

    bool hasNoDuplicateWeights(Weights const& sortedWeights) const
    {
        return std::adjacent_find(sortedWeights.cbegin(), sortedWeights.cend()) == sortedWeights.cend();
    }

    Weights getAllWeights() const
    {
        Weights result;
        std::transform(m_edgeToWeightMap.cbegin(), m_edgeToWeightMap.cend(), std::back_inserter(result), [&](auto const& edgeAndWeightPair)
        {
            return edgeAndWeightPair.second;
        });
        return result;
    }

    Edge createEdgeInMap(Vertex const& vertex1, Vertex const& vertex2) const
    {
        if(this->DIRECTION_TYPE == GraphDirectionType::Undirected)
        {
            return createSortedEdge<Vertex, Edge>(vertex1, vertex2);
        }
        else
        {
            return Edge(vertex1, vertex2);
        }
    }
    EdgeToWeightMap m_edgeToWeightMap;
};
}

}
