#pragma once

#include <Algorithm/Graph/PathSearch/DepthFirstSearch/PathSearchUsingDfs.hpp>
#include <Algorithm/Graph/PathSearch/Common/BasePathSearchWithDistanceCount.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class PathSearchUsingDfsWithDistanceCount
        : public BasePathSearchWithDistanceCount<Vertex>
        , public PathSearchUsingDfs<Vertex>
{
public:
    using BaseDistanceCount = BasePathSearchWithDistanceCount<Vertex>;
    using BaseBfs = PathSearchUsingDfs<Vertex>;
    using BaseGraphWithVertex = BaseGraph<Vertex>;
    using Vertices = typename GraphTypes<Vertex>::Vertices;
    using InitializeDataFunction = typename BaseBfs::InitializeDataFunction;
    using UpdateDataFunction = typename BaseBfs::UpdateDataFunction;

    PathSearchUsingDfsWithDistanceCount(BaseGraphWithVertex const& graph, Vertices const& startVertices)
        : BaseDistanceCount()
        , BaseBfs(graph, startVertices, getInitializeDataFunction(), getUpdateDataFunction())
    {}

private:

    InitializeDataFunction getInitializeDataFunction()
    {
        return std::bind(&BaseDistanceCount::initializeDistances, this, std::placeholders::_1);
         // scope resolution "::" has the highest precedence
    }

    UpdateDataFunction getUpdateDataFunction()
    {
        return std::bind(&BaseDistanceCount::updateDistance, this, std::placeholders::_1, std::placeholders::_2);
         // scope resolution "::" has the highest precedence
    }
};

}

}
