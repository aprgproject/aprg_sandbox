#pragma once

namespace alba
{

namespace algorithm
{

template <typename Object>
class BaseUnionFind
{
public:
    virtual ~BaseUnionFind()
    {}

    virtual bool isConnected(Object const& object1, Object const& object2) const = 0;
    virtual Object getRoot(Object const& object) const = 0; // this is basically an identifier for the connected components
    virtual void connect(Object const& object1, Object const& object2) = 0;
};
}

}