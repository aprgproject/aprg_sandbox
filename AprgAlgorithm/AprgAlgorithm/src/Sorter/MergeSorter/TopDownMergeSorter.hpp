#pragma once

#include <Sorter/MergeSorter/MergeSorterUtilities.hpp>

namespace alba
{

template <typename Values>
class TopDownMergeSorter
{
public:
    void sort(Values & valuesToSort) const
    {
        if(!valuesToSort.empty())
        {
            Values temp(valuesToSort);
            sort(valuesToSort, temp, 0, valuesToSort.size()-1);
        }
    }

    void sort(
            Values & valuesToSort,
            Values & temp,
            unsigned int const low,
            unsigned int const high) const
    {
        if(low < high)
        {
            unsigned int const mid = (low + high)/2;
            sort(valuesToSort, temp, low, mid);
            sort(valuesToSort, temp, mid+1, high);
            mergeTwoSortedSequences(valuesToSort, temp, low, mid, high);
        }
    }
};

}
