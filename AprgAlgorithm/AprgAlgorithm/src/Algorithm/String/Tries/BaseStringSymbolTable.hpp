#pragma once

#include <Common/String/AlbaStringHelper.hpp>

#include <string>

namespace alba
{

namespace algorithm
{

template <typename Value>
class BaseStringSymbolTable
{
public:
    using Key = std::string;
    using Keys = stringHelper::strings;

    virtual ~BaseStringSymbolTable() = default;

    virtual bool isEmpty() const = 0; // is the symbol table empty
    virtual bool doesContain(Key const& key) const = 0; // is key exists on symbol table

    virtual unsigned int getSize() const = 0; // get number of key-value pairs
    virtual Value get(Key const& key) const = 0; // get value paired with key
    virtual Key getLongestPrefixOf(Key const& keyToCheck) const = 0; // get the longest key that has a prefix

    virtual void put(Key const& key, Value const& value) = 0; // put key-value pair
    virtual void deleteBasedOnKey(Key const& key) = 0; // remove key (and its value) from the symbol table

    virtual Keys getKeys() const = 0; // get all keys in sorted order
    virtual Keys getAllKeysWithPrefix(Key const& prefix) const = 0; // all the keys having s as a prefix
    virtual Keys getAllKeysThatMatch(Key const& patternToMatch) const = 0; // all the keys having s as a prefix
};

// Can we do better than generic symbol tables?
// Yes, if we can avoid examining the entrie key, as with string sorting.
// So create a specialized string symbol table

// Applications:
// Character based operations
// -> Prefix match
// -> Wildcard match
// -> Longest prefix



}

}
