#pragma once

#include <PriorityQueue/HeapTreeAdapter.hpp>
#include <Sorter/BaseSorter.hpp>

#include <functional>
#include <utility>

namespace alba
{

template <typename Values>
class HeapSorter : public BaseSorter<Values>
{
public:
    void sort(Values & valuesToSort) const override
    {
        constexpr unsigned int NUMBER_OF_CHILDREN_IN_HEAP_TREE=2U;
        HeapTreeAdapter<Values, NUMBER_OF_CHILDREN_IN_HEAP_TREE, std::less> heapTreeAdapter(valuesToSort);

        unsigned int size = valuesToSort.size();
        for(unsigned int treeIndex=size/NUMBER_OF_CHILDREN_IN_HEAP_TREE; treeIndex>=1; treeIndex--)
        {
            heapTreeAdapter.sink(treeIndex, size);
        }
        while(size > 1)
        {
            std::swap(valuesToSort[0], valuesToSort[size-1]);
            size--;
            heapTreeAdapter.sink(1U, size);
        }
    }
};

}
