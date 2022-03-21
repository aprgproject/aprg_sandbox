#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

#include <string>

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
        return GraphDirectionType::Undirected;
    }
};

}

}
