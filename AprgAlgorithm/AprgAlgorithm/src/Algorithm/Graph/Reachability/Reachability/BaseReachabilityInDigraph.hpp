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

    virtual ~BaseReachabilityInDigraph() = default; // virtual destructor because of virtual functions (vtable exists)

    virtual bool isReachable(Vertex const& destinationVertex) const = 0;
};
}

}