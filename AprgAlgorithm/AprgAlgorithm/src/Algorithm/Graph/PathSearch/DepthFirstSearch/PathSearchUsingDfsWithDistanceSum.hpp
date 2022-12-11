#pragma once

#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>
#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithDistanceSum.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class PathSearchUsingDfsWithDistanceSum
        : public BasePathSearchWithDistanceSum<Vertex, Weight, EdgeWeightedGraph>
        , public PathSearchUsingDfs<Vertex>
{
public:
    using BaseDistanceSum = BasePathSearchWithDistanceSum<Vertex, Weight, EdgeWeightedGraph>;
    using BaseBfs = PathSearchUsingDfs<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using UpdateFunction = typename BaseBfs::UpdateFunction;

    PathSearchUsingDfsWithDistanceSum(EdgeWeightedGraph const& graph, Vertices const& startVertices)
        : BaseDistanceSum(graph)
        , BaseBfs(graph, startVertices, getUpdateFunction())
    {}

private:

    void updateDistance(Vertex const& adjacentVertex, Vertex const& vertex)
    {
        Weight distanceToVertex(0U);
        auto it = this->m_endVertexToDistanceSumMap.find(vertex);
        if(it != this->m_endVertexToDistanceSumMap.cend())
        {
            distanceToVertex = it->second;
        }
        this->m_endVertexToDistanceSumMap[adjacentVertex]
                = distanceToVertex + BaseDistanceSum::m_graph.getWeight(vertex, adjacentVertex);
    }

    UpdateFunction getUpdateFunction()
    {
        return std::bind(&PathSearchUsingDfsWithDistanceSum::updateDistance, this, std::placeholders::_1, std::placeholders::_2);
         // scope resolution "::" has the highest precedence
    }
};

}

}
