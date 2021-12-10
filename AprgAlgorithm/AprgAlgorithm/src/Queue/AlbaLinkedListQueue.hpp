#pragma once

#include <cassert>

namespace alba
{

template <typename ObjectType>
class AlbaLinkedListQueue
{
public:
    struct Node
    {
        ObjectType object;
        Node* next;
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
            m_first = new Node{};
            m_first->object = object;
            m_first->next = nullptr;
            m_last = m_first;
        }
        else
        {
            m_last->next = new Node{};
            m_last = m_last->next;
            m_last->object = object;
            m_last->next = nullptr;
        }
        m_currentSize++;
    }

    ObjectType dequeue()
    {
        // Remove item from the beginning of the list
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
        if(isEmpty())
        {
            m_last = nullptr;
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
    Node* m_last;
};

}
