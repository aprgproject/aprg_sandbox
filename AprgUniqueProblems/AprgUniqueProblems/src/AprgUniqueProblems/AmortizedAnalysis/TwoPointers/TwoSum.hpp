#pragma once

#include <vector>

namespace alba
{

class TwoSum
{
public:
    // Another problem that can be solved using the two pointers method is the following problem,
    // also known as the 2SUM problem: given an array of n numbers and a target sum x,
    // find two array values such that their sum is x, or report that no such values exist.

    using Index = unsigned int;
    using Value = unsigned int;
    using Values = std::vector<Value>;
    using ValuesPair = std::pair<Value, Value>;

    TwoSum(Values const& valuesToCheck);

    ValuesPair getTwoValuesWithSum(Value const targetSum) const;
private:
    Values m_sortedValues;
};

}
