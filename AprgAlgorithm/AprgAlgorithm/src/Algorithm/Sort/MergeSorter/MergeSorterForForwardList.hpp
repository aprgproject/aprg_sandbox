#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <forward_list>

namespace alba
{

namespace algorithm
{

template <typename Value>
class MergeSorterForForwardList : public BaseSorter<std::forward_list<Value>>
{
public:
    using Values = std::forward_list<Value>;
    using Iterator = typename Values::iterator;
    using ConstIterator = typename Values::const_iterator;

    MergeSorterForForwardList() = default;

    void sort(Values & valuesToSort) const override
    {
        valuesToSort = getSortedValues(valuesToSort);
    }

private:

    Values getSortedValues(
            Values const& unsortedValues) const
    {
        ConstIterator middle = getMiddleIterator(unsortedValues);
        if(middle == unsortedValues.cend())
        {
            return unsortedValues;
        }
        else
        {
            // Split to two parts
            Values firstPart, secondPart; // THIS IS COSTLY, in a more controllable forward link list we can split it more easily
            Iterator itNewFirstPart=firstPart.before_begin(), itNewSecondPart=secondPart.before_begin();
            for(ConstIterator it=unsortedValues.cbegin(); it!=middle; it++)
            {
                itNewFirstPart = firstPart.emplace_after(itNewFirstPart, *it);
            }
            for(ConstIterator it=middle; it!=unsortedValues.cend(); it++)
            {
                itNewSecondPart = secondPart.emplace_after(itNewSecondPart, *it);
            }

            return mergeTwoRanges(getSortedValues(firstPart), getSortedValues(secondPart)); // this is top down merge sort
        }
    }

    ConstIterator getMiddleIterator(Values const& values) const
    {
        ConstIterator turtoise(values.cbegin());
        ConstIterator hare(values.cbegin());
        while(hare!=values.cend())
        {
            // std::advance with 2 for hare? no, because we need to check if we exceeded
            turtoise++;
            hare++;
            if(hare!=values.cend())            {
                hare++;
            }
        }        return turtoise;
    }

    Values mergeTwoRanges(
            Values const& firstPart,
            Values const& secondPart) const
    {
        // this is similar with std::forward_list::merge

        Values result;
        Iterator itNewValue=result.before_begin();
        ConstIterator it1=firstPart.cbegin(), it2=secondPart.cbegin();
        for(; it1!=firstPart.cend() && it2!=secondPart.cend(); )
        {
            if(*it1 <= *it2)
            {
                itNewValue = result.emplace_after(itNewValue, *it1);
                it1++;
            }
            else
            {
                itNewValue = result.emplace_after(itNewValue, *it2);
                it2++;
            }
        }
        for(; it1!=firstPart.cend(); it1++)
        {
            itNewValue = result.emplace_after(itNewValue, *it1);
        }
        for(; it2!=secondPart.cend(); it2++)
        {
            itNewValue = result.emplace_after(itNewValue, *it2);
        }
        return result;
    }
};

}

}

// Merge sort is often preferred for sorting a linked list.
// The slow random-access performance of a linked list makes some other algorithms (such as quicksort) perform poorly,
// and others (such as heapsort) completely impossible.

// Approach 2: This approach is simpler and uses log n space.

// mergeSort():
// -> If the size of the linked list is 1 then return the head
// -> Find mid using The Tortoise and The Hare Approach
// -> Store the next of mid in head2 i.e. the right sub-linked list.
// -> Now Make the next midpoint null.
// -> Recursively call mergeSort() on both left and right sub-linked list and store the new head of the left and right linked list.
// -> Call merge() given the arguments new heads of left and right sub-linked lists and store the final head returned after merging.
// -> Return the final head of the merged linkedlist.

// merge(head1, head2):
// -> Take a pointer say merged to store the merged list in it and store a dummy node in it.
// -> Take a pointer temp and assign merge to it.
// -> Else store head2 in next of temp & move head2 to the next of head2.
// -> Move temp to the next of temp.
// -> Repeat steps 3, 4 & 5 until head1 is not equal to null and head2 is not equal to null.
// -> Now add any remaining nodes of the first or the second linked list to the merged linked list.
// -> Return the next of merged(that will ignore the dummy and return the head of the final merged linked list)

// Time Complexity: O(n*log n)
// Auxiliary Space Complexity: O(log n)



