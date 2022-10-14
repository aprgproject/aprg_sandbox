#pragma once

#include <Algorithm/Search/RangeQuery/RangeQueryWithSegmentTree.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class RangeQueryWithLazySegmentTree : public RangeQueryWithSegmentTree<Values>
{
public:

    // Using lazy propagation, we can build a segment tree that supports both range updates and range queries in O(logn) time.
    // The idea is to perform updates and queries from top to bottom and perform updates lazily
    // so that they are propagated down the tree only when it is necessary.

    // In a lazy segment tree, nodes contain two types of information.
    // Like in an ordinary segment tree, each node contains the sum or some other value related to the corresponding subarray.
    // In addition, the node may contain information related to lazy updates, which has not been propagated to its children.

    // There are two types of range updates: each array value in the range is either increased by some value or assigned some value.
    // Both operations can be implemented using similar ideas, and it is even possible to construct a tree that supports both operations at the same time.

    using BaseClass = RangeQueryWithSegmentTree<Values>;
    using Value = typename BaseClass::Value;

    RangeQueryWithLazySegmentTree(
            Values const& valuesToCheck,
            Function const& functionObject)
        : BaseClass(valuesToCheck, functionObject)
        , b_treeValues(BaseClass::m_treeValues)
        , m_pendingUpdates(b_treeValues.size(), Value{})
    {}

private:

    Values & b_treeValues;
    Values m_pendingUpdates;
};

}

}
