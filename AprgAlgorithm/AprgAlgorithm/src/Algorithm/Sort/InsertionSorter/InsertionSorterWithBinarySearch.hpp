#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>

#include <utility>
namespace alba {

namespace algorithm {

template <typename Values>
class InsertionSorterWithBinarySearch : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;
    static constexpr int INVALID_INDEX = getInvalidIndex<int>();

    InsertionSorterWithBinarySearch() = default;

    void sort(Values& valuesToSort) const override {
        for (int insertIndex(1); insertIndex < static_cast<int>(valuesToSort.size()); insertIndex++) {
            swapDownWithIndexFoundInBinarySearch(valuesToSort, insertIndex);
        }
    }

private:
    void swapDownWithIndexFoundInBinarySearch(Values& valuesToSort, int const insertIndex) const {
        int indexWithGreaterValue =
            getIndexWithGreaterValueUsingBinarySearch(valuesToSort, 0, insertIndex - 1, valuesToSort[insertIndex]);
        if (indexWithGreaterValue != INVALID_INDEX) {
            for (int swapIndex(insertIndex); swapIndex > indexWithGreaterValue; swapIndex--) {
                std::swap(valuesToSort[swapIndex - 1], valuesToSort[swapIndex]);
            }
        }
    }

    int getIndexWithGreaterValueUsingBinarySearch(
        Values const& valuesToSort, int const lowIndex, int const highIndex, Value const& value) const {
        int result(INVALID_INDEX);
        int iLow(lowIndex), iHigh(highIndex);
        while (iLow <= iHigh) {
            int middleIndex = getMidpointOfIndexes(iLow, iHigh);
            Value middleValue(valuesToSort[middleIndex]);
            if (value < middleValue) {
                result = middleIndex;
                iHigh = middleIndex - 1;
            } else  // (middleValue < value)
            {
                iLow = middleIndex + 1;
            }
        }
        return result;
    }
};

}  // namespace algorithm

}  // namespace alba

// We can use binary search to reduce the number of comparisons in normal insertion sort.
// Binary Insertion Sort uses binary search to find the proper location to insert the selected item at each iteration.
// In normal insertion sort, it takes O(n) comparisons (at nth iteration) in the worst case.
// We can reduce it to O(log n) by using binary search.

// Time Complexity: The algorithm as a whole still has a running worst-case running time of O(n2) because of the series
// of swaps required for each insertion.
