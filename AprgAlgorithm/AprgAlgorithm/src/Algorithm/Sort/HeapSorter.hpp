#pragma once

#include <Algorithm/PriorityQueue/HeapTreeAdapter.hpp>
#include <Algorithm/Sort/BaseSorter.hpp>

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

    HeapSorter() = default;

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

}

}

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



// Other discussions:
// Heap sort is a comparison-based sorting technique based on Binary Heap data structure.
// It is similar to selection sort where we first find the minimum element and place the minimum element at the beginning.
// We repeat the same process for the remaining elements.

// What is Binary Heap?
// Let us first define a Complete Binary Tree.
// A complete binary tree is a binary tree in which every level, except possibly the last,
// is completely filled, and all nodes are as far left as possible (Source Wikipedia)
// A Binary Heap is a Complete Binary Tree where items are stored in a special order
// such that the value in a parent node is greater(or smaller) than the values in its two children nodes.
// The former is called max heap and the latter is called min-heap.
// The heap can be represented by a binary tree or array.

// Why array based representation for Binary Heap?
// Since a Binary Heap is a Complete Binary Tree, it can be easily represented as an array and the array-based representation is space-efficient.
// If the parent node is stored at index I, the left child can be calculated by 2 * I + 1 and the right child by 2 * I + 2 (assuming the indexing starts at 0).

// Heap Sort Algorithm for sorting in increasing order:
// 1. Build a max heap from the input data.
// 2. At this point, the largest item is stored at the root of the heap.
// -> Replace it with the last item of the heap followed by reducing the size of heap by 1.
// -> Finally, heapify the root of the tree.
// 3. Repeat step 2 while the size of the heap is greater than 1.

// How to build the heap?
// Heapify procedure can be applied to a node only if its children nodes are heapified.
// So the heapification must be performed in the bottom-up order.

// Notes:
// Heap sort is an in-place algorithm.
// Its typical implementation is not stable, but can be made stable.
// Time Complexity:
// Time complexity of heapify is O(Logn).
// Time complexity of createAndBuildHeap() is O(n) and the overall time complexity of Heap Sort is O(nLogn).

// Applications of HeapSort
// 1. Sort a nearly sorted (or K sorted) array
// 2. k largest(or smallest) elements in an array

// Heap sort algorithm has limited uses because Quicksort and Mergesort are better in practice.
// Nevertheless, the Heap data structure itself is enormously used.

