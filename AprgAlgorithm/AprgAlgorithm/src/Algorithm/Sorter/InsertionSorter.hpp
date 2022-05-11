#pragma once

#include <Algorithm/Sorter/BaseSorter.hpp>

#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class InsertionSorter : public BaseSorter<Values>
{
public:

    void sort(Values & valuesToSort) const override
    {
        unsigned int const size = valuesToSort.size();
        for(unsigned int insertedIndex=1; insertedIndex<size; insertedIndex++)
        {
            continuouslySwapDownIfStillOutOfOrder(valuesToSort, insertedIndex);
        }
    }

private:
    void continuouslySwapDownIfStillOutOfOrder(Values& valuesToSort, unsigned int const startingIndex) const
    {
        for(unsigned int i=startingIndex; i>0 && valuesToSort.at(i-1) > valuesToSort.at(i); i--)
        {
            std::swap(valuesToSort[i], valuesToSort[i-1]);
        }
    }
};

// Proposition: To sort a randomly ordered array with distinct keys, insertion sort uses ~(1/4)N^2 compares and ~(1/4)N^2 exchanges on average.
// Proof: Expect each entry to move halfway back. Only half of the elements along the diagonal is involved in the sort.

// Insertion sort depends on the initial order of the data
// Best case: If the array is in ascending order, insertion sort makes N-1 compares and 0 exchanges.
// Worst case: If the array is in descending order (and no duplicates), insertion sort makes ~(1/2)N^2 compares and ~(1/2)N^2 exchanges.

// Proposition: For partially-sorted arrays, insertion sort runs in linear time.
// Proof: Number of exchanges equals the number of inversions.
// Number of compares = number of exchanges + N-1

// Stable -> Proof: Equal items never move past each other

}

}