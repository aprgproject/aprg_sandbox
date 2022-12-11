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
    using UpdateFunction = typename BaseBfs::UpdateFunction;

    PathSearchUsingDfsWithDistanceCount(BaseGraphWithVertex const& graph, Vertices const& startVertices)
        : BaseDistanceCount()
        , BaseBfs(graph, startVertices, getUpdateFunction())
    {}

private:

    void updateDistance(Vertex const& adjacentVertex, Vertex const& vertex)
    {
        unsigned int distanceToVertex(0U);
        auto it = this->m_endVertexToDistanceCountMap.find(vertex);
        if(it != this->m_endVertexToDistanceCountMap.cend())
        {
            distanceToVertex = it->second;
        }
        this->m_endVertexToDistanceCountMap[adjacentVertex] = distanceToVertex+1U;
    }

    UpdateFunction getUpdateFunction()
    {
        return std::bind(&PathSearchUsingDfsWithDistanceCount::updateDistance, this, std::placeholders::_1, std::placeholders::_2);
         // scope resolution "::" has the highest precedence
    }
};

}

}
