#pragma once

#include <Algorithm/PriorityQueue/HeapTreeAdapter.hpp>

#include <utility>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Object, template<class> class ComparisonTemplateType>
class HeapPriorityQueue
{
public:
    using Objects=std::vector<Object>;

    HeapPriorityQueue()
        : m_objects()
        , m_heapTreeAdapter(m_objects)
    {}

    bool isEmpty() const
    {
        return getSize() == 0;
    }

    unsigned int getSize() const
    {
        return m_objects.size();
    }

    Objects const& getObjects() const
    {
        return m_objects;
    }

    void insert(Object const& object)
    {
        m_objects.emplace_back(object);
        m_heapTreeAdapter.swim(getIndexOfLastItemOfTheTree());
    }

    Object deleteAndGetTopObject()
    {
        Object max(m_heapTreeAdapter.getObjectConstReferenceOnTree(INDEX_OF_TOP_TREE));
        std::swap(m_heapTreeAdapter.getObjectReferenceOnTree(INDEX_OF_TOP_TREE), m_objects.back());
        m_objects.pop_back();
        m_heapTreeAdapter.sink(INDEX_OF_TOP_TREE);
        return max;
    }

private:

    unsigned int getIndexOfLastItemOfTheTree() const
    {
        return getSize();
    }

    static constexpr unsigned int INDEX_OF_TOP_TREE=1U;
    Objects m_objects;
    HeapTreeAdapter<Objects, 2U, ComparisonTemplateType> m_heapTreeAdapter;
};

}

}
