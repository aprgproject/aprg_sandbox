#pragma once

#include <vector>

namespace alba
{

class SumRangeQuerySegmentTree
{
public:
    // A segment tree is a data structure that supports two operations: processing a range query and updating an array value.
    // Segment trees can support sum queries, minimum and maximum queries and many other queries so that both operations work in O(logn) time.
    // Compared to a binary indexed tree, the advantage of a segment tree is that it is a more general data structure.
    // While binary indexed trees only support sum queries, segment trees also support other queries.
    // On the other hand, a segment tree requires more memory and is a bit more difficult to implement.

    //Segment trees can support all range queries where it is possible to divide a range into two parts,
    //calculate the answer separately for both parts and then efficiently combine the answers.

    // Examples of such queries are minimum and maximum, greatest common divisor, and bit operations and, or and xor.

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
