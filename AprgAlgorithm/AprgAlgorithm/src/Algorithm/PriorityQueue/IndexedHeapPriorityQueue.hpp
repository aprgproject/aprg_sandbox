#pragma once

#include <Algorithm/PriorityQueue/HeapTreeAdapter.hpp>

#include <utility>
#include <vector>

namespace alba
{
namespace algorithm
{
namespace IndexedHeapPriorityQueueConstants
{
constexpr unsigned int INDEX_OF_TOP_TREE=1U;
constexpr unsigned int VALUE_FOR_UNUSED_INDEX=0xFFFFFFFFU;
}

template <typename Object, template<class> class ComparisonTemplateType, unsigned int NUMBER_OF_CHILDREN>
class IndexedHeapPriorityQueue
{
public:
    // this class is dangerous, the user needs to be aware of index used -> no checks implemented
    using Indexes = std::vector<unsigned int>;
    using Objects = std::vector<Object>;
    using ComparisonClass = ComparisonTemplateType<Object>;

    IndexedHeapPriorityQueue()
        : m_size(0U)
        , m_maxSize(0U)
    {}

    bool isEmpty() const
    {
        return getSize() == 0;
    }

    bool contains(unsigned int const objectIndex) const
    {
        bool result(false);
        if(objectIndex < m_objectIndexToTreeIndex.size())
        {
            result = m_objectIndexToTreeIndex.at(objectIndex) != IndexedHeapPriorityQueueConstants::VALUE_FOR_UNUSED_INDEX;
        }
        return result;
    }

    unsigned int getSize() const
    {
        return m_size;
    }

    Objects const& getObjects() const
    {
        return m_objects;
    }

    Indexes const& getTreeIndexToObjectIndex() const
    {
        return m_treeIndexToObjectIndex;
    }

    Indexes const& getObjectIndexToTreeIndex() const
    {
        return m_objectIndexToTreeIndex;
    }

    unsigned int getIndexOfTopObject() const
    {
        return m_treeIndexToObjectIndex.at(IndexedHeapPriorityQueueConstants::INDEX_OF_TOP_TREE);
    }

    Object const& getTopObject() const
    {
        return m_objects.at(getIndexOfTopObject());
    }

    Object const& getObjectAt(unsigned int const objectIndex) const
    {
        return m_objects.at(objectIndex);
    }

    void setNumberOfItems(unsigned int const numberOfItems)
    {
        resizeToHaveThisIndexIfNeeded(numberOfItems);
    }

    void insert(unsigned int const objectIndex, Object const& object)
    {
        m_size++;
        resizeToHaveThisIndexIfNeeded(std::max(objectIndex, m_size));
        m_objectIndexToTreeIndex[objectIndex] = m_size;
        m_treeIndexToObjectIndex[m_size] = objectIndex;
        m_objects[objectIndex] = object;
        swim(m_size);
    }

    Object deleteAndGetTopObject()
    {
        Object topObject{};
        if(!isEmpty())
        {
            topObject = getTopObject();
            unsigned int objectIndexOfTopObject = getIndexOfTopObject();
            swapIndexes(IndexedHeapPriorityQueueConstants::INDEX_OF_TOP_TREE, m_size--);
            sink(IndexedHeapPriorityQueueConstants::INDEX_OF_TOP_TREE);
            m_objectIndexToTreeIndex[objectIndexOfTopObject] = IndexedHeapPriorityQueueConstants::VALUE_FOR_UNUSED_INDEX;
            m_objects[objectIndexOfTopObject] = Object{};
            m_treeIndexToObjectIndex[m_size+1] = IndexedHeapPriorityQueueConstants::VALUE_FOR_UNUSED_INDEX;
        }
        return topObject;
    }

    void deleteObjectAt(unsigned int const objectIndex)
    {
        if(objectIndex < m_objects.size())
        {
            unsigned int treeIndex(m_objectIndexToTreeIndex.at(objectIndex));
            if(treeIndex != IndexedHeapPriorityQueueConstants::VALUE_FOR_UNUSED_INDEX)
            {
                swapIndexes(treeIndex, m_size--);
                swim(treeIndex);
                sink(treeIndex);
                m_objects[objectIndex] = Object{};
                m_objectIndexToTreeIndex[objectIndex] = IndexedHeapPriorityQueueConstants::VALUE_FOR_UNUSED_INDEX;
                m_treeIndexToObjectIndex[m_size+1] = IndexedHeapPriorityQueueConstants::VALUE_FOR_UNUSED_INDEX;
            }
        }
    }

    void change(unsigned int const objectIndex, Object const& object)
    {
        if(objectIndex >= m_objects.size())
        {
            insert(objectIndex, object);
        }
        else
        {
            m_objects[objectIndex] = object;
            unsigned int treeIndex(m_objectIndexToTreeIndex.at(objectIndex));
            if(treeIndex == IndexedHeapPriorityQueueConstants::VALUE_FOR_UNUSED_INDEX)
            {
                m_size++;
                m_objectIndexToTreeIndex[objectIndex] = m_size;
                m_treeIndexToObjectIndex[m_size] = objectIndex;
                treeIndex = m_size;
            }
            swim(treeIndex);
            sink(treeIndex);
        }
    }

private:

    bool isComparisonSatisfied(
            Object const& object1,
            Object const& object2)
    {
        return m_comparisonObject(object1, object2);
    }

    unsigned int getContainerIndex(unsigned int const treeIndex) const
    {
        // This is not used because size usage is not efficient. No use to make it efficient.
        return treeIndex-1;
    }

    Object const& getObjectConstReferenceOnTree(unsigned int const treeIndex) const
    {
        return m_objects.at(m_treeIndexToObjectIndex.at(treeIndex));
    }

    void resizeToHaveThisIndexIfNeeded(unsigned int const index)
    {
        if(m_maxSize <= index)
        {
            // resize to enlarge, no resize to reduce? // Boo not efficient.
            m_treeIndexToObjectIndex.resize(index+1);
            m_objectIndexToTreeIndex.resize(index+1);
            m_objects.resize(index+1);
            std::fill(m_treeIndexToObjectIndex.begin()+m_maxSize, m_treeIndexToObjectIndex.end(), IndexedHeapPriorityQueueConstants::VALUE_FOR_UNUSED_INDEX);
            std::fill(m_objectIndexToTreeIndex.begin()+m_maxSize, m_objectIndexToTreeIndex.end(), IndexedHeapPriorityQueueConstants::VALUE_FOR_UNUSED_INDEX);
            std::fill(m_objects.begin()+m_maxSize, m_objects.end(), Object{});
            m_maxSize = index+1;
        }
    }

    void swim(unsigned int const startTreeIndex)
    {
        //Swim is "bottom up reheapify"
        unsigned int treeIndex(startTreeIndex);
        while(treeIndex > 1
              && isComparisonSatisfied(getObjectConstReferenceOnTree(treeIndex/NUMBER_OF_CHILDREN), getObjectConstReferenceOnTree(treeIndex)))
        {
            swapIndexes(treeIndex/NUMBER_OF_CHILDREN, treeIndex);
            treeIndex /= NUMBER_OF_CHILDREN;
        }
    }

    void sink(unsigned int const startTreeIndex)
    {
        sink(startTreeIndex, m_size);
    }

    void sink(unsigned int const startTreeIndex, unsigned int const treeSize)
    {
        //Sink is "top down reheapify"
        unsigned int treeIndex(startTreeIndex);
        while(treeIndex*NUMBER_OF_CHILDREN < treeSize)
        {
            unsigned int multipliedIndex(treeIndex*NUMBER_OF_CHILDREN);
            if(multipliedIndex < treeSize
                    && isComparisonSatisfied(getObjectConstReferenceOnTree(multipliedIndex), getObjectConstReferenceOnTree(multipliedIndex+1)))
            {
                multipliedIndex++;
            }
            if(!isComparisonSatisfied(getObjectConstReferenceOnTree(treeIndex), getObjectConstReferenceOnTree(multipliedIndex)))
            {
                break;
            }
            swapIndexes(treeIndex, multipliedIndex);
            treeIndex=multipliedIndex;
        }
    }

    void swapIndexes(unsigned int const treeIndex1, unsigned int const treeIndex2)
    {
        std::swap(m_treeIndexToObjectIndex[treeIndex1], m_treeIndexToObjectIndex[treeIndex2]);
        m_objectIndexToTreeIndex[m_treeIndexToObjectIndex.at(treeIndex1)] = treeIndex1;
        m_objectIndexToTreeIndex[m_treeIndexToObjectIndex.at(treeIndex2)] = treeIndex2;
    }

    unsigned int m_size;
    unsigned int m_maxSize;
    ComparisonClass m_comparisonObject;
    Indexes m_treeIndexToObjectIndex;
    Indexes m_objectIndexToTreeIndex;
    Objects m_objects;
};

}

}
