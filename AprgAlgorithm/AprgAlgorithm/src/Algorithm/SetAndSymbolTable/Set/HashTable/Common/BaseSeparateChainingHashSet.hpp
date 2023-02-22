#pragma once

#include <Algorithm/SetAndSymbolTable/Common/HashTable/BaseSeparateChainingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Common/HashTable/HashTableEntry.hpp>
#include <Algorithm/SetAndSymbolTable/Set/Array/OrderedArraySet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/HashTable/Common/BaseSetWithBaseSeparateChainingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Set/LinkedList/UnorderedLinkedListSet.hpp>

namespace alba
{

namespace algorithm
{

template <typename Key, typename HashFunction, unsigned int HASH_TABLE_SIZE>
class BaseSeparateChainingHashSet
        : public BaseSetWithBaseSeparateChainingHash<
        BaseSeparateChainingHash<Key, HashTableEntry<Key>, HashFunction, HASH_TABLE_SIZE,
        OrderedArraySet<Key>, UnorderedLinkedListSet<Key>, BaseSet<Key>>>
{
public:
    ~BaseSeparateChainingHashSet() override = default; // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
};

}

}
