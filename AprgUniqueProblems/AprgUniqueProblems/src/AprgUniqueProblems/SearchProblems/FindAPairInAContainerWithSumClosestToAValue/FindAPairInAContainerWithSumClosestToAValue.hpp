#pragma once

#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <limits>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class FindAPairInAContainerWithSumClosestToAValue {
public:
    // Another problem that can be solved using the two pointers method is the following problem,
    // also known as the 2SUM problem: given an array of n numbers and a target sum x,
    // find two array values such that their sum is x, or report that no such values exist.

    using Index = int;
    using Value = typename Values::value_type;
    using ValuePair = std::pair<Value, Value>;

    FindAPairInAContainerWithSumClosestToAValue(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    ValuePair getValuePairWithSumClosestToAValue(Value const& targetSum) const {
        // std::less_equal because index can be equal
        return getValuePairWithSumClosestToAValue(targetSum, 0, m_sortedValues.size() - 1);
    }

private:
    ValuePair getValuePairWithSumClosestToAValue(
        Value const& targetSum, Index const lowestIndex, Index const highestIndex) const {
        ValuePair result{};
        if (!m_sortedValues.empty()) {
            // similar to TwoSum

            Value minimumDeviation(std::numeric_limits<Value>::max());
            Index lowerIndex = lowestIndex, higherIndex = highestIndex;
            while (lowerIndex < higherIndex) {
                Value currentSum(m_sortedValues.at(lowerIndex) + m_sortedValues.at(higherIndex));
                Value currentDeviation(mathHelper::getPositiveDelta(currentSum, targetSum));
                if (minimumDeviation > currentDeviation) {
                    minimumDeviation = currentDeviation;
                    result = {m_sortedValues.at(lowerIndex), m_sortedValues.at(higherIndex)};
                }
                if (currentSum == targetSum) {
                    break;
                } else if (currentSum > targetSum) {
                    higherIndex--;
                } else if (currentSum < targetSum) {
                    lowerIndex++;
                }
            }
        }
        return result;
    }

    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba

// Given a sorted array and a number x, find a pair in array whose sum is closest to x.

// An efficient solution can find the pair in O(n) time. The idea is similar to method 1 of this post.
// The following is a detailed algorithm:
// -> 1) Initialize a variable diff as infinite (Diff is used to store the difference between pair and x).
// ---> We need to find the minimum diff.
// -> 2) Initialize two index variables l and r in the given sorted array.
// ---> (a) Initialize first to the leftmost index:  l = 0
// ---> (b) Initialize second  the rightmost index:  r = n-1
// -> 3) Loop while l < r.
// ---> (a) If  abs(arr[l] + arr[r] - sum) < diff  then
// -----> update diff and result
// ---> (b) If(arr[l] + arr[r] <  sum )  then l++
// ---> (c) Else r--
