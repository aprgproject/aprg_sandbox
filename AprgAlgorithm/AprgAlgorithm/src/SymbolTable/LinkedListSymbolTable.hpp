#pragma once

#include <memory>

namespace alba
{

template <typename Key, typename Object>
class LinkedListSymbolTable
{
public:
    struct Node
    {
        Key key;
        Object object;
        std::unique_ptr<Node> next;
    };

    LinkedListSymbolTable()
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

    Object get(Key const& key) const
    {
        Object result{};
        for(Node* currentNodePointer=m_first.get(); currentNodePointer!=nullptr; currentNodePointer=currentNodePointer->next.get())
        {
            if(key == currentNodePointer->key)
            {
                result = currentNodePointer->object;
            }
        }
        return result;
    }

    void put(Key const& key, Object const& object)
    {
        bool isKeyFound(false);
        for(Node* currentNodePointer=m_first.get(); currentNodePointer!=nullptr; currentNodePointer=currentNodePointer->next.get())
        {
            if(key == currentNodePointer->key)
            {
                currentNodePointer->object = object;
                isKeyFound = true;
                break;
            }
        }
        if(!isKeyFound)
        {
            std::unique_ptr<Node> newNext = std::move(m_first);
            m_first.reset(new Node{key, object, std::move(newNext)});
            m_currentSize++;
        }
    }

private:

    unsigned int m_currentSize;
    std::unique_ptr<Node> m_first;
};

}
