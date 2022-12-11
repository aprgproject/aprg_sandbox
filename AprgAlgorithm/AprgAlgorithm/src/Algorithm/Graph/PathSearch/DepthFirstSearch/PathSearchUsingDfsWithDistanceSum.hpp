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
    using InitializeDataFunction = typename BaseBfs::InitializeDataFunction;
    using UpdateDataFunction = typename BaseBfs::UpdateDataFunction;

    PathSearchUsingDfsWithDistanceSum(EdgeWeightedGraph const& graph, Vertices const& startVertices)
        : BaseDistanceSum(graph)
        , BaseBfs(graph, startVertices, getInitializeDataFunction(), getUpdateDataFunction())
    {}

private:

    InitializeDataFunction getInitializeDataFunction()
    {
        return std::bind(&BaseDistanceSum::initializeDistances, this, std::placeholders::_1);
         // scope resolution "::" has the highest precedence
    }

    UpdateDataFunction getUpdateDataFunction()
    {
        return std::bind(&BaseDistanceSum::updateDistance, this, std::placeholders::_1, std::placeholders::_2);
         // scope resolution "::" has the highest precedence
    }
};

}

}
