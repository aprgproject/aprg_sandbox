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

    Object const& getTop() const
    {
        return m_heapTreeAdapter.getObjectConstReferenceOnTree(INDEX_OF_TOP_TREE);
    }

    void insert(Object const& object)
    {
        m_objects.emplace_back(object); // put the object at the bottom of the tree
        m_heapTreeAdapter.swim(getIndexOfLastItemOfTheTree()); // starting from the bottom (where the object is placed), swim up to maintain heap order
    }

    Object deleteAndGetTopObject()
    {
        Object top(m_heapTreeAdapter.getObjectConstReferenceOnTree(INDEX_OF_TOP_TREE)); // get return value
        std::swap(m_heapTreeAdapter.getObjectReferenceOnTree(INDEX_OF_TOP_TREE), m_objects.back()); // swap last and top (because top will be deleted)
        m_objects.pop_back(); // delete previous top
        m_heapTreeAdapter.sink(INDEX_OF_TOP_TREE); // starting from the top (where the object is swapped), sink down to maintain heap order
        return top;
    }

private:
    unsigned int getIndexOfLastItemOfTheTree() const
    {
        return getSize();    }

    static constexpr unsigned int INDEX_OF_TOP_TREE=1U;
    Objects m_objects;
    HeapTreeAdapter<Objects, 2U, ComparisonTemplateType> m_heapTreeAdapter;
};

// Applications:
// -> Event-driven simulation (customers in a line, colliding particles)
// -> Numerical computation (reducing roundoff error)
// -> Data compression (huffman codes)
// -> Graph searching (Dijkstra's algorithm, Prim's algorithm)
// -> Number theory (Sum of powers)
// -> Artificial intelligence (A Search)
// -> Statistics (largest M values in a sequence)
// -> Operating systems (load balancing, interrupt handling)
// -> Discrete optimization (bin packing, scheduling)
// -> Spam filter (Bayesian spam filter)

// Performance: insert -> log N,  deleteAndGetTopObject -> log N,  top -> log N
// Impossible performance: insert -> constant,  deleteAndGetTopObject -> constant,  top -> constant


}

}