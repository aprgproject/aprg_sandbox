#pragma once

#include <Algorithm/SetAndSymbolTable/Common/LinkedList/BaseUnorderedLinkedList.hpp>
#include <Algorithm/SetAndSymbolTable/Common/LinkedList/LinkedListNode.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>

namespace alba
{

namespace algorithm
{

template <typename Key>
class UnorderedLinkedListSet : public BaseUnorderedLinkedList<Key, LinkedListNode<Key>, BaseSet<Key>>
{
public:
    using BaseClass = BaseUnorderedLinkedList<Key, LinkedListNode<Key>, BaseSet<Key>>;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;
    using Keys = typename BaseClass::Keys;

    UnorderedLinkedListSet()
        : BaseClass()
        , b_size(BaseClass::m_size)
        , b_first(BaseClass::m_first)
    {}

    void put(Key const& key) override
    {
        bool isKeyFound(false);
        this->traverseWithChange([&](Node & node, bool & shouldBreak)
        {
            if(key == node.key)
            {
                isKeyFound = true;
                shouldBreak = true;
            }
        });
        if(!isKeyFound)
        {
            NodeUniquePointer newNext(std::move(b_first));
            b_first.reset(new Node{key, std::move(newNext)});
            b_size++;
        }
    }

private:
    unsigned int & b_size;
    NodeUniquePointer & b_first;
};

}

}
