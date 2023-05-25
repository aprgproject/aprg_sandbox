#pragma once

#include <algorithm>

namespace alba {

namespace algorithm {

template <typename Values>
class MaximumSubArraySum {
public:
    // Given an array of n numbers, our task is to calculate the maximum subarray sum, i.e.,
    // the largest possible sum of a sequence of consecutive values in the array.
    // The problem is interesting when there may be negative values in the array.

    using Index = int;
    using Value = typename Values::value_type;
    struct SubArrayDetails {
        Index lowIndex;
        Index highIndex;
        Value sum;
    };

    MaximumSubArraySum(Values const& valuesToCheck) : m_valuesToCheck(valuesToCheck) {}

    Value getMaximumSubArraySum() {
        // Surprisingly, it is possible to solve the problem in O(n) time, which means that just one loop is enough.
        // The idea is to calculate, for each array position, the maximum sum of a subarray that ends at that position.
        // After this, the answer for the problem is the maximum of those sums.
        // Consider the subproblem of finding the maximum-sum subarray that ends at position k.

        // There are two possibilities:
        // 1. The subarray only contains the element at position k.
        // 2. The subarray consists of a subarray that ends at position k-1, followed by the element at position k.

        // In the latter case, since we want to find a subarray with maximum sum, the subarray that ends at position k-1
        // should also have the maximum sum. Thus, we can solve the problem efficiently by calculating the maximum
        // subarray sum or each ending position from left to right.

        // This linear-time algorithm is attributed to J. B. Kadane, and the algorithm is sometimes called Kadane’s
        // algorithm.

        Value currentSum(0), bestSum(0);
        for (Value const& value : m_valuesToCheck) {
            currentSum = std::max(value, currentSum + value);
            bestSum = std::max(bestSum, currentSum);
        }
        return bestSum;
    }

    SubArrayDetails getMaximumSubArraySumWithDetails() {
        SubArrayDetails currentSubArray{}, bestSubArray{};
        int index(0);
        for (Value const& value : m_valuesToCheck) {
            if (value > currentSubArray.sum + value)  // new sub array contains only value
            {
                currentSubArray = {index, index, value};
            } else {
                // add value to current sub array
                currentSubArray.highIndex = index;
                currentSubArray.sum += value;
            }
            if (bestSubArray.sum < currentSubArray.sum) {
                bestSubArray = currentSubArray;
            }
            index++;
        }
        return bestSubArray;
    }

private:
    Values const& m_valuesToCheck;
};

}  // namespace algorithm

}  // namespace alba
