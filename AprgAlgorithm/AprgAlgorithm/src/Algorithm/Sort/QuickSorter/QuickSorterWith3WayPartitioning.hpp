#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class QuickSorterWith3WayPartitioning : public BaseSorter<Values>
{
public:

    QuickSorterWith3WayPartitioning() = default;

    void sort(Values & valuesToSort) const override
    {
        if(!valuesToSort.empty())
        {
            // You can randomize inputs here to remove dependence on input (quick sort works best if input is not sorted)
            sort(valuesToSort, 0U, valuesToSort.size()-1);
        }
    }

private:
    void sort(
            Values & valuesToSort,
            unsigned int const lowest,
            unsigned int const highest) const
    {
        if(lowest < highest)
        {
            unsigned int boundaryIndexForLessThan = lowest, i = lowest+1, boundaryIndexForGreaterThan = highest;
            auto partitionValue(valuesToSort.at(lowest));
            while(i <= boundaryIndexForGreaterThan) //i moves within the boundaries
            {
                if(valuesToSort.at(i) < partitionValue)
                {
                    // swap so that elements that are less than are kept to the left of boundaryIndexForLessThan
                    std::swap(valuesToSort[boundaryIndexForLessThan++], valuesToSort[i++]); // i is moved here as well (to keep i within the boundary)
                }
                else if(partitionValue < valuesToSort.at(i))
                {
                    // swap so that elements that are greater than are kept to the right of boundaryIndexForGreaterThan
                    std::swap(valuesToSort[i], valuesToSort[boundaryIndexForGreaterThan--]);
                }
                else
                {
                    i++; // equal to partition value so just move to the next item
                }
            }
            if(boundaryIndexForLessThan > 0) // prevent negative index            {
                sort(valuesToSort, lowest, boundaryIndexForLessThan-1); // sort items that are less than the partitionValue
            }
            sort(valuesToSort, boundaryIndexForGreaterThan+1, highest); // sort items that are greater than the partitionValue            // do nothing for items that are equal to the partitionValue
        }
    }
};

}

}

// The motivation of this algorithm is to handle items with duplicate keys more efficiently. (compared to original quick sort algorithm)
// Put the equal items in place and focus(sort/partition) on items that are not equal.
// This version of quicksort is still NOT STABLE.

// This algorithm runs by dividing the partition into 3 parts:
// 1) Values less than the partition value is on the left
// 2) Values greater than the partition value is on the right
// 3) Values equal to the partition value is between (1) and (2)

// This is proposed by Djisktra and he was interested in the correctness of programs.

// Worst case (Lower bound): When the keys are distinct so no need to divide the partition into 3 parts.
// What is interesting about this algorithm is that the number compares its using is equal to the lower bound within a constant factor.
// Proof: provided by Sedgewick-Bentley in 1997

// Bottom line is that randomized quicksort with 3-way partitioning reduces running time from linearithmic to linear in broad class of applications.

// Engineering a sort function -> paper by Jon L Bentley and M Douglass Mcllroy
// -> Cut off to insertion sort for small subarrays
// -> Partitioning scheme: 3-way partitioning (like Dijkstra)
// -> Partitioning item:
// ---> small arrays: middle entry
// ---> medium arrays: median of 3
// ---> large arrays: Tukey's ninther
// ------> Pick 9 items in the array (evenly spaced), get median of each 3 samples, get the median of that -> that is Tukey's ninther
// ---> Why Tukey's ninther? Inexpensive and gets close to the middle
// -> No random shuffle, so there is no change is the state of the system and less costly
// -> Now widely used: C C++ Java
// -> Solid right? NO! A killer input exists that causes a stack overflow and crashes the program and would take quadratic if if didnt crash.
// ---> This is because there is no shuffling done.
