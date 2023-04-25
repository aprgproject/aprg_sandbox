#pragma once

#include <Algorithm/SetAndSymbolTable/Set/HashTable/Common/BaseSeparateChainingHashSet.hpp>

namespace alba {

namespace algorithm {

template <typename Key, typename HashFunction, unsigned int HASH_TABLE_SIZE>
class SeparateChainingHashSet : public BaseSeparateChainingHashSet<Key, HashFunction, HASH_TABLE_SIZE> {};

}  // namespace algorithm

}  // namespace alba
