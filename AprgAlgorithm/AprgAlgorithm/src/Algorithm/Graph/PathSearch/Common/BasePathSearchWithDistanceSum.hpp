#pragma once

#include <Algorithm/Graph/Types/GraphTypes.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class BasePathSearchWithDistanceSum {
public:
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using VertexToWeightMap = typename GraphTypesWithWeights<Vertex, Weight>::VertexToWeightMap;

    BasePathSearchWithDistanceSum(EdgeWeightedGraph const& graph) : m_graph(graph) {}

    Weight getDistanceTo(Vertex const& endVertex) const {
        Weight result(0);
        auto it = m_endVertexToDistanceSumMap.find(endVertex);
        if (it != m_endVertexToDistanceSumMap.cend()) {
            result = it->second;
        }
        return result;
    }

    VertexToWeightMap const& getEndVertexToDistanceSumMap() const { return m_endVertexToDistanceSumMap; }

    void initializeDistances(Vertices const& vertices) {
        for (Vertex const& vertex : vertices) {
            m_endVertexToDistanceSumMap.emplace(vertex, Vertex{});
        }
    }

    void updateDistance(Vertex const& adjacentVertex, Vertex const& vertex) {
        Weight distanceToVertex(0);
        auto it = this->m_endVertexToDistanceSumMap.find(vertex);
        if (it != this->m_endVertexToDistanceSumMap.cend()) {
            distanceToVertex = it->second;
        }
        this->m_endVertexToDistanceSumMap[adjacentVertex] =
            distanceToVertex + m_graph.getWeight(vertex, adjacentVertex);
    }

protected:
    // No need for virtual destructor because this class is not destroyed polymorphically.
    // Guideline #4: A base class destructor should be either public and virtual, or protected and nonvirtual.
    // Source: http://www.gotw.ca/publications/mill18.htm
    ~BasePathSearchWithDistanceSum() = default;

private:
    EdgeWeightedGraph const& m_graph;
    VertexToWeightMap m_endVertexToDistanceSumMap;
};

}  // namespace algorithm

}  // namespace alba
