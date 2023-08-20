#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/QuickSorter/QuickSorterUtilities.hpp>

#include <list>

namespace alba {

namespace algorithm {

template <typename Value>
class QuickSorterForList : public BaseSorter<std::list<Value>> {
public:
    using Values = std::list<Value>;
    using Iterator = typename Values::iterator;

    QuickSorterForList() = default;

    void sort(Values& valuesToSort) const override {
        if (!valuesToSort.empty() && valuesToSort.size() != 1) {
            // You can randomize inputs here to remove dependence on input (quick sort works best if input is not
            // sorted) std::shuffle should help
            Iterator itLast = prev(valuesToSort.end());
            sort(valuesToSort, valuesToSort.begin(), itLast);
        }
    }

private:
    void sort(Values& valuesToSort, Iterator const itLow, Iterator const itHigh) const {
        Iterator partitionIt = partitionAndGetPartitionIteratorInTwoDirections<Values>(itLow, itHigh);
        if (partitionIt != valuesToSort.begin()) {
            Iterator partitionItMinusOne = prev(partitionIt);
            if (itLow != partitionIt && itLow != partitionItMinusOne) {  // size must be at least two
                // recursively sort/partition the low part without the partitionIt
                sort(valuesToSort, itLow, partitionItMinusOne);
            }
        }
        Iterator partitionItPlusOne = next(partitionIt);
        if (partitionIt != itHigh && partitionItPlusOne != itHigh) {  // size must be at least two
            // recursively sort/partition the high part without the partitionIt
            sort(valuesToSort, partitionItPlusOne, itHigh);
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// Time Complexity: Time complexity of the above implementation is same as time complexity of QuickSort() for arrays.
// -> It takes O(n^2) time in the worst case and O(nLogn) in average and best cases.
// -> The worst case occurs when the linked list is already sorted.

// Can we implement random quicksort for a linked list?
// -> Quicksort can be implemented for Linked List only when we can pick a fixed point as the pivot (like the first or
// last element).
// -> Random QuickSort cannot be efficiently implemented for Linked Lists by picking random pivot.
