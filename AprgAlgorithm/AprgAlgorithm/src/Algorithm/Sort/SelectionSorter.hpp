#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>

#include <algorithm>
#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class SelectionSorter : public BaseSorter<Values>
{
public:
    void sort(Values & valuesToSort) const override
    {
        unsigned int const size = valuesToSort.size();
        for(unsigned int indexToSwap=0; indexToSwap<size-1; indexToSwap++)
        {
            auto currentMinimumIt = std::min_element(valuesToSort.begin()+indexToSwap, valuesToSort.end());
            if(currentMinimumIt != valuesToSort.cend())
            {
                std::swap(valuesToSort[indexToSwap], *currentMinimumIt);
            }
        }
    }
};

}

}

// Proposition: Selection sort uses (N-1)+(N-2)+....+1+0 = (N^2)/2 compares and N exchanges
// Proof: Trace the algorithm, double loop only happens for compare (second loop only covers not yet processed items)
// and single loop happens in swapping the elements

// The running time insensitive to input: Quadratic time, even if input is sorted
// Data movement is minimal: Linear number of exchanges

// Not stable -> Proof by counter example: Long distance swap might move an item past some equal item



// Other discussions:
// The selection sort algorithm sorts an array by repeatedly finding the minimum element (considering ascending order)
// from unsorted part and putting it at the beginning.
// The algorithm maintains two subarrays in a given array.
// 1) The subarray which is already sorted.
// 2) Remaining subarray which is unsorted.
// In every iteration of selection sort, the minimum element (considering ascending order)
// from the unsorted subarray is picked and moved to the sorted subarray.
