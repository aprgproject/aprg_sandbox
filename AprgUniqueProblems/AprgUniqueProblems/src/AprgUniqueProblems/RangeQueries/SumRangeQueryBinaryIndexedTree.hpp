#pragma once

#include <vector>

namespace alba
{

class SumRangeQueryBinaryIndexedTree
{
public:
    // Sum queries
    // We can easily process sum queries on a static array by constructing a prefix sum array.
    // Each value in the prefix sum array equals the sum of values in the original array up to that position, i.e., the value at position k is sumq(0,k).

    // A binary indexed tree or a Fenwick tree can be seen as a dynamic variant of a prefix sum array.
    // It supports two O(logn) time operations on an array: processing a range sum query and updating a value.

    using Index = unsigned int;    using Value = unsigned int;
    using Values = std::vector<Value>;

    SumRangeQueryBinaryIndexedTree(Values const& valuesToCheck);
    Value getSumFromStartToEnd(Index const start, Index const end) const;
    Value getSumFrom0ToIndex(Index const index) const;
    void changeValueAtIndex(Index const index, Value const value);
private:
    void initializePartialSums(Values const& valuesToCheck);
    Values m_valuesToCheck;
    Values m_partialTreeSums;
};

}
