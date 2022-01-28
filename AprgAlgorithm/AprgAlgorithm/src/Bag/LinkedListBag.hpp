#pragma once

#include <functional>
#include <cassert>
#include <memory>

namespace alba
{

template <typename Object>
class LinkedListBag
{
public:
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    using TraverseFunction = std::function<void(Object const& object)>;
    struct Node
    {
        Object object;
        NodeUniquePointer next;
    };

    LinkedListBag()
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

    void add(Object const& object)
    {
        NodeUniquePointer newNext(std::move(m_first));
        m_first.reset(new Node{object, std::move(newNext)});
        m_currentSize++;
    }

    void traverse(TraverseFunction const& traverseFunction)
    {
        Node* currentPointer = m_first.get();
        while(currentPointer != nullptr)
        {
            traverseFunction(currentPointer->object);
            currentPointer = currentPointer->next.get();
        }
    }

private:

    unsigned int m_currentSize;
    NodeUniquePointer m_first;
};

}
