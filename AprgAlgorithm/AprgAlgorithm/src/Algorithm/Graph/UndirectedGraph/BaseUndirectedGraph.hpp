#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class BaseUndirectedGraph : public BaseGraph<Vertex>
{
public:
    virtual bool hasAnyConnection(Vertex const& vertex) const = 0;

    GraphDirectionType getGraphDirectionType() const
    {
        return DIRECTION_TYPE;
    }
    static constexpr GraphDirectionType DIRECTION_TYPE = GraphDirectionType::Undirected;
};

}
}