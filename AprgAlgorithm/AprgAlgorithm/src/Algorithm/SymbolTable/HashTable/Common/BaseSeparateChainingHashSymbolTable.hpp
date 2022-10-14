#pragma once

#include <Algorithm/SetAndSymbolTable/Common/HashTable/BaseSeparateChainingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Common/HashTable/HashTableEntry.hpp>
#include <Algorithm/SymbolTable/OrderedArraySymbolTable.hpp>
#include <Algorithm/SymbolTable/UnorderedLinkedListSymbolTable.hpp>
#include <Algorithm/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SymbolTable/HashTable/Common/BaseSymbolTableWithBaseSeparateChainingHash.hpp>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value, typename HashFunction, unsigned int HASH_TABLE_SIZE>
class BaseSeparateChainingHashSymbolTable
        : public BaseSymbolTableWithBaseSeparateChainingHash<
        Value,
        BaseSeparateChainingHash<Key, HashTableEntryWithValue<Key, Value>, HashFunction, HASH_TABLE_SIZE,
        OrderedArraySymbolTable<Key, Value>, UnorderedLinkedListSymbolTable<Key, Value>, BaseSymbolTable<Key, Value>>>
{};

}

}
