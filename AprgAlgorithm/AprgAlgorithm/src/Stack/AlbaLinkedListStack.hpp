#pragma once

#include <cassert>
#include <memory>

namespace alba
{

template <typename Object>
class AlbaLinkedListStack
{
public:
    struct Node
    {
        Object object;
        std::unique_ptr<Node> next;
    };

    AlbaLinkedListStack()
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
        std::unique_ptr<Node> newNext = std::move(m_first);
        m_first.reset(new Node{object, std::move(newNext)});
        m_currentSize++;
    }
    Object pop()
    {
        assert(m_first);        Object result{};
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
    std::unique_ptr<Node> m_first;
};

}
