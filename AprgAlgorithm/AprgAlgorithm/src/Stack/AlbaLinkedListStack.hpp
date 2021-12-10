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
        , m_head(nullptr)
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
        Node* newNext = m_head;
        m_head = new Node{};
        m_head->object = object;
        m_head->next = newNext;
        m_currentSize++;
    }

    ObjectType pop()
    {
        assert(m_head != nullptr);
        ObjectType result{};
        if(m_head != nullptr)
        {
            result = m_head->object;
            Node* newHead = m_head->next;
            delete m_head;
            m_head = newHead;
            m_currentSize--;
        }
        return result;
    }

private:
    void deleteAllObjects()
    {
        Node* currentPointer = m_head;
        while(currentPointer != nullptr)
        {
            Node* nextPointer = currentPointer->next;
            delete currentPointer;
            currentPointer = nextPointer;
        }
    }

    unsigned int m_currentSize;
    Node* m_head;
};

}
