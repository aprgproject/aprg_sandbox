#pragma once

#include <cassert>
#include <memory>

namespace alba
{
template <typename ObjectType>
class AlbaLinkedListStack
{public:
    struct Node
    {
        ObjectType object;
        std::unique_ptr<Node> next;
    };

    AlbaLinkedListStack()        : m_currentSize(0)
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

    void push(ObjectType const& object)
    {
        std::unique_ptr<Node> newNext = std::move(m_first);
        m_first.reset(new Node{});
        m_first->object = object;
        m_first->next = std::move(newNext);
        m_currentSize++;
    }

    ObjectType pop()
    {
        assert(m_first);
        ObjectType result{};
        if(m_first)
        {
            result = m_first->object;
            m_first = std::move(m_first->next);
            m_currentSize--;
        }
        return result;    }

private:

    unsigned int m_currentSize;
    std::unique_ptr<Node> m_first;
};

}