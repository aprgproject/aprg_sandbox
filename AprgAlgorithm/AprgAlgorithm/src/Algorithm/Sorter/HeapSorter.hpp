#pragma once

#include <Algorithm/PriorityQueue/HeapTreeAdapter.hpp>
#include <Algorithm/Sorter/BaseSorter.hpp>

#include <functional>
#include <utility>

namespace alba
{

namespace algorithm
{

template <typename Values>
class HeapSorter : public BaseSorter<Values>
{
public:
    static constexpr unsigned int NUMBER_OF_CHILDREN_IN_HEAP_TREE=2U;
    using MaxHeapTreeAdapter = HeapTreeAdapter<Values, NUMBER_OF_CHILDREN_IN_HEAP_TREE, std::less>;

    void sort(Values & valuesToSort) const override
    {
        MaxHeapTreeAdapter maxHeapTreeAdapter(valuesToSort);

        // two passes, first put in heap order, second use the top values to sort
        putItemsInHeapOrder(maxHeapTreeAdapter);
        swapTopItemsToLastPlaces(maxHeapTreeAdapter);
    }

private:

    void putItemsInHeapOrder(MaxHeapTreeAdapter & maxHeapTreeAdapter) const
    {
        unsigned int size(maxHeapTreeAdapter.getSize());
        // Traverse all parents (starting from bottom to top), and sink down to put items in heap order
        for(unsigned int parentIndex=getLastParentAtTheBottom(maxHeapTreeAdapter); parentIndex>=maxHeapTreeAdapter.getTopTreeIndex(); parentIndex--)
        {
            maxHeapTreeAdapter.sink(parentIndex, size);
        }
    }

    void swapTopItemsToLastPlaces(MaxHeapTreeAdapter & maxHeapTreeAdapter) const
    {
        unsigned int treeIndex(maxHeapTreeAdapter.getBottomTreeIndex()); // traverse from bottom to top
        while(treeIndex > maxHeapTreeAdapter.getTopTreeIndex())
        {
            // swap current max to current last place
            std::swap(maxHeapTreeAdapter.getObjectReferenceOnTree(maxHeapTreeAdapter.getTopTreeIndex()),
                      maxHeapTreeAdapter.getObjectReferenceOnTree(treeIndex));
            treeIndex--; // move the next last place
            // starting from the top (where the object is swapped), sink down to maintain heap order
            maxHeapTreeAdapter.sink(maxHeapTreeAdapter.getTopTreeIndex(), treeIndex);
        }
    }

    unsigned int getLastParentAtTheBottom(MaxHeapTreeAdapter const& maxHeapTreeAdapter) const
    {
        return maxHeapTreeAdapter.getParentIndex(maxHeapTreeAdapter.getBottomTreeIndex());
    }
};

// Proposition: Heap construction uses <= 2N compares and exchanges
// Proposition: Heap sort uses <= 2N*log2(N) lo compares and exchanges
// Proof in heap sort: first loop with N has swap operation and sink (log2(N)) -> so its 2N*log2(N).

// Comparison to other sorts:
// Mergesort: Heapsort has no linear extra space compared to merge sort
// Quicksort: Heapsort has no case that would yield be quadratic time compared to quick sort

// Not stable -> Proof by counter example: Long distance swap might move an item past some equal item

// Bottom line: Heapsort is optimal for both time and space, but:
// -> Inner loop longer than quicksort (more things to do, several compares in sink, array index arithmetic)
// -> Makes poor use of cache memory (memory access are all over the place, not cache friendly)
// -> not stable


}

}
