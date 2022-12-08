#pragma once

namespace alba
{

namespace algorithm
{

template <typename Object>
class BaseUnionFind
{
public:
    virtual ~BaseUnionFind() = default;

    virtual bool isConnected(Object const& object1, Object const& object2) const = 0;
    virtual Object getRoot(Object const& object) const = 0; // this is basically an identifier for the connected components
    virtual void connect(Object const& object1, Object const& object2) = 0;
};

}

}

// This can be called as a disjoint-set data structure.
// A disjoint-set data structure is a data structure that keeps track of a set of elements partitioned into a number of disjoint (non-overlapping) subsets.
// A union-find algorithm is an algorithm that performs two useful operations on such a data structure:
// -> Find: Determine which subset a particular element is in. This can be used for determining if two elements are in the same subset.
// -> Union: Join two subsets into a single subset.
// In this post, we will discuss the application of Disjoint Set Data Structure.
