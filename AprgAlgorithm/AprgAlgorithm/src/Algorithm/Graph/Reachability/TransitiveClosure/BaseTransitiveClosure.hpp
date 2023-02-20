#pragma once

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BaseTransitiveClosure
{
public:

    virtual ~BaseTransitiveClosure() = default; // virtual destructor because of virtual functions (vtable exists)

    virtual bool isReachable(Vertex const& sourceVertex, Vertex const& destinationVertex) const = 0;
};
}

}