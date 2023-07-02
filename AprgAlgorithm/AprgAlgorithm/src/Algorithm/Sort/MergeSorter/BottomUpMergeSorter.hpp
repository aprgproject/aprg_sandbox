#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/MergeSorter/MergeSorterUtilities.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class BottomUpMergeSorter : public BaseSorter<Values> {
public:
    BottomUpMergeSorter() = default;

    void sort(Values& valuesToSort) const override {
        Values auxiliary(valuesToSort);
        int const size = valuesToSort.size();
        for (int subHalfSize = 1; subHalfSize < size; subHalfSize *= 2) {
            for (int lowest = 0; lowest < size - subHalfSize; lowest += subHalfSize * 2) {
                int middle = lowest + subHalfSize - 1;
                int highest = std::min(lowest + (subHalfSize * 2) - 1, size - 1);
                mergeTheTwoSortedParts(valuesToSort, auxiliary, lowest, middle, highest);
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// No recursion approach
// Concise industrial-strength code, if you have the space

// Takes N*log2(N) as well

// Stable -> Proof: Merge sort is stable if the merge operation is stable.
// Since the merge operation is stable (equal items never move past each other), then merge sort is stable.
