#pragma once

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class BaseTransitiveClosure
{
public:
    virtual bool isReachable(Vertex const& sourceVertex, Vertex const& destinationVertex) const = 0;
};

}

}
