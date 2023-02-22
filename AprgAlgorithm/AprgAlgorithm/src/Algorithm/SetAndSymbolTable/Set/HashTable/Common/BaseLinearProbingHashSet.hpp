#pragma once

#include <Algorithm/SetAndSymbolTable/Common/HashTable/BaseLinearProbingHash.hpp>
#include <Algorithm/SetAndSymbolTable/Common/HashTable/HashTableEntry.hpp>
#include <Algorithm/SetAndSymbolTable/Set/Array/OrderedArraySet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/HashTable/Common/BaseSetWithBaseLinearProbingHash.hpp>

namespace alba
{

namespace algorithm
{

template <typename Key, typename HashFunction>
class BaseLinearProbingHashSet
        : public BaseSetWithBaseLinearProbingHash<BaseLinearProbingHash<Key, HashTableEntry<Key>, HashFunction, OrderedArraySet<Key>, BaseSet<Key>>>
{
public:
    ~BaseLinearProbingHashSet() override = default; // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
};

}

}
