#pragma once

#include <Algorithm/Graph/BaseGraph.hpp>

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BaseReachabilityInDigraph
{
public:
    virtual ~BaseReachabilityInDigraph()
    {}
    virtual bool isReachable(Vertex const& destinationVertex) const = 0;
};

}

}
