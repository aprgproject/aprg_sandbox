#pragma once

#include <Algorithm/SetAndSymbolTable/Common/LinkedList/BaseUnorderedLinkedList.hpp>
#include <Algorithm/SetAndSymbolTable/Common/LinkedList/LinkedListNode.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value>
class UnorderedLinkedListSymbolTable : public BaseUnorderedLinkedList<Key, LinkedListNodeWithValue<Key, Value>, BaseSymbolTable<Key, Value>>
{
public:
    using BaseClass = BaseUnorderedLinkedList<Key, LinkedListNodeWithValue<Key, Value>, BaseSymbolTable<Key, Value>>;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;
    using Keys = typename BaseClass::Keys;

    UnorderedLinkedListSymbolTable()
        : BaseClass()
        , b_size(BaseClass::m_size)
        , b_first(BaseClass::m_first)
    {}

    Value get(Key const& key) const override
    {
        Value result{};
        this->traverseWithNoChange([&](Node const& node, bool & shouldBreak)
        {
            if(key == node.key)
            {
                result = node.value;
                shouldBreak = true;
            }
        });
        return result;
    }

    void put(Key const& key, Value const& value) override
    {
        bool isKeyFound(false);
        this->traverseWithChange([&](Node & node, bool & shouldBreak)
        {
            if(key == node.key)
            {
                node.value = value;
                isKeyFound = true;
                shouldBreak = true;
            }
        });
        if(!isKeyFound)
        {
            NodeUniquePointer newNext(std::move(b_first));
            b_first.reset(new Node{key, value, std::move(newNext)});
            b_size++;
        }
    }

private:
    unsigned int & b_size;
    NodeUniquePointer & b_first;
};
}

}