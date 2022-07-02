#pragma once

#include <vector>

namespace alba
{

class SumRangeQuery
{
public:
    // Sum queries
    // We can easily process sum queries on a static array by constructing a prefix sum array.
    // Each value in the prefix sum array equals the sum of values in the original array up to that position, i.e., the value at position k is sumq(0,k).
    // The prefix sum array can be constructed in O(n) time.

    using Index = unsigned int;
    using Value = unsigned int;
    using Values = std::vector<Value>;

    SumRangeQuery(Values const& valuesToCheck);

    Value getSumFromStartAndEnd(Index const start, Index const end) const;
private:
    void initialize(Values const& valuesToCheck);
    Values m_partialSums;
};

}
