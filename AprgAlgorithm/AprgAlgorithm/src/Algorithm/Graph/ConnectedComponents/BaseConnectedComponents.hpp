#pragma once

#include <Algorithm/Graph/GraphTypes.hpp>

namespace alba
{

namespace algorithm
{

class BaseConnectedComponents
{
public:
    virtual bool isConnected(Vertex const vertex1, Vertex const vertex2) const = 0;
};

}

}
