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
        if (!valuesToSort.empty()) {
            // You can randomize inputs here to remove dependence on input (quick sort works best if input is not
            // sorted) std::shuffle should help
            Iterator itLast = valuesToSort.end();
            itLast--;
            sort(valuesToSort, valuesToSort.begin(), itLast);
        }
    }

private:
    void sort(Values& valuesToSort, Iterator const itLow, Iterator const itHigh) const {
        Iterator partitionIt = partitionAndGetPartitionIteratorInTwoDirections<Values>(itLow, itHigh);
        Iterator partitionItMinusOne = partitionIt;
        Iterator partitionItPlusOne = partitionIt;
        partitionItMinusOne--;
        partitionItPlusOne++;
        if (itLow != partitionIt && itLow != partitionItMinusOne) {  // size must be at least two
            // recursively sort/partition the low part without the partitionIt
            sort(valuesToSort, itLow, partitionItMinusOne);
        }
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
