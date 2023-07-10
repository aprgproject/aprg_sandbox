#pragma once

#include <string_view>
#include <vector>

namespace alba {
namespace algorithm {

class BaseStringSet {
public:
    using Key = std::string_view;
    using Strings = std::vector<std::string>;

    virtual ~BaseStringSet() = default;  // virtual destructor because of virtual functions (vtable exists)
    virtual bool isEmpty() const = 0;                    // is the symbol table empty
    virtual bool doesContain(Key const& key) const = 0;  // is key exists on symbol table
    virtual int getSize() const = 0;                                  // get number of key-value pairs
    virtual Key getLongestPrefixOf(Key const& keyToCheck) const = 0;  // get the longest key that has a prefix

    virtual void put(Key const& key) = 0;               // put key-value pair
    virtual void deleteBasedOnKey(Key const& key) = 0;  // remove key (and its value) from the symbol table

    virtual Strings getKeys() const = 0;                                       // get all keys in sorted order
    virtual Strings getAllKeysWithPrefix(Key const& prefix) const = 0;         // all the keys having s as a prefix
    virtual Strings getAllKeysThatMatch(Key const& patternToMatch) const = 0;  // all the keys having s as a prefix
};

}  // namespace algorithm
}  // namespace alba

// Can we do better than generic symbol tables?// Yes, if we can avoid examining the entrie key, as with string sorting.
// So create a specialized string symbol table

// Applications:
// Character based operations
// -> Prefix match
// -> Wildcard match
// -> Longest prefix
