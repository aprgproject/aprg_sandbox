#pragma once

#include <Algorithm/SetAndSymbolTable/Common/HashTable/BaseLinearProbingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Common/HashTable/HashTableEntry.hpp>
#include <Algorithm/SymbolTable/OrderedArraySymbolTable.hpp>
#include <Algorithm/SymbolTable/HashTable/Common/BaseSymbolTableWithBaseLinearProbingHash.hpp>
#include <Algorithm/SymbolTable/BaseSymbolTable.hpp>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value, typename HashFunction>
class BaseLinearProbingHashSymbolTable
        : public BaseSymbolTableWithBaseLinearProbingHash<
        Value,
        BaseLinearProbingHash<Key, HashTableEntryWithValue<Key, Value>, HashFunction, OrderedArraySymbolTable<Key, Value>, BaseSymbolTable<Key, Value>>>
{};

}

}
