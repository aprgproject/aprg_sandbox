#pragma once

#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithDistanceCount.hpp>
#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>

namespace alba {

namespace algorithm {

template <typename Vertex>
class PathSearchUsingDfsWithDistanceCount : public BasePathSearchWithDistanceCount<Vertex>,
                                            public PathSearchUsingDfs<Vertex> {
public:
    using BaseDistanceCount = BasePathSearchWithDistanceCount<Vertex>;
    using BaseBfs = PathSearchUsingDfs<Vertex>;
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using InitializeDataFunction = typename BaseBfs::InitializeDataFunction;
    using UpdateDataFunction = typename BaseBfs::UpdateDataFunction;

    PathSearchUsingDfsWithDistanceCount(BaseGraphWithVertex const& graph, Vertices const& startVertices)
        : BaseDistanceCount(), BaseBfs(graph, startVertices, getInitializeDataFunction(), getUpdateDataFunction()) {}

private:
    InitializeDataFunction getInitializeDataFunction() {
        return [&](Vertices const& vertices) { BaseDistanceCount::initializeDistances(vertices); };
    }

    UpdateDataFunction getUpdateDataFunction() {
        return
            [&](Vertex const& vertex1, Vertex const& vertex2) { BaseDistanceCount::updateDistance(vertex1, vertex2); };
    }
};

}  // namespace algorithm

}  // namespace alba
