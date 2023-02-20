#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BaseUndirectedGraph : public BaseGraph<Vertex>
{
public:

    virtual ~BaseUndirectedGraph() = default; // virtual destructor because of virtual functions (vtable exists)

    virtual bool hasAnyConnection(Vertex const& vertex) const = 0;
    GraphDirectionType getGraphDirectionType() const
    {
        return DIRECTION_TYPE;    }
    static constexpr GraphDirectionType DIRECTION_TYPE = GraphDirectionType::Undirected;
};

}

}
