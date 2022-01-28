#pragma once

#include <Sorter/BaseSorter.hpp>

#include <utility>

namespace alba
{

template <typename Values>
class QuickSorter : public BaseSorter<Values>
{
public:
    void sort(Values & valuesToSort) const override
    {
        // You can randomize inputs here to remove dependence on input (quick sort works best if input is not sorted)
        sort(valuesToSort, 0U, valuesToSort.size()-1);
    }

private:
    void sort(
            Values & valuesToSort,
            unsigned int const low,
            unsigned int const high) const
    {
        if(low < high)
        {
            unsigned int partitionIndex = partitionAndGetPartitionIndex(valuesToSort, low, high);
            if(low != partitionIndex)
            {
                sort(valuesToSort, low, partitionIndex-1);
            }
            if(high != partitionIndex)
            {
                sort(valuesToSort, partitionIndex+1, high);
            }
        }
    }

    unsigned int partitionAndGetPartitionIndex(
            Values & valuesToSort,
            unsigned int const low,
            unsigned int const high) const
    {
        unsigned int i=low, j=high+1;
        auto partitionValue(valuesToSort.at(low)); // use first item as the partition value
        while(true)
        {
            while(valuesToSort.at(++i) < partitionValue)
            {
                if(i == high)
                {
                    break;
                }
            }
            while(partitionValue < valuesToSort.at(--j))
            {
                if(j == low)
                {
                    break;
                }
            }
            if(i >= j)
            {
                break;
            }
            std::swap(valuesToSort[i], valuesToSort[j]);
        }
        std::swap(valuesToSort[low], valuesToSort[j]);
        return j;
    }
};

}
