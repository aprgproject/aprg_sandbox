#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/MergeSorter/MergeSorterUtilities.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values, typename ArrayOfCountPerValue>
class CountingSorter : public BaseSorter<Values>
{

public:
    void sort(Values & valuesToSort) const override
    {
        ArrayOfCountPerValue countPerValue{}; // important to initialize to zero
        for(auto const& value : valuesToSort)
        {
            countPerValue[value]++; // count each value
        }
        unsigned int k=0;
        for(unsigned int i=0; i<countPerValue.size(); i++)
        {
            for(unsigned int j=0; j<countPerValue.at(i); j++)
            {
                valuesToSort[k++] = i; // put the index multiple times depending on the count
            }
        }
    }
};

// This is a linear algorithm
// This algorithm depends on values as indices so the max value corresponds to the space cost

}

}
