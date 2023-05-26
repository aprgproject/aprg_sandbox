#pragma once

#include <vector>

namespace alba {

class SubArraySum {
public:
    // As the first example, consider a problem where we are given an array of n positive integers and a target sum x,
    // and we want to find a subarray whose sum is x or report that there is no such subarray.

    using Index = int;
    using Value = int;
    using Values = std::vector<Value>;

    SubArraySum(Values const& valuesToCheck);
    Values getSubArrayWithSum(Value const targetSum) const;

private:    Values m_valuesToCheck;
};

}  // namespace alba
