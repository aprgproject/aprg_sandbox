#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Common/Math/Helpers/ComputationHelpers.hpp>

#include <algorithm>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class CombSorter : public BaseSorter<Values> {
public:
    CombSorter() = default;

    void sort(Values& valuesToSort) const override {
        // Based from: https://en.wikipedia.org/wiki/Comb_sort#Python_code
        if (!valuesToSort.empty()) {
            int size = valuesToSort.size();
            int gap = size;

            bool didSwapHappened(true);
            while (didSwapHappened || gap > 1) {
                didSwapHappened = false;
                gap = getNextGapValue(gap);
                for (int i = 0; i < size - gap; i++) {                    if (valuesToSort[i] > valuesToSort[i + gap]) {
                        didSwapHappened = true;
                        std::swap(valuesToSort[i], valuesToSort[i + gap]);
                    }
                }
            }
        }
    }

private:
    int getNextGapValue(int const gap) const {
        // gap = floor(gap / shrink)
        int result = (gap * 10) / 13;  // apply shrink factor=1.3
        return mathHelper::clampLowerBound(result, 1);
    }
};

}  // namespace algorithm

}  // namespace alba

// Comb Sort is mainly an improvement over Bubble Sort. Bubble sort always compares adjacent values.
// So all inversions are removed one by one.
// Comb Sort improves on Bubble Sort by using gap of size more than 1.
// The gap starts with a large value and shrinks by a factor of 1.3 in every iteration until it reaches the value 1.
// Thus Comb Sort removes more than one inversion counts with one swap and performs better than Bubble Sort.

// The shrink factor has been empirically found to be 1.3 (by testing Combsort on over 200,000 random lists) [Source:
// Wikipedia] Although, it works better than Bubble Sort on average, worst case remains O(n2).

// Illustration:
// Let the array elements be
// 8, 4, 1, 56, 3, -44, 23, -6, 28, 0

// Initially gap value = 10
// After shrinking gap value => 10/1.3 = 7;
// 8 4 1 56 3 -44 23 -6 28 0
// -6 4 1 56 3 -44 23  8 28 0
// -6 4 0 56 3 -44 23  8 28 1

// New gap value => 7/1.3 = 5;
// -44 4 0 56 3 -6 23 8 28 1
// -44 4 0 28 3 -6 23 8 56 1
// -44 4 0 28 1 -6 23 8 56 3

// New gap value => 5/1.3 = 3;
// -44 1  0 28 4 -6 23 8 56 3
// -44 1 -6 28 4  0 23 8 56 3
// -44 1 -6 23 4  0 28 8 56 3
// -44 1 -6 23 4  0  3 8 56 28

// New gap value => 3/1.3 = 2;
// -44 1 -6 0 4 23 3 8 56 28
// -44 1 -6 0 3 23 4 8 56 28
// -44 1 -6 0 3 8 4 23 56 28

// New gap value => 2/1.3 = 1;
// -44 -6 1 0 3 8 4 23 56 28
// -44 -6 0 1 3 8 4 23 56 28
// -44 -6 0 1 3 4 8 23 56 28
// -44 -6 0 1 3 4 8 23 28 56
// no more swaps required (Array sorted)

// Time Complexity: Average case time complexity of the algorithm is Ω(N2/2p), where p is the number of increments.
// The worst-case complexity of this algorithm is O(n2) and the Best Case complexity is O(nlogn).
// Auxiliary Space : O(1).
