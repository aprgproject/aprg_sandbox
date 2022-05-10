#pragma once

#include <Algorithm/Bag/BaseBag.hpp>
#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Object>
class LinkedListBag : public BaseBag<Object>
{
public:
    using BaseClass = BaseBag<Object>;
    using TraverseFunction = typename BaseBag<Object>::TraverseFunction;
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node
    {
        Object object;
        NodeUniquePointer next;
    };

    LinkedListBag()
        : m_size(0)
        , m_first(nullptr)
    {}

    bool isEmpty() const override
    {
        return m_size == 0;
    }

    unsigned int getSize() const override
    {
        return m_size;
    }

    void add(Object const& object) override
    {
        NodeUniquePointer newNext(std::move(m_first));
        m_first.reset(new Node{object, std::move(newNext)});
        m_size++;
    }

    void traverse(TraverseFunction const& traverseFunction) override
    {
        Node* currentPointer = m_first.get();
        while(currentPointer != nullptr)
        {
            traverseFunction(currentPointer->object);
            currentPointer = currentPointer->next.get();
        }
    }

private:

    unsigned int m_size;
    NodeUniquePointer m_first;
};

}

}
