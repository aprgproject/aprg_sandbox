#pragma once

#include <Algorithm/Sort/QuickSorter/QuickSorterUtilities.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class QuickSelector {
public:
    using Value = typename Values::value_type;

    QuickSelector(PivotType const pivotType) : m_pivotType(pivotType) {}

    Value getNthSelect(Values& valuesToSort, unsigned int const selectionIndex) const {
        doNthElement(valuesToSort, selectionIndex);
        return valuesToSort.at(selectionIndex);
    }

    void doNthElement(Values& valuesToSort, unsigned int const selectionIndex) const {
        unsigned int lowest = 0, highest = valuesToSort.size() - 1;
        while (highest > lowest) {
            unsigned int partitionIndex = partitionAndGetPartitionIndex(valuesToSort, lowest, highest, m_pivotType);

            // move lowest or highest to the partition where selectionIndex is
            if (partitionIndex < selectionIndex) {
                lowest = partitionIndex + 1;
            } else if (selectionIndex < partitionIndex) {
                highest = partitionIndex - 1;
            } else {
                break;
            }
        }
    }

private:
    PivotType m_pivotType;
};

}  // namespace algorithm

}  // namespace alba

// Proposition: Quick select takes linear time on average.
// Proof sketch: Intuitively, each partitioning step splits array approximately in half.
// N + (N/2) + (N/4) + .... + 1 ~ 2N compares.
// On average, it is split in half but on worst case its (1/2)*N^2 compares, initial random suffle provides a
// probabilistic guarantee. In 1973, Blum Floyd Pratt Rivest Tarjan developed a selection algorithm whose worst-case
// running time is linear. But construction are too high => not used in practice.

// Other discussions:

// Problem: K’th Smallest/Largest Element in Unsorted Array
// -> Given an array and a number k where k is smaller than the size of the array, we need to find the k’th smallest
// element in the given array.
// -> It is given that all array elements are distinct.

// In QuickSort, we pick a pivot element, then move the pivot element to its correct position and partition the
// surrounding array. The idea in QuickSelect is not to do complete quicksort, but stop at the point where pivot itself
// is k’th smallest element. Also, not to recur for both left and right sides of pivot, but recur for one of them
// according to the position of pivot. The worst case time complexity of this method is O(n2), but it works in O(n) on
// average.

// A improvement idea is to randomly pick a pivot element.
// However, the worst case time complexity of the above solution is still O(n2).
// In the worst case, the randomized function may always pick a corner element.
// The assumption in the analysis is, random number generator is equally likely to generate any number in the input
// range.
