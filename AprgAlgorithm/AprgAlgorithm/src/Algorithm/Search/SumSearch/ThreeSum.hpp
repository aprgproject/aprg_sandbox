#pragma once

#include <Algorithm/Search/SumSearch/TwoSum.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class ThreeSum {
public:
    // Approach: By Sorting the array the efficiency of the algorithm can be improved.
    // This efficient approach uses the two-pointer technique.
    // Traverse the array and fix the first element of the triplet.
    // Now use the Two Pointers algorithm to find if there is a pair whose sum is equal to x – array[i].
    // Two pointers algorithm take linear time so it is better than a nested loop.

    // Algorithm :
    // (1) Sort the given array.
    // (2) Loop over the array and fix the first element of the possible triplet, arr[i].
    // (3) Then fix two pointers, one at i + 1 and the other at n – 1. And look at the sum,
    // ----> If the sum is smaller than the required sum, increment the first pointer.
    // ----> Else, If the sum is bigger, Decrease the end pointer to reduce the sum.
    // ----> Else, if the sum of elements at two-pointer is equal to given sum then print the triplet and break.

    // Complexity Analysis:
    // -> Time complexity: O(N^2).
    // ---> There are only two nested loops traversing the array, so time complexity is O(n^2).
    // ---> Two pointers algorithm takes O(n) time and the first element can be fixed using another nested traversal.
    // -> Space Complexity: O(1).
    // ---> As no extra space is required.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using ThreeValues = std::tuple<Value, Value, Value>;

    ThreeSum(Values const& sortedValues) : m_sortedValues(sortedValues) {}

    ThreeValues getNonDuplicateThreeValuesWithSum(Value const& targetSum) const {
        ThreeValues result{};
        if (!m_sortedValues.empty()) {
            TwoSum<Values> twoSum(m_sortedValues);
            for (Index firstIndex = 0; firstIndex < m_sortedValues.size(); firstIndex++) {
                Value const& firstValue(m_sortedValues.at(firstIndex));
                auto twoSumValues(twoSum.getNonDuplicateTwoValuesWithSum(
                    targetSum - firstValue, firstIndex + 1, m_sortedValues.size() - 1));
                if (firstValue + twoSumValues.first + twoSumValues.second == targetSum) {
                    result = ThreeValues{firstValue, twoSumValues.first, twoSumValues.second};
                    break;
                }
            }
        }
        return result;
    }

    ThreeValues getPossibleDuplicatedThreeValuesWithSum(Value const& targetSum) const {
        ThreeValues result{};
        if (!m_sortedValues.empty()) {
            TwoSum<Values> twoSum(m_sortedValues);
            for (Index firstIndex = 0; firstIndex < m_sortedValues.size(); firstIndex++) {
                Value const& firstValue(m_sortedValues.at(firstIndex));
                auto twoSumValues(twoSum.getPossibleDuplicatedTwoValuesWithSum(
                    targetSum - firstValue, firstIndex, m_sortedValues.size() - 1));
                if (firstValue + twoSumValues.first + twoSumValues.second == targetSum) {
                    result = ThreeValues{firstValue, twoSumValues.first, twoSumValues.second};
                    break;
                }
            }
        }
        return result;
    }

private:
    Values const& m_sortedValues;
};

}  // namespace algorithm

}  // namespace alba
