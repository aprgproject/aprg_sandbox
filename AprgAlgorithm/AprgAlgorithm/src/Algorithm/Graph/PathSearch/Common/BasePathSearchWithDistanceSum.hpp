#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class BasePathSearchWithDistanceSum
{
public:
    using VertexToWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToWeightMap;

    BasePathSearchWithDistanceSum(EdgeWeightedGraph const& graph)
        : m_graph(graph)
    {}

    virtual ~BasePathSearchWithDistanceSum() = default;

    Weight getDistanceTo(Vertex const& endVertex) const
    {
        Weight result(0);
        auto it = m_endVertexToDistanceSumMap.find(endVertex);
        if(it != m_endVertexToDistanceSumMap.cend())
        {
            result = it->second;
        }
        return result;
    }

    VertexToWeightMap const& getEndVertexToDistanceSumMap() const
    {
        return m_endVertexToDistanceSumMap;
    }

protected:
    EdgeWeightedGraph const& m_graph;
    VertexToWeightMap m_endVertexToDistanceSumMap;
};

}

}
