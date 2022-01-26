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
    struct Node
    {
        Object object;
        std::unique_ptr<Node> next;
    };
    using TraverseFunction = std::function<void(Object const& object)>;

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
        std::unique_ptr<Node> newNext(std::move(m_first));
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
    std::unique_ptr<Node> m_first;
};

}
