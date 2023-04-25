#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithDistanceSum.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex, typename Weight, typename EdgeWeightedGraph>
class PathSearchUsingDfsWithDistanceSum : public BasePathSearchWithDistanceSum<Vertex, Weight, EdgeWeightedGraph>,
                                          public PathSearchUsingDfs<Vertex> {
public:
    using BaseDistanceSum = BasePathSearchWithDistanceSum<Vertex, Weight, EdgeWeightedGraph>;
    using BaseBfs = PathSearchUsingDfs<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using InitializeDataFunction = typename BaseBfs::InitializeDataFunction;
    using UpdateDataFunction = typename BaseBfs::UpdateDataFunction;

    PathSearchUsingDfsWithDistanceSum(EdgeWeightedGraph const& graph, Vertices const& startVertices)
        : BaseDistanceSum(graph), BaseBfs(graph, startVertices, getInitializeDataFunction(), getUpdateDataFunction()) {}

private:
    InitializeDataFunction getInitializeDataFunction() {
        return [&](Vertices const& vertices) { BaseDistanceSum::initializeDistances(vertices); };
    }

    UpdateDataFunction getUpdateDataFunction() {
        return [&](Vertex const& vertex1, Vertex const& vertex2) { BaseDistanceSum::updateDistance(vertex1, vertex2); };
    }
};

}  // namespace algorithm

}  // namespace alba
