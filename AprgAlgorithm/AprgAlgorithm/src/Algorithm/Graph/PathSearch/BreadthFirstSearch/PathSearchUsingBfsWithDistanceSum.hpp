#pragma once

#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/PathSearchUsingBfs.hpp>
#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithDistanceSum.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class PathSearchUsingBfsWithDistanceSum
        : public BasePathSearchWithDistanceSum<Vertex, Weight, EdgeWeightedGraph>
        , public PathSearchUsingBfs<Vertex>
{
public:
    using BaseDistanceSum = BasePathSearchWithDistanceSum<Vertex, Weight, EdgeWeightedGraph>;
    using BaseBfs = PathSearchUsingBfs<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using InitializeDataFunction = typename BaseBfs::InitializeDataFunction;
    using UpdateDataFunction = typename BaseBfs::UpdateDataFunction;

    PathSearchUsingBfsWithDistanceSum(EdgeWeightedGraph const& graph, Vertices const& startVertices)
        : BaseDistanceSum(graph)
        , BaseBfs(graph, startVertices, getInitializeDataFunction(), getUpdateDataFunction())
    {}

private:

    InitializeDataFunction getInitializeDataFunction()
    {
        return [&](Vertices const& vertices)
        {
            BaseDistanceSum::initializeDistances(vertices);
        };
    }

    UpdateDataFunction getUpdateDataFunction()
    {
        return [&](Vertex const& vertex1, Vertex const& vertex2)
        {
            BaseDistanceSum::updateDistance(vertex1, vertex2);
        };
    }
};

}

}
