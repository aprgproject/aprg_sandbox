#pragma once

#include <Algorithm/Sorter/BaseSorter.hpp>
#include <Algorithm/Sorter/MergeSorter/MergeSorterUtilities.hpp>

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
        Values auxiliary(valuesToSort);
        unsigned int const size = valuesToSort.size();
        for(unsigned int sizeToSort=1; sizeToSort<size; sizeToSort+=sizeToSort)
        {
            for(unsigned int lowest=0; lowest < size-sizeToSort; lowest+=2*sizeToSort)
            {
                unsigned int middle = lowest+sizeToSort-1;
                unsigned int highest = std::min(lowest+(2*sizeToSort)-1, size-1);
                mergeTheTwoSortedParts(valuesToSort, auxiliary, lowest, middle, highest);
            }
        }
    }

    // No recursion approach
    // Concise industrial-strength code, if you have the space

    // Takes N*log2(N) as well

    // Stable -> Proof: Merge sort is stable if the merge operation is stable.
    // Since the merge operation is stable (equal items never move past each other), then merge sort is stable.
};

}
}