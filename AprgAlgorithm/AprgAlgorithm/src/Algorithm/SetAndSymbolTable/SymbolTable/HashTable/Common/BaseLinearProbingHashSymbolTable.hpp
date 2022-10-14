#pragma once

#include <Algorithm/SetAndSymbolTable/Common/HashTable/BaseLinearProbingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Common/HashTable/HashTableEntry.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/Array/OrderedArraySymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/HashTable/Common/BaseSymbolTableWithBaseLinearProbingHash.hpp>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value, typename HashFunction>
class BaseLinearProbingHashSymbolTable
        : public BaseSymbolTableWithBaseLinearProbingHash<
        Value,
        BaseLinearProbingHash<Key, HashTableEntryWithValue<Key, Value>, HashFunction,
        OrderedArraySymbolTable<Key, Value>, BaseSymbolTable<Key, Value>>>
{};

}

}
