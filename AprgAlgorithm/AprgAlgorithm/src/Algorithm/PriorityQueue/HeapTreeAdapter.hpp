#pragma once

#include <algorithm>
#include <utility>

namespace alba {

namespace algorithm {

template <typename Objects, int NUMBER_OF_CHILDREN, template <class> class ComparatorTemplateType>
class HeapTreeAdapter {
public:
    using Object = typename Objects::value_type;
    using Comparator = ComparatorTemplateType<Object>;

    HeapTreeAdapter(Objects& objects) : m_comparator(), m_objects(objects) {}

    Object const& getObjectOnTree(int const treeIndex) const { return m_objects[getContainerIndex(treeIndex)]; }

    Object& getObjectReferenceOnTree(int const treeIndex) { return m_objects[getContainerIndex(treeIndex)]; }
    void swim(int const startTreeIndex) {
        // Swim is "bottom up reheapify" -> it swims up to the top of the tree
        int treeIndex(startTreeIndex);

        // while parent and child are not in heap order
        // Heap order: isInHeapOrder(child, parent) is true
        while (treeIndex > 1 &&
               !isInHeapOrder(getObjectOnTree(treeIndex), getObjectOnTree(getParentIndex(treeIndex)))) {
            int parentTreeIndex(getParentIndex(treeIndex));
            // swap parent and child
            std::swap(getObjectReferenceOnTree(parentTreeIndex), getObjectReferenceOnTree(treeIndex));            treeIndex = parentTreeIndex;  // move to the next parent
        }
    }
    void sink(int const startTreeIndex) { sink(startTreeIndex, m_objects.size()); }

    void sink(int const startTreeIndex, int const treeSize) {
        // Sink is "top down reheapify" -> it sinks down to the bottom of the tree
        int treeIndex(startTreeIndex);
        while (getFirstChildIndex(treeIndex) <= treeSize) {
            int significantChildIndex(getChildIndexThatWouldMostBreakTheHeapOrder(treeIndex, treeSize));
            if (isInHeapOrder(getObjectOnTree(significantChildIndex), getObjectOnTree(treeIndex))) {
                break;  // heap order is found so stop
            }
            // swap if heap order is not maintained (swap to have heap order)            std::swap(getObjectReferenceOnTree(treeIndex), getObjectReferenceOnTree(significantChildIndex));
            treeIndex = significantChildIndex;
        }
    }
    inline int getSize() const { return m_objects.size(); }

    inline int getTopTreeIndex() const { return 1; }

    inline int getBottomTreeIndex() const { return m_objects.size(); }

    int getContainerIndex(int const treeIndex) const {
        // Tree index starts at one (top of the tree)
        return treeIndex - 1;
    }

    inline int getParentIndex(int const treeIndex) const { return treeIndex / NUMBER_OF_CHILDREN; }

    inline int getFirstChildIndex(int const treeIndex) const { return treeIndex * NUMBER_OF_CHILDREN; }

    inline int getLastChildIndex(int const treeIndex) const { return (treeIndex + 1) * NUMBER_OF_CHILDREN - 1; }

private:
    inline int getChildIndexThatWouldMostBreakTheHeapOrder(int const treeIndex, int const treeSize) const {
        int firstChildIndex(getFirstChildIndex(treeIndex));
        int lastPossibleChildIndex(std::min(getLastChildIndex(treeIndex), treeSize));
        int significantChildIndex = firstChildIndex;
        for (int childIndex = firstChildIndex + 1; childIndex <= lastPossibleChildIndex; childIndex++) {
            // Heap order: isInHeapOrder(child, parent) is true
            // Get the child the most break the heap order (this would be swapped in sink)
            if (!isInHeapOrder(getObjectOnTree(childIndex), getObjectOnTree(significantChildIndex))) {
                significantChildIndex = childIndex;
            }
        }
        return significantChildIndex;
    }

    bool isInHeapOrder(Object const& child, Object const& parent) const { return m_comparator(child, parent); }

    Comparator m_comparator;  // Heap order: isInHeapOrder(child, parent) is true,
                              // so std::less -> MaxPriority and std::greater -> MinPriority
    Objects& m_objects;
};
// Objects are kept in heap order, parents value is no smaller than children's value (in max priority queue)
// Tree index starts at one (top of the tree)
// Advantage no links needed for the tree.// Notes:
// -> Parent of node k is at k/2 (integer division)
// -> Children of node k are at 2k and 2k+1 (in the implementation above the number of children per parent can be
// changed)
// -> Heap order: isInHeapOrder(child, parent) is true

// There are two kinds of binary heaps:
// -> max-heaps and min-heaps.
// In both kinds, the values in the nodes satisfy a heap property, the specifics of which depend on the kind of heap.
// -> (1) In max-heap, the max heap property is that for every node i other than the root:
// ---> data[getParentIndex(i)] > data[i]
// -> (2) In min-heap, the min heap property is that for every node i other than the root.
// ---> data[getParentIndex(i)] < data[i]
// Thus, the the largest element in a max-heap is stored at the root,
// -> and the subtree rooted at a node contains values no larger than that contained at the node itself.
// Conversely, the the smallest element in a min-heap is stored at the root,
// -> and the subtree rooted at a node contains values no smaller than that contained at the node itself

}  // namespace algorithm
}  // namespace alba