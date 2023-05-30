#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <forward_list>

namespace alba {

namespace algorithm {

template <typename Value>
class MergeSorterForForwardList : public BaseSorter<std::forward_list<Value>> {
public:
    using Values = std::forward_list<Value>;
    using Iterator = typename Values::iterator;
    using ConstIterator = typename Values::const_iterator;

    MergeSorterForForwardList() = default;

    void sort(Values& valuesToSort) const override { sortFromTheTopDown(valuesToSort); }

private:
    void sortFromTheTopDown(Values& values) const {
        // list contains one or empty stop
        if (values.begin() != values.cend() && std::next(values.begin()) != values.cend()) {
            // Split to two parts
            Values& firstPart(values);
            Values secondPart;
            ConstIterator beforeMiddle = getBeforeMiddleIterator(values);

            secondPart.splice_after(secondPart.cbefore_begin(), firstPart, beforeMiddle, firstPart.cend());

            // this is top down merge sort
            sortFromTheTopDown(firstPart);
            sortFromTheTopDown(secondPart);
            mergeTwoRanges(values, firstPart, secondPart);
        }
    }

    ConstIterator getBeforeMiddleIterator(Values const& values) const {
        ConstIterator turtoise(values.cbefore_begin());
        ConstIterator hare(values.cbegin());
        while (hare != values.cend()) {
            // std::advance with 2 for hare? no, because we need to check if we exceeded
            ++hare;
            ++turtoise;
            if (hare != values.cend()) {
                ++hare;
            }        }
        return turtoise;
    }

    void mergeTwoRanges(Values& result, Values& firstPart, Values& secondPart) const {
        // this is similar with std::forward_list::merge

        Values merged;
        ConstIterator itMerged = merged.cbefore_begin();
        for (; firstPart.cbegin() != firstPart.cend() && secondPart.cbegin() != secondPart.cend(); ++itMerged) {
            if (firstPart.front() <= secondPart.front()) {
                merged.splice_after(itMerged, firstPart, firstPart.cbefore_begin());
            } else {
                merged.splice_after(itMerged, secondPart, secondPart.cbefore_begin());
            }
        }
        // copy remaining from first part
        merged.splice_after(itMerged, firstPart);
        // copy remaining from second part
        merged.splice_after(itMerged, secondPart);

        result = std::move(merged);
    }
};
}  // namespace algorithm

}  // namespace alba
// Merge sort is often preferred for sorting a linked list.
// The slow random-access performance of a linked list makes some other algorithms (such as quicksort) perform poorly,
// and others (such as heapsort) completely impossible.

// Approach 2: This approach is simpler and uses log n space.

// mergeSort():
// -> If the size of the linked list is 1 then return the head
// -> Find mid using The Tortoise and The Hare Approach
// -> Store the next of mid in head2 i.e. the right sub-linked list.
// -> Now Make the next midpoint null.
// -> Recursively call mergeSort() on both left and right sub-linked list and store the new head of the left and right
// linked list.
// -> Call merge() given the arguments new heads of left and right sub-linked lists and store the final head returned
// after merging.
// -> Return the final head of the merged linkedlist.

// merge(head1, head2):
// -> Take a pointer say merged to store the merged list in it and store a dummy node in it.
// -> Take a pointer temp and assign merge to it.
// -> Else store head2 in next of temp and move head2 to the next of head2.
// -> Move temp to the next of temp.
// -> Repeat steps 3, 4 and 5 until head1 is not equal to null and head2 is not equal to null.
// -> Now add any remaining nodes of the first or the second linked list to the merged linked list.
// -> Return the next of merged(that will ignore the dummy and return the head of the final merged linked list)

// Time Complexity: O(n*log n)
// Auxiliary Space Complexity: O(log n)
