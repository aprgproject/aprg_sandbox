#pragma once

#include <Algorithm/PriorityQueue/BinaryHeap/BinaryHeapAdapter.hpp>

#include <utility>
#include <vector>
namespace alba {

namespace algorithm {

template <typename Object, template <class> class ComparatorTemplateType>
class BinaryHeapPriorityQueue {
public:
    using Objects = std::vector<Object>;

    BinaryHeapPriorityQueue() : m_objects(), m_heapTreeAdapter(m_objects) {}

    bool isEmpty() const { return getSize() == 0; }
    int getSize() const { return m_objects.size(); }

    Objects const& getObjects() const { return m_objects; }
    Object const& getTop() const { return m_heapTreeAdapter.getObjectOnTree(INDEX_OF_TOP_TREE); }

    void insert(Object const& object) {
        // put the object at the bottom of the tree
        m_objects.emplace_back(object);
        // starting from the bottom (where the object is placed), swim up to maintain heap order
        m_heapTreeAdapter.swim(getIndexOfLastItemOfTheTree());
    }

    Object deleteAndGetTopObject() {
        // get return value
        Object top(m_heapTreeAdapter.getObjectOnTree(INDEX_OF_TOP_TREE));
        // swap last and top (because top will be deleted)
        std::swap(m_heapTreeAdapter.getObjectReferenceOnTree(INDEX_OF_TOP_TREE), m_objects.back());
        // delete previous top
        m_objects.pop_back();
        // starting from the top (where the object is swapped), sink down to maintain heap order
        m_heapTreeAdapter.sink(INDEX_OF_TOP_TREE);
        return top;
    }

private:
    int getIndexOfLastItemOfTheTree() const { return getSize(); }

    static constexpr int INDEX_OF_TOP_TREE = 1;
    Objects m_objects;
    BinaryHeapAdapter<Objects, 2, ComparatorTemplateType> m_heapTreeAdapter;
};

// Applications:// -> Event-driven simulation (customers in a line, colliding particles)
// -> Numerical computation (reducing roundoff error)
// -> Data compression (huffman codes)
// -> Graph searching (Dijkstra's algorithm, Prim's algorithm)// -> Number theory (Sum of powers)
// -> Artificial intelligence (A Search)
// -> Statistics (largest M values in a sequence)
// -> Operating systems (load balancing, interrupt handling)
// -> Discrete optimization (bin packing, scheduling)
// -> Spam filter (Bayesian spam filter)

// Performance: insert -> log N,  deleteAndGetTopObject -> log N,  top -> log N
// Impossible performance: insert -> constant,  deleteAndGetTopObject -> constant,  top -> constant

}  // namespace algorithm

}  // namespace alba
