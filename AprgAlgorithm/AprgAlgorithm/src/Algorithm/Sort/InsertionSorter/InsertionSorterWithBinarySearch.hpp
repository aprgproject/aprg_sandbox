#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Utilities/InvalidIndex.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>

#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class InsertionSorterWithBinarySearch : public BaseSorter<Values> {
public:
    using Value = typename Values::value_type;
    static constexpr unsigned int INVALID_INDEX = getInvalidIndex<unsigned int>();

    InsertionSorterWithBinarySearch() = default;

    void sort(Values& valuesToSort) const override {
        for (unsigned int insertIndex(1U); insertIndex < valuesToSort.size(); insertIndex++) {
            swapDownWithIndexFoundInBinarySearch(valuesToSort, insertIndex);
        }
    }

private:
    void swapDownWithIndexFoundInBinarySearch(Values& valuesToSort, unsigned int const insertIndex) const {
        unsigned int indexWithGreaterValue =
            getIndexWithGreaterValueUsingBinarySearch(valuesToSort, 0U, insertIndex - 1U, valuesToSort.at(insertIndex));
        if (indexWithGreaterValue != INVALID_INDEX) {
            for (unsigned int swapIndex(insertIndex); swapIndex > indexWithGreaterValue; swapIndex--) {
                std::swap(valuesToSort[swapIndex - 1], valuesToSort[swapIndex]);
            }
        }
    }

    unsigned int getIndexWithGreaterValueUsingBinarySearch(
        Values const& valuesToSort, unsigned int const lowestIndex, unsigned int const highestIndex,
        Value const& value) const {
        unsigned int result(INVALID_INDEX);
        unsigned int lowerIndex(lowestIndex), higherIndex(highestIndex);
        while (lowerIndex <= higherIndex) {
            unsigned int middleIndex = getMidpointOfIndexes(lowerIndex, higherIndex);
            Value middleValue(valuesToSort.at(middleIndex));
            if (value < middleValue) {
                result = middleIndex;
                if (middleIndex > 0U) {
                    higherIndex = middleIndex - 1;
                } else {
                    break;
                }
            } else  // (middleValue < value)
            {
                lowerIndex = middleIndex + 1;
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
