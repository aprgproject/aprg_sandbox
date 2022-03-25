#pragma once

#include <utility>

namespace alba
{

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
        //Swim is "bottom up reheapify"
        unsigned int treeIndex(startTreeIndex);
        while(treeIndex > 1
              && isComparisonSatisfied(getObjectConstReferenceOnTree(treeIndex/NUMBER_OF_CHILDREN), getObjectConstReferenceOnTree(treeIndex)))
        {
            std::swap(getObjectReferenceOnTree(treeIndex/NUMBER_OF_CHILDREN), getObjectReferenceOnTree(treeIndex));
            treeIndex /= NUMBER_OF_CHILDREN;
        }
    }

    void sink(unsigned int const startTreeIndex)
    {
        sink(startTreeIndex, m_objects.size());
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
            std::swap(getObjectReferenceOnTree(treeIndex), getObjectReferenceOnTree(multipliedIndex));
            treeIndex=multipliedIndex;
        }
    }

private:

    unsigned int getContainerIndex(
            unsigned int const treeIndex) const
    {
        return treeIndex-1;
    }

    bool isComparisonSatisfied(
            Object const& object1,
            Object const& object2) const
    {
        return m_comparisonObject(object1, object2);
    }

    ComparisonClass m_comparisonObject;
    Objects & m_objects;
};

}

}
