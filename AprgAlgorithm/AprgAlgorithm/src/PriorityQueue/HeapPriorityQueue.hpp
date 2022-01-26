#pragma once

#include <utility>
#include <vector>

namespace alba
{

template <typename Object, template<class> class ComparisonTemplateType>
class HeapPriorityQueue
{
public:
    using Objects=std::vector<Object>;
    using ComparisonClass=ComparisonTemplateType<Object>;
    HeapPriorityQueue()
    {}

    bool isEmpty() const
    {
        return getSize() == 0;
    }

    unsigned int getSize() const
    {
        return m_objects.size();
    }

    Objects getObjects() const
    {
        return m_objects;
    }

    void insert(Object const& object)
    {
        m_objects.emplace_back(object);
        swim(getIndexOfLastItemOfTheTree());
    }

    Object deleteAndGetMax()
    {
        Object max(getObjectConstReferenceOnTree(INDEX_OF_TOP_TREE));
        std::swap(getObjectReferenceOnTree(INDEX_OF_TOP_TREE), m_objects.back());
        m_objects.pop_back();
        sink(INDEX_OF_TOP_TREE);
        return max;
    }

private:
    void swim(unsigned int const startTreeIndex)
    {
        //Swim is "bottom up reheapify"
        unsigned int treeIndex(startTreeIndex);
        while(treeIndex > 1
              && isComparisonSatisfied(getObjectConstReferenceOnTree(treeIndex/2), getObjectConstReferenceOnTree(treeIndex)))
        {
            std::swap(getObjectReferenceOnTree(treeIndex/2), getObjectReferenceOnTree(treeIndex));
            treeIndex /= 2;
        }
    }

    void sink(unsigned int const startTreeIndex)
    {
        //Sink is "top down reheapify"
        unsigned int treeIndex(startTreeIndex);
        unsigned int size(getSize());
        while(treeIndex*2 < size)
        {
            unsigned int doubleIndex(treeIndex*2);
            if(doubleIndex < size
                    && isComparisonSatisfied(getObjectConstReferenceOnTree(doubleIndex), getObjectConstReferenceOnTree(doubleIndex+1)))
            {
                doubleIndex++;
            }
            if(!isComparisonSatisfied(getObjectConstReferenceOnTree(treeIndex), getObjectConstReferenceOnTree(doubleIndex)))
            {
                break;
            }
            std::swap(getObjectReferenceOnTree(treeIndex), getObjectReferenceOnTree(doubleIndex));
            treeIndex=doubleIndex;
        }
    }

    Object & getObjectReferenceOnTree(
            unsigned int const treeIndex)
    {
        return m_objects[getContainerIndex(treeIndex)];
    }

    Object const& getObjectConstReferenceOnTree(
            unsigned int const treeIndex)
    {
        return m_objects.at(getContainerIndex(treeIndex));
    }

    unsigned int getContainerIndex(
            unsigned int const treeIndex)
    {
        return treeIndex-1;
    }

    unsigned int getIndexOfLastItemOfTheTree()
    {
        return getSize();
    }

    bool isComparisonSatisfied(
            Object const& object1,
            Object const& object2)
    {
        return m_comparisonObject(object1, object2);
    }

    static constexpr unsigned int INDEX_OF_TOP_TREE=1U;
    unsigned int m_currentSize;
    ComparisonClass m_comparisonObject;
    Objects m_objects; //This is ordered in a tree
};

}
