#pragma once

#include <Algorithm/SetAndSymbolTable/SymbolTable/HashTable/Common/BaseLinearProbingHashSymbolTable.hpp>

namespace alba {

namespace algorithm {

template <typename Key, typename Value, typename HashFunction>
class LinearProbingHashSymbolTable : public BaseLinearProbingHashSymbolTable<Key, Value, HashFunction> {};

}  // namespace algorithm

}  // namespace alba
