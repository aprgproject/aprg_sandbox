#pragma once

#include <Algorithm/String/Tries/BaseStringSymbolTable.hpp>

#include <algorithm>
#include <array>
#include <memory>
#include <vector>

namespace alba {

namespace algorithm {

template <typename Value>
class RWayTrieUsingLinkedArrays : public BaseStringSymbolTable<Value> {
public:
    static constexpr int RADIX = 256;
    using BaseClass = BaseStringSymbolTable<Value>;
    using Key = typename BaseClass::Key;
    using Strings = typename BaseClass::Strings;
    using ValueUniquePointer = std::unique_ptr<Value>;
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node {
        ValueUniquePointer valueUniquePointer;
        std::array<NodeUniquePointer, RADIX> next;  // costly
    };

    RWayTrieUsingLinkedArrays() : m_root(nullptr) {}

    bool isEmpty() const override { return getSize() == 0; }

    bool doesContain(Key const& key) const override {
        Node const* const nodePointer(get(m_root, key, 0));
        return nodePointer != nullptr;
    }

    int getSize() const override { return getSize(m_root); }

    int getNumberOfNodes() const { return getNumberOfNodes(m_root); }

    Value get(Key const& key) const override {
        Value result{};
        Node const* const nodePointer(get(m_root, key, 0));
        if (nodePointer != nullptr) {
            ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
            if (valueUniquePointer) {
                result = *valueUniquePointer;
            }
        }
        return result;
    }

    Key getLongestPrefixOf(Key const& keyToCheck) const override {
        int longestPrefixLength(getLengthOfLongestPrefix(m_root.get(), keyToCheck, 0, 0));
        return keyToCheck.substr(0, longestPrefixLength);
    }

    void put(Key const& key, Value const& value) override { put(m_root, key, value, 0); }

    void deleteBasedOnKey(Key const& key) override { deleteBasedOnKeyAndReturnIfDeleted(m_root, key, 0); }

    Strings getKeys() const override { return getAllKeysWithPrefix(std::string()); }

    Strings getAllKeysWithPrefix(Key const& prefix) const override {
        Strings result;
        collectAllKeysAtNode(get(m_root, prefix, 0), std::string(prefix), result);
        return result;
    }

    Strings getAllKeysThatMatch(Key const& patternToMatch) const override {
        Strings result;
        collectKeysThatMatchAtNode(m_root.get(), std::string(), patternToMatch, result);
        return result;
    }

private:
    bool isEmptyNode(NodeUniquePointer const& currentNodePointer) {
        return !currentNodePointer->valueUniquePointer &&
               std::all_of(
                   currentNodePointer->next.cbegin(), currentNodePointer->next.cend(),
                   [](NodeUniquePointer const& nodePointer) { return !nodePointer; });
    }

    int getSize(NodeUniquePointer const& currentNodePointer) const {
        int result(0);
        if (currentNodePointer) {
            ValueUniquePointer const& valueUniquePointer(currentNodePointer->valueUniquePointer);
            if (valueUniquePointer) {
                result++;
            }
            for (int c = 0; c < RADIX; c++) {
                result += getSize(currentNodePointer->next[c]);
            }
        }
        return result;
    }

    int getNumberOfNodes(NodeUniquePointer const& currentNodePointer) const {
        int result(0);
        if (currentNodePointer) {
            result++;
            for (int c = 0; c < RADIX; c++) {
                result += getNumberOfNodes(currentNodePointer->next[c]);
            }
        }
        return result;
    }

    Node const* get(NodeUniquePointer const& currentNodePointer, Key const& key, int const index) const {
        Node const* result(nullptr);
        if (currentNodePointer) {
            if (index == static_cast<int>(key.length())) {
                result = currentNodePointer.get();
            } else {
                result = get(currentNodePointer->next[key[index]], key, index + 1);
            }
        }
        return result;
    }

    int getLengthOfLongestPrefix(
        Node const* const currentNodePointer, Key const& keyToCheck, int const index, int const length) const {
        int currentLongestLength(length);
        if (currentNodePointer != nullptr) {
            if (currentNodePointer->valueUniquePointer) {
                currentLongestLength = index;
            }
            if (index < static_cast<int>(keyToCheck.length())) {
                char c = keyToCheck[index];
                currentLongestLength = getLengthOfLongestPrefix(
                    currentNodePointer->next[c].get(), keyToCheck, index + 1, currentLongestLength);
            }
        }
        return currentLongestLength;
    }

    void collectAllKeysAtNode(
        Node const* const currentNodePointer, std::string const& previousPrefix, Strings& collectedKeys) const {
        if (currentNodePointer != nullptr) {
            ValueUniquePointer const& valueUniquePointer(currentNodePointer->valueUniquePointer);
            if (valueUniquePointer) {
                collectedKeys.emplace_back(previousPrefix);
            }
            for (int c = 0; c < RADIX; c++) {
                collectAllKeysAtNode(
                    currentNodePointer->next[c].get(), previousPrefix + static_cast<char>(c), collectedKeys);
            }
        }
    }

    void collectKeysThatMatchAtNode(
        Node const* const currentNodePointer, std::string const& previousPrefix, Key const& patternToMatch,
        Strings& collectedKeys) const {
        if (currentNodePointer != nullptr) {
            int prefixLength = previousPrefix.length();
            if (prefixLength == static_cast<int>(patternToMatch.length()) && currentNodePointer->valueUniquePointer) {
                collectedKeys.emplace_back(previousPrefix);
            } else if (prefixLength < static_cast<int>(patternToMatch.length())) {
                char charToMatch = patternToMatch[prefixLength];
                for (int c = 0; c < RADIX; c++) {
                    if ('.' == charToMatch || charToMatch == static_cast<char>(c)) {
                        collectKeysThatMatchAtNode(
                            currentNodePointer->next[c].get(), previousPrefix + static_cast<char>(c), patternToMatch,
                            collectedKeys);
                    }
                }
            }
        }
    }

    void put(NodeUniquePointer& currentNodePointer, Key const& key, Value const& value, int const index) {
        if (!currentNodePointer) {
            currentNodePointer = std::make_unique<Node>();
        }
        if (index == static_cast<int>(key.length())) {
            currentNodePointer->valueUniquePointer = std::make_unique<Value>(value);
        } else {
            put(currentNodePointer->next[key[index]], key, value, index + 1);
        }
    }

    bool deleteBasedOnKeyAndReturnIfDeleted(NodeUniquePointer& currentNodePointer, Key const& key, int const index) {
        bool isDeleted(false);
        if (currentNodePointer) {
            ValueUniquePointer& valueUniquePointer(currentNodePointer->valueUniquePointer);
            if (index == static_cast<int>(key.length())) {
                valueUniquePointer.reset();
                if (isEmptyNode(currentNodePointer)) {
                    currentNodePointer.reset();
                    isDeleted = true;
                }
            } else {
                bool isASingleNextDeleted =
                    deleteBasedOnKeyAndReturnIfDeleted(currentNodePointer->next[key[index]], key, index + 1);
                if (isASingleNextDeleted && isEmptyNode(currentNodePointer)) {
                    currentNodePointer.reset();
                    isDeleted = true;
                }
            }
        }
        return isDeleted;
    }

    NodeUniquePointer m_root;
};

}  // namespace algorithm

}  // namespace alba

// Tries
// -> From the word re[trie]val, but pronounced "try"
// ---> For now, store character in nodes, (not keys)
// ---> Each node has R children, on for each possible character.
// ---> Store values in nodes corresponding to last character in keys.
// -----> so only the last character has the value for the key

// Search in a trie
// -> Follow the links corresponding to each character in the key.
// ---> Search hit: node where search ends has a non-null values.
// ---> Seach miss: reach null or node where search end has null value.

// Insertion into a trie
// -> Follow links corresponding to each character in the key.
// ---> Encounter a null link: create a new node
// ---> Encounter the last character of the key: set value in that node

// Node: A value, plus references to R nodes
// -> Neither keys nor characters are not explicitly stored
// -> characters are implicitly defined by link index
// -> each node has an array of links and a value

// Trie Performance
// -> Search hit: Need to examine all L characters for equality. (linear)
// -> Search miss: Could have mismatch on first character
// ---> Typical case: examine only a few characters (sublinear)

// Space
// R null links at each leaf. -> Costly
// -> but sublinear space possible if many short string share common prefixes

// Bottom line: Fast search hit and even faster search miss, but wastes space.

// Interview question: Design a data structure to perform efficient spell checking
// -> Solution build a 26-way trie (key=word, value=bit)

// Deletion in an R-way trie
// -> Find the node corresponding to key and set value to null
// -> If the node has all null link, remove that node (and recur)

// R-way trie
// -> Method of choice for small R.
// -> Too much memory for large R.
// Challenge: Use less memory e.g. 65536-way trie for Unicode!

// Longest prefix in an R-way trie
// -> Find longest key in symbol table that is a prefix of query string.
// ---> Search for query string
// ---> Keep track of longest key encountered
