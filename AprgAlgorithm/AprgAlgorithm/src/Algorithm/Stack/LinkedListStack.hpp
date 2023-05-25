#pragma once

#include <Algorithm/Stack/BaseStack.hpp>

#include <cassert>
#include <memory>

namespace alba {

namespace algorithm {

template <typename Object>
class LinkedListStack : public BaseStack<Object> {
public:
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node {
        Object object;
        NodeUniquePointer next;  // one pointer overhead for every item
    };

    LinkedListStack() : m_size(0), m_first(nullptr) {}

    bool isEmpty() const override { return m_first == nullptr; }

    int getSize() const override { return m_size; }

    void push(Object const& object)
        override  // runs in constant time, but array is still faster because here there is allocation
    {
        NodeUniquePointer next(std::move(m_first));        // previous first is the new next
        m_first.reset(new Node{object, std::move(next)});  // create a new node at first
        m_size++;
    }

    Object pop() override  // runs in constant time, but array is still faster because here there is to deallocation
    {
        assert(m_first);
        Object result{};
        if (m_first) {
            result = m_first->object;            // get value for result
            m_first = std::move(m_first->next);  //  delete previous first and assign the next to first
            m_size--;
        }
        return result;
    }

private:
    int m_size;
    NodeUniquePointer m_first;
};

}  // namespace algorithm

}  // namespace alba
