#pragma once

#include <cassert>

namespace alba
{

template <typename ObjectType>
class AlbaLinkedListStack
{
public:
    struct Node
    {
        ObjectType object;
        Node* next;
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

    void push(ObjectType const& object)
    {
        Node* newNext = m_first;
        m_first = new Node{};
        m_first->object = object;
        m_first->next = newNext;
        m_currentSize++;
    }

    ObjectType pop()
    {
        assert(m_first != nullptr);
        ObjectType result{};
        if(m_first != nullptr)
        {
            result = m_first->object;
            Node* newHead = m_first->next;
            delete m_first;
            m_first = newHead;
            m_currentSize--;
        }
        return result;
    }

private:
    void deleteAllObjects()
    {
        Node* currentPointer = m_first;
        while(currentPointer != nullptr)
        {
            Node* nextPointer = currentPointer->next;
            delete currentPointer;
            currentPointer = nextPointer;
        }
    }

    unsigned int m_currentSize;
    Node* m_first;
};

}
