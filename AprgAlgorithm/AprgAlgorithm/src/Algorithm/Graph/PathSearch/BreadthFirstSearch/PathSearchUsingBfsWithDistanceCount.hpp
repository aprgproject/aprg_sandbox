#pragma once

#include <Algorithm/Graph/PathSearch/BreadthFirstSearch/PathSearchUsingBfs.hpp>
#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithDistanceCount.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class PathSearchUsingBfsWithDistanceCount
        : public BasePathSearchWithDistanceCount<Vertex>
        , public PathSearchUsingBfs<Vertex>
{
public:
    using BaseDistanceCount = BasePathSearchWithDistanceCount<Vertex>;
    using BaseBfs = PathSearchUsingBfs<Vertex>;
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using InitializeDataFunction = typename BaseBfs::InitializeDataFunction;
    using UpdateDataFunction = typename BaseBfs::UpdateDataFunction;

    PathSearchUsingBfsWithDistanceCount(BaseGraphWithVertex const& graph, Vertices const& startVertices)
        : BaseDistanceCount()
        , BaseBfs(graph, startVertices, getInitializeDataFunction(), getUpdateDataFunction())
    {}

private:

    InitializeDataFunction getInitializeDataFunction()
    {
        return [&](Vertices const& vertices)
        {
            BaseDistanceCount::initializeDistances(vertices);
        };
    }

    UpdateDataFunction getUpdateDataFunction()
    {
        return [&](Vertex const& vertex1, Vertex const& vertex2)
        {
            BaseDistanceCount::updateDistance(vertex1, vertex2);
        };
    }
};
}

}