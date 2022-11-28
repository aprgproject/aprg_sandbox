#pragma once

#include <Algorithm/Sort/QuickSorter/QuickSorterUtilities.hpp>

#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class QuickSelector
{
public:
    using Value = typename Values::value_type;

    QuickSelector() = default;

    Value getNthSelect(Values & valuesToSort, unsigned int const selectionIndex) const
    {        doNthElement(valuesToSort, selectionIndex);
        return valuesToSort.at(selectionIndex);
    }

    void doNthElement(Values & valuesToSort, unsigned int const selectionIndex) const
    {
        unsigned int lowest=0, highest=valuesToSort.size()-1;
        while(highest > lowest)
        {
            unsigned int partitionIndex = partitionAndGetPartitionIndex(valuesToSort, lowest, highest);
            if(partitionIndex < selectionIndex)
            {
                lowest = partitionIndex+1;
            }
            else if(partitionIndex > selectionIndex)
            {
                highest = partitionIndex-1;
            }
            else
            {
                break;
            }
        }
    }
};

}

}

// Proposition: Quick select takes linear time on average.
// Proof sketch: Intuitively, each partitioning step splits array approximately in half.
// N + (N/2) + (N/4) + .... + 1 ~ 2N compares.
// On average, it is split in half but on worst case its (1/2)*N^2 compares, initial random suffle provides a probabilistic guarantee.
// In 1973, Blum Floyd Pratt Rivest Tarjan developed a selection algorithm whose worst-case running time is linear.
// But construction are too high => not used in practice.

