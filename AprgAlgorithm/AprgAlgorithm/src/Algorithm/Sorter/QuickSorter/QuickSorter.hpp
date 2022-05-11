#pragma once

#include <Algorithm/Sorter/BaseSorter.hpp>
#include <Algorithm/Sorter/QuickSorter/QuickSorterUtilities.hpp>

#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class QuickSorter : public BaseSorter<Values>
{
public:
    void sort(Values & valuesToSort) const override
    {
        // You can randomize inputs here to remove dependence on input (quick sort works best if input is not sorted)
        // std::shuffle should help
        sort(valuesToSort, 0U, valuesToSort.size()-1);
    }

private:
    void sort(
            Values & valuesToSort,
            unsigned int const lowestIndex,
            unsigned int const highestIndex) const
    {
        if(lowestIndex < highestIndex)
        {
            unsigned int partitionIndex = partitionAndGetPartitionIndex(valuesToSort, lowestIndex, highestIndex);
            if(lowestIndex != partitionIndex)
            {
                sort(valuesToSort, lowestIndex, partitionIndex-1); // recursively sort/partition the low part without the parition index
            }
            if(highestIndex != partitionIndex)
            {
                sort(valuesToSort, partitionIndex+1, highestIndex); // recursively sort/partition the high part without the parition index
            }
        }
    }
};

// Quicksort is an in-place sorting algorithm
// Quicksort does partitioning in place so there is no extra cost of memory for sorting
// Having some extra memory can make quick sort stable (but its not worth the cost)

// Quicksort is faster than merge sort -> Lesson 2 : Great algorithms are better than good ones.

// Proposition: The average number of compares CN to quicksort an array of N distinct keys is 2N*ln(N) and the number of exchanges is (1/3)N*ln(N).
// Proof: Check for recurrence

// Best case: Partitions split at the middle and continuously divide the problem by half. The running time its ~N*log2(N)
// Worst case: Partitions are in the edge so it continuous divide the problem one element at a time. The running time is about (1/2)N^2
// At worst case, quick sort is quadratic. But having an initial random shuffle makes this really unlikely (lightning bolt odds).
// At average case, quicksort has 39% more compares (1.39 N*log2(N)), but still faster because of less data movement.

// The initial random shuffle provides probabilistic guarantee against the worst case.
// It also provides the basis for a math model that can be validated with experiments (because probability of the partition can be computed).

// Not stable -> Proof by counter example: Long distance swap might move an item past some equal item

// Practical improvements:
// -> Cut off to insertion sort when the subarrays becomes too small (~10 items). It can improve the running time ~20%. Not implemented above.
// -> Stop at small arrays and do one insertion sort at the end. Not implemented above.
// -> Use the median as the partition value. Not worth it for large sample but median of 3 is worth it.
// ---> Median of 3 means gets the median at lowest, middle and highest index. Sorting these 3 indexes also help next partitions.
// ---> It can improve the running time ~10%. Not implemented above.

// Duplicate keys:
// -> Runs in quadratic time if all equal elements are put on one side (not splitted properly).
// ---> Consequence is that partitions with equal items are reduced one by one (instead of halving the partition on average)
// ---> In the implementation above, divides the items on the middle as much as possible even if there are equal keys.
// ---> In 1990s, a C user found this defect on quick sort implementation in C (quadratic time for large files with equal keys)
// -----> This problematic algorithm is the standard found in a lot of text books.
// ---> Why dont we put all the equal items in place in the middle and process other items -> This is quick sort with 3 way partitioning.

}

}