#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class BubbleSorter : public BaseSorter<Values> {
public:
    BubbleSorter() = default;

    void sort(Values& valuesToSort) const override {
        if (!valuesToSort.empty()) {
            auto itStop = valuesToSort.begin();
            itStop++;
            for (auto itEnd = valuesToSort.end(); itStop != itEnd; itEnd--) {
                bool noSwapHappened(true);
                auto itFirst = valuesToSort.begin();
                auto itSecond = valuesToSort.begin();
                itSecond++;
                for (; itSecond != itEnd; itFirst++, itSecond++) {
                    if (*itSecond < *itFirst) {
                        std::swap(*itFirst, *itSecond);
                        noSwapHappened = false;
                    }
                }
                if (noSwapHappened) {
                    break;
                }
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// Bubble Sort is the simplest sorting algorithm that works by repeatedly swapping the adjacent elements if they are in
// wrong order.

// Optimized Implementation:
// The above function always runs O(n^2) time even if the array is sorted.
// It can be optimized by stopping the algorithm if inner loop didn’t cause any swap.

// Worst and Average Case Time Complexity: O(n^2). (should be not Oh)
// Worst case occurs when array is reverse sorted.
// Best Case Time Complexity: O(n) (should be not Oh). Best case occurs when array is already sorted.
// Auxiliary Space: O(1)
// Boundary Cases: Bubble sort takes minimum time (Order of n) when elements are already sorted.
// Sorting In Place: Yes
// Stable: Yes

// Due to its simplicity, bubble sort is often used to introduce the concept of a sorting algorithm.
// In computer graphics it is popular for its capability to detect a very small error (like swap of just two elements)
// in almost-sorted arrays and fix it with just linear complexity (2n).
// For example, it is used in a polygon filling algorithm,
// where bounding lines are sorted by their x coordinate at a specific scan line (a line parallel to x axis)
// and with incrementing y their order changes (two elements are swapped) only at intersections of two lines.
