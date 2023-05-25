#pragma once

#include <Algorithm/SetAndSymbolTable/SymbolTable/HashTable/Common/BaseSeparateChainingHashSymbolTable.hpp>

namespace alba {

namespace algorithm {

template <typename Key, typename Value, typename HashFunction, int HASH_TABLE_SIZE>
class SeparateChainingHashSymbolTable
    : public BaseSeparateChainingHashSymbolTable<Key, Value, HashFunction, HASH_TABLE_SIZE> {};

}  // namespace algorithm

}  // namespace alba
