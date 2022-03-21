#pragma once

namespace alba
{

namespace algorithm
{

template<typename Vertex>
class BaseConnectedComponents
{
public:
    virtual bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const = 0;
    virtual unsigned int getNumberOfComponentIds() const = 0;
};

}

}
