#pragma once

#include <Algorithm/Sorter/MergeSorter/MergeSorterUtilities.hpp>
#include <Algorithm/Sorter/BaseSorter.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class BottomUpMergeSorter : public BaseSorter<Values>
{

public:
    void sort(Values & valuesToSort) const override
    {
        Values temp(valuesToSort);
        unsigned int const size = valuesToSort.size();
        for(unsigned int sizeToSort=1; sizeToSort<size; sizeToSort+=sizeToSort)
        {
            for(unsigned int low=0; low < size-sizeToSort; low+=2*sizeToSort)
            {
                unsigned int high = std::min(low+(2*sizeToSort)-1, size-1);
                mergeTwoSortedSequences(valuesToSort, temp, low, low+sizeToSort-1, high);
            }

        }
    }
};

}

}