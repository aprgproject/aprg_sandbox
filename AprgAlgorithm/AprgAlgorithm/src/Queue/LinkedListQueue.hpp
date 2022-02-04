#pragma once

#include <Queue/BaseQueue.hpp>

#include <cassert>
#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Object>
class LinkedListQueue : public BaseQueue<Object>
{public:
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node    {
        Object object;
        NodeUniquePointer next;
    };

    LinkedListQueue()
        : m_size(0)
        , m_first(nullptr)
    {}

    bool isEmpty() const override
    {
        return m_size == 0;
    }

    unsigned int getSize() const override
    {
        return m_size;
    }

    void enqueue(Object const& object) override
    {
        if(isEmpty())
        {
            m_first.reset(new Node{object, nullptr});
            m_last = m_first.get();
        }
        else
        {
            m_last->next.reset(new Node{object, nullptr});
            m_last = m_last->next.get();
        }
        m_size++;
    }

    Object dequeue() override
    {
        assert(m_first);
        Object result{};
        if(m_first)
        {
            result = m_first->object;
            m_first = std::move(m_first->next);
            m_size--;
        }
        if(isEmpty())
        {
            m_last = nullptr;
        }
        return result;
    }

private:

    unsigned int m_size;
    NodeUniquePointer m_first;
    Node* m_last;
};

}

}