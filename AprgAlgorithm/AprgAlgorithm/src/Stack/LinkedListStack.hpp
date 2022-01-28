#pragma once

#include <cassert>
#include <memory>

namespace alba
{

template <typename Object>
class LinkedListStack
{
public:
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node
    {
        Object object;
        NodeUniquePointer next;
    };

    LinkedListStack()
        : m_currentSize(0)
        , m_first(nullptr)
    {}

    bool isEmpty() const
    {
        return m_currentSize == 0;
    }

    unsigned int getSize() const
    {
        return m_currentSize;
    }

    void push(Object const& object)
    {
        NodeUniquePointer newNext(std::move(m_first));
        m_first.reset(new Node{object, std::move(newNext)});
        m_currentSize++;
    }

    Object pop()
    {
        assert(m_first);
        Object result{};
        if(m_first)
        {
            result = m_first->object;
            m_first = std::move(m_first->next);
            m_currentSize--;
        }
        return result;
    }

private:

    unsigned int m_currentSize;
    NodeUniquePointer m_first;
};

}
