#pragma once

#include <utility>

namespace alba
{

template <typename Values>
class HeapSorter
{
public:
    void sort(Values & valuesToSort) const
    {
        unsigned int size = valuesToSort.size();
        for(unsigned int treeIndex=size/2; treeIndex>=1; treeIndex--)
        {
            sink(valuesToSort, treeIndex, size);
        }
        while(size > 1)
        {
            std::swap(valuesToSort[0], valuesToSort[size-1]);
            size--;
            sink(valuesToSort, 1, size);
        }
    }

private:
    void sink(
            Values & valuesToSort,
            unsigned int const startTreeIndex,
            unsigned int const size) const
    {
        //Sink is "top down reheapify"
        unsigned int treeIndex(startTreeIndex);
        while(treeIndex*2 < size)
        {
            unsigned int doubleIndex(treeIndex*2);
            if(doubleIndex < size
                    && valuesToSort.at(doubleIndex-1) < valuesToSort.at(doubleIndex))
            {
                doubleIndex++;
            }
            if(valuesToSort.at(treeIndex-1) >= valuesToSort.at(doubleIndex-1))
            {
                break;
            }
            std::swap(valuesToSort[treeIndex-1], valuesToSort[doubleIndex-1]);
            treeIndex=doubleIndex;
        }
    }
};

}
