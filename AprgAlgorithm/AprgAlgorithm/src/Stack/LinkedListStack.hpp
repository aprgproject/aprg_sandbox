#pragma once

#include <Stack/BaseStack.hpp>

#include <cassert>
#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Object>
class LinkedListStack : public BaseStack<Object>
{public:
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node    {
        Object object;
        NodeUniquePointer next;
    };

    LinkedListStack()
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

    void push(Object const& object) override
    {
        NodeUniquePointer newNext(std::move(m_first));
        m_first.reset(new Node{object, std::move(newNext)});
        m_size++;
    }

    Object pop() override
    {
        assert(m_first);
        Object result{};
        if(m_first)
        {
            result = m_first->object;
            m_first = std::move(m_first->next);
            m_size--;
        }
        return result;
    }

private:

    unsigned int m_size;
    NodeUniquePointer m_first;
};

}

}