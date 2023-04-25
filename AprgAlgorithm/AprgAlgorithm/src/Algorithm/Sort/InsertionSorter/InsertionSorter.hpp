#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <iterator>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Values>
class InsertionSorter : public BaseSorter<Values> {
public:
    using Iterator = typename Values::iterator;
    InsertionSorter() = default;

    void sort(Values& valuesToSort) const override {
        if (!valuesToSort.empty()) {
            auto insertIt = valuesToSort.begin();
            insertIt++;
            for (; insertIt != valuesToSort.end(); insertIt++) {
                continuouslySwapDownIfStillOutOfOrder(valuesToSort, insertIt);
            }
        }
    }

private:
    void continuouslySwapDownIfStillOutOfOrder(Values& valuesToSort, Iterator const insertIt) const {
        auto itHigh = std::make_reverse_iterator(
            insertIt);  // make_reverse_iterator advances it by one (so there is decrement after)
        auto itLow = itHigh;
        itHigh--;
        for (; itLow != valuesToSort.rend() && *itLow > *itHigh; itLow++, itHigh++) {
            std::swap(*itLow, *itHigh);
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// Proposition: To sort a randomly ordered array with distinct keys, insertion sort uses ~(1/4)N^2 compares and
// ~(1/4)N^2 exchanges on average. Proof: Expect each entry to move halfway back. Only half of the elements along the
// diagonal is involved in the sort.

// Insertion sort depends on the initial order of the data
// Best case: If the array is in ascending order, insertion sort makes N-1 compares and 0 exchanges.
// Worst case: If the array is in descending order (and no duplicates), insertion sort makes ~(1/2)N^2 compares and
// ~(1/2)N^2 exchanges.

// Proposition: For partially-sorted arrays, insertion sort runs in linear time.
// Proof: Number of exchanges equals the number of inversions.
// Number of compares = number of exchanges + N-1

// Stable -> Proof: Equal items never move past each other

// Other discussions:
// Insertion sort is a simple sorting algorithm that works similar to the way you sort playing cards in your hands.
// The array is virtually split into a sorted and an unsorted part.
// Values from the unsorted part are picked and placed at the correct position in the sorted part.
// Algorithm
// To sort an array of size n in ascending order:
// 1: Iterate from arr[1] to arr[n] over the array.
// 2: Compare the current element (key) to its predecessor.
// 3: If the key element is smaller than its predecessor, compare it to the elements before.
// -> Move the greater elements one position up to make space for the swapped element.

// Time Complexity: O(n^2)
// Auxiliary Space: O(1)
// Boundary Cases: Insertion sort takes maximum time to sort if elements are sorted in reverse order.
// And it takes minimum time (Order of n) when elements are already sorted.
// Algorithmic Paradigm: Incremental Approach
// Sorting In Place: Yes
// Stable: Yes
// Online: Yes
// Uses: Insertion sort is used when number of elements is small.
// It can also be useful when input array is almost sorted, only few elements are misplaced in complete big array.

// What is Binary Insertion Sort?
// We can use binary search to reduce the number of comparisons in normal insertion sort.
// Binary Insertion Sort uses binary search to find the proper location to insert the selected item at each iteration.
// In normal insertion, sorting takes O(i) (at ith iteration) in worst case.
// We can reduce it to O(log(i)) by using binary search.
// The algorithm, as a whole, still has a running worst case running time of O(n^2) because of the series of swaps
// required for each insertion.

// How to implement Insertion Sort for Linked List?
// Below is simple insertion sort algorithm for linked list.
// 1) Create an empty sorted (or result) list
// 2) Traverse the given list, do following for every node.
// -> 2.a) Insert current node in sorted way in sorted/result list.
// 3) Change head of given linked list to head of sorted (or result) list.
