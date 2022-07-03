#pragma once

#include <vector>

namespace alba
{

class SumRangeQuerySegmentTree
{
public:
    // Sum queries
    // We can easily process sum queries on a static array by constructing a prefix sum array.
    // Each value in the prefix sum array equals the sum of values in the original array up to that position, i.e., the value at position k is sumq(0,k).

    // A binary indexed tree or a Fenwick tree2 can be seen as a dynamic variant of a prefix sum array.
    // It supports two O(logn) time operations on an array: processing a range sum query and updating a value.

    using Index = unsigned int;
    using Value = unsigned int;
    using Values = std::vector<Value>;
    static constexpr unsigned int NUMBER_OF_CHILDREN=2U; // only 2 children are supported for now

    SumRangeQuerySegmentTree(Values const& valuesToCheck);

    Value getSumFromStartToEnd(Index const start, Index const end) const;
    void changeValueAtIndex(Index const index, Value const value);
private:
    bool isLeftChild(Index const index) const;
    bool isRightChild(Index const index) const;
    Index getParent(Index const index) const;
    Index getCielOfLogarithmOfChildren(Index const index) const;
    Index getChildrenRaiseToPower(Index const index) const;
    void initialize(Values const& valuesToCheck);
    Index m_startOfChildren;
    Values m_treeValues;
};

}
