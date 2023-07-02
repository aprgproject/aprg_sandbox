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

    Object const& getObjectConstReferenceOnTree(int const treeIndex) const {
        return m_objects[getContainerIndex(treeIndex)];
    }

    Object& getObjectReferenceOnTree(int const treeIndex) { return m_objects[getContainerIndex(treeIndex)]; }

    void swim(int const startTreeIndex) {
        // Swim is "bottom up reheapify" -> it swims up to the top of the tree
        int treeIndex(startTreeIndex);

        // while parent and child are not in heap order
        // Heap order: isComparisonSatisfied(child, parent) is true
        while (treeIndex > 1 && isComparisonSatisfied(
                                    getObjectConstReferenceOnTree(getParentIndex(treeIndex)),
                                    getObjectConstReferenceOnTree(treeIndex))) {
            int parentTreeIndex(getParentIndex(treeIndex));
            // swap parent and child
            std::swap(getObjectReferenceOnTree(parentTreeIndex), getObjectReferenceOnTree(treeIndex));
            treeIndex = parentTreeIndex;  // move to the next parent
        }
    }

    void sink(int const startTreeIndex) { sink(startTreeIndex, m_objects.size()); }

    void sink(int const startTreeIndex, int const treeSize) {
        // Sink is "top down reheapify" -> it sinks down to the bottom of the tree
        int treeIndex(startTreeIndex);
        while (getFirstChildIndex(treeIndex) <= treeSize) {
            int significantChildIndex(getChildIndexThatWouldMostBreakTheHeapOrder(treeIndex, treeSize));
            if (!isComparisonSatisfied(
                    getObjectConstReferenceOnTree(treeIndex), getObjectConstReferenceOnTree(significantChildIndex))) {
                break;  // heap order is found so stop
            }
            // swap if heap order is not maintained (swap to have heap order)
            std::swap(getObjectReferenceOnTree(treeIndex), getObjectReferenceOnTree(significantChildIndex));
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
            // Heap order: isComparisonSatisfied(child, parent) is true
            // Get the child the most break the heap order (this would be swapped in sink)
            if (isComparisonSatisfied(
                    getObjectConstReferenceOnTree(significantChildIndex), getObjectConstReferenceOnTree(childIndex))) {
                significantChildIndex = childIndex;
            }
        }
        return significantChildIndex;
    }

    bool isComparisonSatisfied(Object const& object1, Object const& object2) const {
        return m_comparator(object1, object2);
    }

    Comparator m_comparator;  // Heap order: isComparisonSatisfied(child, parent) is true, so std::less -> MaxPriority
                              // and std::greater -> MinPriority
    Objects& m_objects;
};

// Objects are kept in heap order, parents value is no smaller than children's value (in max priority queue)
// Tree index starts at one (top of the tree)
// Advantage no links needed for the tree.
// Notes:
// -> Parent of node k is at k/2 (integer division)
// -> Children of node k are at 2k and 2k+1 (in the implementation above the number of children per parent can be
// changed)
// -> Heap order: isComparisonSatisfied(child, parent) is true

}  // namespace algorithm

}  // namespace alba
