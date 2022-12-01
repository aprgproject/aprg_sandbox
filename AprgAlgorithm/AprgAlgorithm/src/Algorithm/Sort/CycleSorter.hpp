#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class CycleSorter : public BaseSorter<Values>
{
public:
    using Value = typename Values::value_type;

    CycleSorter() = default;

    void sort(Values & valuesToSort) const override
    {
        unsigned int numberOfWrites(0U);

        // traverse array elements and put it to on
        // the right place
        for (unsigned int cycleStartingPoint = 0; cycleStartingPoint+2U <= valuesToSort.size(); cycleStartingPoint++)
        {

            Value value = valuesToSort.at(cycleStartingPoint); // initialize item as starting point

            // Find position where we put the item. We basically count all smaller elements on right side of item.
            unsigned int position = cycleStartingPoint;
            for (unsigned int i = cycleStartingPoint+1U; i<valuesToSort.size(); i++)
            {
                if (valuesToSort.at(i) < value)
                {
                    position++;
                }
            }

            if (position == cycleStartingPoint) // If item is already in correct position
            {
                continue;
            }

            // ignore all duplicate  elements
            while (value == valuesToSort.at(position))
            {
                position++;
            }

            // put the item to it's right position
            if (position != cycleStartingPoint)
            {
                std::swap(value, valuesToSort.at(position));
                numberOfWrites++;
            }

            // Rotate rest of the cycle
            while (position != cycleStartingPoint)
            {
                position = cycleStartingPoint;

                // Find position where we put the element
                for (unsigned int i = cycleStartingPoint + 1; i < valuesToSort.size(); i++)
                {
                    position += (valuesToSort.at(i) < value) ? 1U : 0U;
                }

                // ignore all duplicate  elements
                while (value == valuesToSort.at(position))
                {
                    position++;
                }

                // put the item to it's right position
                if (value != valuesToSort.at(position))
                {
                    std::swap(value, valuesToSort[position]);
                    numberOfWrites++;
                }
            }
        }
    }
};

}

}


// Cycle sort is an in-place sorting Algorithm, unstable sorting algorithm,
// a comparison sort that is theoretically optimal in terms of the total number of writes to the original array.

// It is optimal in terms of number of memory writes.
// It minimizes the number of memory writes to sort (Each value is either written zero times,
// if it’s already in its correct position, or written one time to its correct position.)
// It is based on the idea that array to be sorted can be divided into cycles.
// We have n nodes and an edge directed from node i to node j if the element at i-th index must be present at j-th index in the sorted array.

// We one by one consider all cycles.
// We first consider the cycle that includes first element.
// We find correct position of first element, place it at its correct position, say j.
// We consider old value of arr[j] and find its correct position,
// we keep doing this till all elements of current cycle are placed at correct position, i.e., we don’t come back to cycle starting point.

// Explanation :
// arr[] = {10, 5, 2, 3}
// index =  0   1   2   3
// cycle_start = 0
// item = 10 = arr[0]

// Find position where we put the item
// pos = cycle_start
// i=pos+1
// while(i<n)
// if (arr[i] < item)
//    pos++;

// We put 10 at arr[3] and change item to old value of arr[3].
// arr[] = {10, 5, 2, 10}
// item = 3

// Again rotate rest cycle that start with index '0'
// Find position where we put the item = 3
// we swap item with element at arr[1] now
// arr[] = {10, 3, 2, 10}
// item = 5

// Again rotate rest cycle that start with index '0' and item = 5
// we swap item with element at arr[2].
// arr[] = {10, 3, 5, 10 }
// item = 2

// Again rotate rest cycle that start with index '0' and item = 2
// arr[] = {2, 3,  5, 10}

// Above is one iteration for cycle_stat = 0.
// Repeat above steps for cycle_start = 1, 2, ..n-2

// Time Complexity : O(n2)
// Worst Case : O(n2)
// Average Case: O(n2)
// Best Case : O(n2)
// This sorting algorithm is best suited for situations where memory write or swap operations are costly.

