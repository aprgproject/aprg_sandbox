#pragma once

namespace alba
{

namespace algorithm
{

template <typename Vertex>
class BaseConnectedComponents
{
public:
    virtual ~BaseConnectedComponents() = default;

    virtual bool isConnected(Vertex const& vertex1, Vertex const& vertex2) const = 0;
    virtual unsigned int getNumberOfComponentIds() const = 0;
    virtual unsigned int getComponentId(Vertex const& vertex) const = 0;
};

// The relation "is connected to" is an equivalence relation.
// -> Reflexive: v is connected to v.
// -> Symmetric: if v is connected to w, then w is connected to v.
// -> Transitive: if v is connected to w and w is connected to x then v is connected to x.

}

}
