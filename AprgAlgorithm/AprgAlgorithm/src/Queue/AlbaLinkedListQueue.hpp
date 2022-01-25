#pragma once

#include <cassert>
#include <memory>

namespace alba
{

template <typename ObjectType>
class AlbaLinkedListQueue
{
public:
    struct Node
    {
        ObjectType object;
        std::unique_ptr<Node> next;
    };

    AlbaLinkedListQueue()
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

    void enqueue(ObjectType const& object)
    {
        //Add item to the end of the list
        if(isEmpty())
        {
            m_first.reset(new Node{});
            m_first->object = object;
            m_last = m_first.get();
        }
        else
        {
            m_last->next.reset(new Node{});
            m_last = m_last->next.get();
            m_last->object = object;
        }
        m_currentSize++;
    }

    ObjectType dequeue()
    {
        // Remove item from the beginning of the list
        assert(m_first);
        ObjectType result{};
        if(m_first)
        {
            result = m_first->object;
            m_first = std::move(m_first->next);
            m_currentSize--;
        }
        if(isEmpty())
        {
            m_last = nullptr;
        }
        return result;
    }

private:

    unsigned int m_currentSize;
    std::unique_ptr<Node> m_first;
    Node* m_last;
};

}
