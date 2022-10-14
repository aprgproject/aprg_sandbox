#pragma once

#include <Algorithm/SymbolTable/HashTable/Common/BaseLinearProbingHashSymbolTable.hpp>

namespace alba
{
namespace algorithm
{

template <typename Key, typename Value, typename HashFunction>
class LinearProbingHashSymbolTable
        : public BaseLinearProbingHashSymbolTable<Key, Value, HashFunction>
{
};

}

}