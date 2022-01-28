#pragma once

#include <Sorter/BaseSorter.hpp>

#include <utility>

namespace alba
{

template <typename Values>
class QuickSorterWith3WayPartitioning : public BaseSorter<Values>
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
            unsigned int indexForLessThan = low, i = low+1, indexForGreaterThan = high;
            auto partitionValue(valuesToSort.at(low));
            while(i <= indexForGreaterThan)
            {
                if(valuesToSort.at(i) < partitionValue)
                {
                    std::swap(valuesToSort[indexForLessThan++], valuesToSort[i]);
                }
                else if(valuesToSort.at(i) > partitionValue)
                {
                    std::swap(valuesToSort[i], valuesToSort[indexForGreaterThan--]);
                }
                else
                {
                    i++;
                }
            }
            if(low != indexForLessThan)
            {
                sort(valuesToSort, low, indexForLessThan-1);
            }
            if(high != indexForGreaterThan)
            {
                sort(valuesToSort, indexForGreaterThan+1, high);
            }
        }
    }
};

}
