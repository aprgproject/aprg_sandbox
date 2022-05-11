#pragma once

#include <algorithm>
#include <utility>

namespace alba{

namespace algorithm
{
template <typename Objects, unsigned int NUMBER_OF_CHILDREN, template<class> class ComparisonTemplateType>
class HeapTreeAdapter
{
public:
    using Object = typename Objects::value_type;
    using ComparisonClass=ComparisonTemplateType<Object>;

    HeapTreeAdapter(Objects & objects)
        : m_comparisonObject()
        , m_objects(objects)
    {}

    Object const& getObjectConstReferenceOnTree(
            unsigned int const treeIndex) const
    {
        return m_objects.at(getContainerIndex(treeIndex));
    }

    Object & getObjectReferenceOnTree(
            unsigned int const treeIndex)
    {
        return m_objects[getContainerIndex(treeIndex)];
    }

    void swim(unsigned int const startTreeIndex)
    {
        //Swim is "bottom up reheapify" -> it swims up to the top of the tree
        unsigned int treeIndex(startTreeIndex);

        // while parent and child are not in heap order
        // Heap order: isComparisonSatisfied(child, parent) is true
        while(treeIndex > 1
              && isComparisonSatisfied(getObjectConstReferenceOnTree(getParentIndex(treeIndex)), getObjectConstReferenceOnTree(treeIndex)))
        {
            unsigned int parentTreeIndex(getParentIndex(treeIndex));
            std::swap(getObjectReferenceOnTree(parentTreeIndex), getObjectReferenceOnTree(treeIndex)); // swap parent and child
            treeIndex = parentTreeIndex; // move to the next parent
        }
    }
    void sink(unsigned int const startTreeIndex)
    {
        sink(startTreeIndex, m_objects.size());    }

    void sink(unsigned int const startTreeIndex, unsigned int const treeSize)
    {
        //Sink is "top down reheapify" -> it sinks down to the bottom of the tree
        unsigned int treeIndex(startTreeIndex);
        while(getFirstChildIndex(treeIndex) <= treeSize)
        {
            unsigned int significantChildIndex(getChildIndexThatWouldMostBreakTheHeapOrder(treeIndex, treeSize));
            if(!isComparisonSatisfied(getObjectConstReferenceOnTree(treeIndex), getObjectConstReferenceOnTree(significantChildIndex)))
            {
                break; // heap order is found so stop
            }
            std::swap(getObjectReferenceOnTree(treeIndex), getObjectReferenceOnTree(significantChildIndex)); // swap if heap order is not maintained (swap to have heap order)
            treeIndex=significantChildIndex;
        }
    }

    inline unsigned int getSize() const
    {
        return m_objects.size();
    }

    inline unsigned int getTopTreeIndex() const
    {
        return 1U;
    }

    inline unsigned int getBottomTreeIndex() const
    {
        return m_objects.size();
    }

    unsigned int getContainerIndex(
            unsigned int const treeIndex) const
    {
        // Tree index starts at one (top of the tree)
        return treeIndex-1;
    }

    inline unsigned int getParentIndex(
            unsigned int const treeIndex) const
    {
        return treeIndex/NUMBER_OF_CHILDREN;
    }

    inline unsigned int getFirstChildIndex(
            unsigned int const treeIndex) const
    {
        return treeIndex*NUMBER_OF_CHILDREN;
    }

    inline unsigned int getLastChildIndex(
            unsigned int const treeIndex) const
    {
        return (treeIndex+1)*NUMBER_OF_CHILDREN-1;
    }

private:

    inline unsigned int getChildIndexThatWouldMostBreakTheHeapOrder(
            unsigned int const treeIndex,
            unsigned int const treeSize) const
    {
        unsigned int firstChildIndex(getFirstChildIndex(treeIndex));
        unsigned int lastPossibleChildIndex(std::min(getLastChildIndex(treeIndex), treeSize));
        unsigned int significantChildIndex = firstChildIndex;
        for(unsigned int index = firstChildIndex+1; index<=lastPossibleChildIndex; index++)
        {
            // Get the child the most break the heap order (this would be swapped in sink)
            // Heap order: isComparisonSatisfied(child, parent) is true
            if(isComparisonSatisfied(getObjectConstReferenceOnTree(significantChildIndex), getObjectConstReferenceOnTree(index))) // most break comparison
            {
                significantChildIndex = index;
            }
        }
        return significantChildIndex;
    }

    bool isComparisonSatisfied(
            Object const& object1,
            Object const& object2) const    {
        return m_comparisonObject(object1, object2);
    }

    ComparisonClass m_comparisonObject; //Heap order: isComparisonSatisfied(child, parent) is true, so std::less -> MaxPriority and std::greater -> MinPriority
    Objects & m_objects;
};

// Objects are kept in heap order, parents value is no smaller than children's value (in max priority queue)
// Tree index starts at one (top of the tree)
// Advantage no links needed for the tree.
// Notes:
// -> Parent of node k is at k/2 (integer division)
// -> Children of node k are at 2k and 2k+1 (in the implementation above the number of children per parent can be changed)
// -> Heap order: isComparisonSatisfied(child, parent) is true

}

}