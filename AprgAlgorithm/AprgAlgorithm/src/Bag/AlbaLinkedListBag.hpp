#pragma once

#include <functional>
#include <cassert>

namespace alba
{

template <typename ObjectType>
class AlbaLinkedListBag
{
public:
    struct Node
    {
        ObjectType object;
        Node* next;
    };
    using TraverseFunction = std::function<void(ObjectType const& object)>;

    AlbaLinkedListBag()
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

    void add(ObjectType const& object)
    {
        Node* newNext = m_first;
        m_first = new Node{};
        m_first->object = object;
        m_first->next = newNext;
        m_currentSize++;
    }

    void traverse(TraverseFunction const& traverseFunction)
    {
        Node* currentPointer = m_first;
        while(currentPointer != nullptr)
        {
            traverseFunction(currentPointer->object);
            currentPointer = currentPointer->next;
        }
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
