#pragma once

#include <functional>
#include <cassert>
#include <memory>

namespace alba
{

template <typename ObjectType>
class AlbaLinkedListBag
{
public:
    struct Node
    {
        ObjectType object;
        std::unique_ptr<Node> next;
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
        std::unique_ptr<Node> newNext(std::move(m_first));
        m_first.reset(new Node{});
        m_first->object = object;
        m_first->next = std::move(newNext);
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
