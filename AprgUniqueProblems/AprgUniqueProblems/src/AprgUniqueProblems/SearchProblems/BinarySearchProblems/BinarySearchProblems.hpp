#pragma once

#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class BinarySearchProblems {
public:
    using Count = int;
    using Index = int;
    using Value = typename Values::value_type;

    BinarySearchProblems() = default;

    Value getNearestFloor(Values const& sortedValues, Value const& valueToCheck) {
        // Problem Statement:
        // Given an array of N distinct integers, find floor value of input ‘key’.
        // Say, A = {-1, 2, 3, 5, 6, 8, 9, 10} and key = 7, we should return 6 as outcome.

        // We can use the above optimized implementation to find floor value of key.
        // We keep moving the left pointer to right most as long as the invariant holds.
        // Eventually left pointer points an element less than or equal to key (by definition floor value).
        // The following are possible corner cases:
        // —> If all elements in the array are smaller than key, left pointer moves till last element.
        // —> If all elements in the array are greater than key, it is an error condition.
        // —> If all elements in the array equal and <= key, it is worst case input to our implementation.

        Value result{};
        if (!sortedValues.empty()) {
            result = sortedValues.at(getNearestFloorIndex(sortedValues, valueToCheck));
        }
        return result;
    }

    Value getNearestCeil(Values const& sortedValues, Value const& valueToCheck) {
        Value result{};
        if (!sortedValues.empty()) {
            result = sortedValues.at(getNearestCielIndex(sortedValues, valueToCheck));
        }
        return result;
    }

    Index getNumberOfDuplicates(Values const& sortedValues, Value const& valueToCheck) {
        // Problem Statement:
        // Given a sorted array with possible duplicate elements.
        // Find number of occurrences of input ‘key’ in log N time.

        // The idea here is finding left and right most occurrences of key in the array using binary search.
        // We can modify floor function to trace right most occurrence and left most occurrence.

        Index result(getInvalidIndex<Index>());
        if (!sortedValues.empty()) {
            // reversed
            Index higherIndex = getNearestFloorIndex(sortedValues, valueToCheck);
            Index lowerIndex = getNearestCielIndex(sortedValues, valueToCheck);
            if (sortedValues.at(higherIndex) == valueToCheck && valueToCheck == sortedValues.at(lowerIndex)) {
                result = higherIndex + 1 - lowerIndex;
            }
        }
        return result;
    }

    Index getPositionOfRotation(Values const& sortedValues) {
        // Problem Statement:
        // Given a sorted array of distinct elements, and the array is rotated at an unknown position.
        // Find minimum element in the array.

        // Example in {6,7,8,9,10,[1],2,3,4,5} the answer is 5.

        // We converge the search space till l and r points single element.
        // If the middle location falls in the first pulse, the condition A[m] < A[r] doesn’t satisfy,
        // we converge our search space to A[m+1 … r].
        // If the middle location falls in the second pulse, the condition A[m] < A[r] satisfied,
        // we converge our search space to A[1 … m].
        // At every iteration we check for search space size, if it is 1, we are done.

        Index result(getInvalidIndex<Index>());
        Index lowerIndex(0), higherIndex(sortedValues.size() - 1);
        if (sortedValues.at(lowerIndex) <= sortedValues.at(higherIndex)) {
            result = lowerIndex;
        } else {
            while (lowerIndex <= higherIndex) {
                if (lowerIndex == higherIndex) {
                    result = lowerIndex;
                    break;
                }
                Index middleIndex = getMidpointOfIndexes(lowerIndex, higherIndex);
                if (sortedValues.at(middleIndex) < sortedValues.at(higherIndex)) {
                    higherIndex = middleIndex;
                } else {
                    lowerIndex = middleIndex + 1;
                }
            }
        }
        return result;
    }

private:
    Index getNearestFloorIndex(Values const& sortedValues, Value const& value) const {
        // Similar to nearest value binary search
        Index lowerIndex(0), higherIndex(sortedValues.size() - 1);
        while (lowerIndex + 1 < higherIndex) {
            Index middleIndex = getMidpointOfIndexes(lowerIndex, higherIndex);
            Value middleValue(sortedValues.at(middleIndex));
            if (middleValue <= value) {
                lowerIndex = middleIndex;
            } else {
                higherIndex = middleIndex;
            }
        }
        return lowerIndex;
    }

    Index getNearestCielIndex(Values const& sortedValues, Value const& value) const {
        // Similar to nearest value binary search
        Index lowerIndex(0), higherIndex(sortedValues.size() - 1);
        while (lowerIndex + 1 < higherIndex) {
            Index middleIndex = getMidpointOfIndexes(lowerIndex, higherIndex);
            Value middleValue(sortedValues.at(middleIndex));
            if (value <= middleValue) {
                higherIndex = middleIndex;
            } else {
                lowerIndex = middleIndex;
            }
        }
        return higherIndex;
    }
};

}  // namespace algorithm

}  // namespace alba

// Questions:
// 1. A function called signum(x, y) is defined as,
// signum(x, y) = -1 if x < y
//              =  0 if x = y
//              =  1 if x > y
// Did you come across any instruction set in which a comparison behaves like signum function?
// Can it make first implementation of binary search optimal?

// 2. Implement ceil function replica of floor function.

// 3. Discuss with your friends on “Is binary search optimal (results in least number of comparisons)?
// Why not ternary search or interpolation search on sorted array?
// When do you prefer ternary or interpolation search over binary search?”

// 4. Draw a tree representation of binary search (believe me, it helps you a lot to understand many internals of binary
// search).
