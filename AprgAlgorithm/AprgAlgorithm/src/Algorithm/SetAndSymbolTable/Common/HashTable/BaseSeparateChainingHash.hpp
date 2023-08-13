#pragma once

#include <Algorithm/SetAndSymbolTable/SymbolTable/Array/OrderedArraySymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/LinkedList/UnorderedLinkedListSymbolTable.hpp>
#include <Algorithm/Sort/MergeSorter/MergeSorterUtilities.hpp>

#include <array>
#include <memory>

namespace alba {
namespace algorithm {

template <
    typename KeyTemplateType, typename EntryTemplateType, typename HashFunction, int HASH_TABLE_SIZE,
    typename OrderedArray, typename UnorderedLinkedList, typename BaseDataStructure>
class BaseSeparateChainingHash : public BaseDataStructure {
public:
    using Key = KeyTemplateType;
    using Entry = EntryTemplateType;
    using Keys = std::vector<Key>;
    using HashTable = std::array<UnorderedLinkedList, HASH_TABLE_SIZE>;

    BaseSeparateChainingHash() : m_size(0) {}

    ~BaseSeparateChainingHash() override = default;  // no need for virtual destructor because base destructor is
                                                     // virtual (similar to other virtual functions)

    bool isEmpty() const override { return m_size == 0; }

    bool doesContain(Key const& key) const override { return m_smallerSymbolTables[getHash(key)].doesContain(key); }

    int getSize() const override { return m_size; }

    int getRank(Key const& key) const override {
        Keys keys(getKeys());
        return OrderedArray::getRank(key, keys);
    }

    Key getMinimum() const override {
        Key result{};
        bool isFirst(true);
        for (auto const& smallerSymbolTables : m_smallerSymbolTables) {
            if (!smallerSymbolTables.isEmpty()) {
                if (isFirst) {
                    result = smallerSymbolTables.getMinimum();
                    isFirst = false;
                } else {
                    result = std::min(result, smallerSymbolTables.getMinimum());
                }
            }
        }
        return result;
    }

    Key getMaximum() const override {
        Key result;
        bool isFirst(true);
        for (auto const& smallerSymbolTables : m_smallerSymbolTables) {
            if (!smallerSymbolTables.isEmpty()) {
                if (isFirst) {
                    result = smallerSymbolTables.getMaximum();
                    isFirst = false;
                } else {
                    result = std::max(result, smallerSymbolTables.getMaximum());
                }
            }
        }
        return result;
    }

    Key selectAt(int const index) const override {
        Keys keys(getKeys());
        return OrderedArray::selectAt(index, keys);
    }

    Key getFloor(Key const& key) const override {
        Keys keys(getKeys());
        return OrderedArray::getFloor(key, keys);
    }

    Key getCeiling(Key const& key) const override {
        Keys keys(getKeys());
        return OrderedArray::getCeiling(key, keys);
    }

    void deleteBasedOnKey(Key const& key) override {
        m_smallerSymbolTables[getHash(key)].deleteBasedOnKey(key);
        m_size--;
    }

    void deleteMinimum() override { deleteBasedOnKey(getMinimum()); }

    void deleteMaximum() override { deleteBasedOnKey(getMaximum()); }

    Keys getKeys() const override {
        Keys result;
        for (auto const& smallerSymbolTables : m_smallerSymbolTables) {
            if (!smallerSymbolTables.isEmpty()) {
                result = mergeTwoSortedSequences(result, smallerSymbolTables.getKeys());
            }
        }
        return result;
    }

    Keys getKeysInRangeInclusive(Key const& low, Key const& high) const override {
        Keys result;
        for (auto const& smallerSymbolTables : m_smallerSymbolTables) {
            if (!smallerSymbolTables.isEmpty()) {
                result = mergeTwoSortedSequences(result, smallerSymbolTables.getKeysInRangeInclusive(low, high));
            }
        }
        return result;
    }

protected:
    int getHash(Key const& key) const { return HashFunction::getHash(key); }

    int m_size;
    HashTable m_smallerSymbolTables;
};

// Approach: use an array of M<N linked lists. H. P. Luhn IBM 1953.

// Proposition. Under uniform hashing assumption, probability that the number of keys in a list is within a constant
// factor of N/M is extremely close to 1 Note: N is the number of items, M is the hash table size Proof sketch:
// Distribution of list size obeys a binomial distribution.

// Consequence. Number of probes (getting hash and check if equal) for search/insert is proportional to N/M
// -> M is too large -> too many empty chains.
// -> M is too small -> chains are too long.
// -> Typical choice: M ~ N/5 -> constant time operation on average

// Improved version: Two probe hashing (separate chaining variant)
// -> Hash to two positions, insert key in shorter of the two chains
// -> Reduces expected length of the longest chain to log log N

}  // namespace algorithm

}  // namespace alba
