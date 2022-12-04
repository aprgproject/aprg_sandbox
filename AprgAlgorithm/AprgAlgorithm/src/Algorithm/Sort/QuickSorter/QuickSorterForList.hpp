#pragma once

#include <Algorithm/Sort/BaseSorter.hpp>
#include <Algorithm/Sort/QuickSorter/QuickSorterUtilities.hpp>

#include <list>

namespace alba
{

namespace algorithm
{

template <typename Value>
class QuickSorterForList : public BaseSorter<std::list<Value>>
{
public:
    using Values = std::list<Value>;
    using Iterator = typename Values::iterator;

    QuickSorterForList() = default;

    void sort(Values & valuesToSort) const override
    {
        if(!valuesToSort.empty())
        {
            // You can randomize inputs here to remove dependence on input (quick sort works best if input is not sorted)
            // std::shuffle should help
            Iterator itLast = valuesToSort.end();
            itLast--;
            sort(valuesToSort, valuesToSort.begin(), itLast);
        }
    }

private:
    void sort(
            Values & valuesToSort,
            Iterator const lowestIt,
            Iterator const highestIt) const
    {
        Iterator partitionIt = partitionAndGetPartitionIteratorInTwoDirections<Values>(lowestIt, highestIt);
        Iterator partitionItMinusOne = partitionIt;
        Iterator partitionItPlusOne = partitionIt;
        partitionItMinusOne--;
        partitionItPlusOne++;
        if(lowestIt != partitionIt && lowestIt != partitionItMinusOne) // size must be at least two
        {
            sort(valuesToSort, lowestIt, partitionItMinusOne); // recursively sort/partition the low part without the partitionIt
        }
        if(partitionIt != highestIt && partitionItPlusOne != highestIt) // size must be at least two
        {
            sort(valuesToSort, partitionItPlusOne, highestIt); // recursively sort/partition the high part without the partitionIt
        }
    }
};

}

}


