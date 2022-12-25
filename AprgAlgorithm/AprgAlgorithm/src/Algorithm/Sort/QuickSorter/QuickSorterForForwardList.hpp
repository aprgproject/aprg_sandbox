#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/QuickSorter/QuickSorterUtilities.hpp>

#include <forward_list>

namespace alba
{

namespace algorithm
{

template <typename Value>
class QuickSorterForForwardList : public BaseSorter<std::forward_list<Value>>
{
public:
    using Values = std::forward_list<Value>;
    using Iterator = typename Values::iterator;

    QuickSorterForForwardList() = default;

    void sort(Values & valuesToSort) const override
    {
        if(!valuesToSort.empty())
        {
            // You can randomize inputs here to remove dependence on input (quick sort works best if input is not sorted)
            // std::shuffle should help
            sort(valuesToSort, valuesToSort.begin(), valuesToSort.end());
        }
    }

private:
    void sort(
            Values & valuesToSort,
            Iterator const lowestIt,
            Iterator const highestItPlusOne) const // half open
    {
        Iterator partitionIt = partitionAndGetPartitionIteratorInOneDirection<Values>(lowestIt, highestItPlusOne);
        Iterator partitionItPlusOne = std::next(partitionIt, 1U);
        if(lowestIt!=partitionIt && lowestIt!=partitionItPlusOne) // size must be at least two
        {
            sort(valuesToSort, lowestIt, partitionIt); // recursively sort/partition the low part without the partitionIt
        }
        if(partitionIt!=highestItPlusOne && partitionItPlusOne!=highestItPlusOne) // size must be at least two
        {
            sort(valuesToSort, partitionItPlusOne, highestItPlusOne); // recursively sort/partition the high part without the partitionIt
        }
    }
};

}

}


