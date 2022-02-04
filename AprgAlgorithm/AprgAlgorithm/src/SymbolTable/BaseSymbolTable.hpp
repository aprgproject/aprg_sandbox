#pragma once

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value>
class BaseSymbolTable
{public:
    using Keys = std::vector<Key>;

    virtual ~BaseSymbolTable()    {}

    virtual bool isEmpty() const = 0; // is the symbol table empty
    virtual bool doesContain(Key const& key) const = 0; // is key exists on symbol table

    virtual unsigned int getSize() const = 0; // get number of key-value pairs
    virtual unsigned int getRank(Key const& key) const = 0; // get number of keys less than key

    virtual Value get(Key const& key) const = 0; // get value paired with key

    virtual Key getMinimum() const = 0; // get smallest key
    virtual Key getMaximum() const = 0; // get largest key
    virtual Key selectAt(unsigned int const rank) const = 0; // get key at rank
    virtual Key getFloor(Key const& key) const = 0; // get largest key less than or equal to key
    virtual Key getCeiling(Key const& key) const = 0; // get smallest key greater than or equal to key

    virtual void put(Key const& key, Value const& value) = 0; // put key-value pair
    virtual void deleteBasedOnKey(Key const& key) = 0; // remove key (and its value) from the symbol table
    virtual void deleteMinimum() = 0; // remove smallest key (and its value) from the symbol table
    virtual void deleteMaximum() = 0; // remove largest key (and its value) from the symbol table

    virtual Keys getKeys() const = 0; // get all keys in sorted order
    virtual Keys getKeysInRangeInclusive(Key const& low, Key const& high) const = 0; // get all keys that fall in range in sorted order
};

}

}