#pragma once

#include <Algorithm/String/Tries/TernarySearchTrieSymbolTable.hpp>

namespace alba {

namespace algorithm {

class TernarySearchSuffixTrie : protected TernarySearchTrieSymbolTable<int> {
public:
    using BaseClass = TernarySearchTrieSymbolTable<int>;
    using Key = typename BaseClass::Key;
    using Node = typename BaseClass::Node;
    using Value = typename BaseClass::Value;

    TernarySearchSuffixTrie(Key const& searchSpace) { initialize(searchSpace); }

    Value getIndexOfFirstOccurrence(Key const& key) const { return get(key); }

protected:
    void initialize(Key const& searchSpace) {
        int length = searchSpace.length();
        for (int i = 0; i < length; i++) {
            TernarySearchSuffixTrie::put(searchSpace.substr(i), i);
        }
    }

    Value get(Key const& key) const override {
        Value result(-1);  // assign negative one if not found
        Node const* const nodePointer(this->getStartingOnThisNode(b_root, key, 0));
        if (nodePointer != nullptr) {
            ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
            if (valueUniquePointer) {
                result = *valueUniquePointer;
            }
        }
        return result;
    }

    void put(Key const& key, Value const& value) override {
        if (!key.empty()) {
            TernarySearchSuffixTrie::putStartingOnThisNode(b_root, key, value, 0);
        }
    }

    void putStartingOnThisNode(
        NodeUniquePointer& currentNodePointer, Key const& key, Value const& value, int const index) override {
        char charAtKey(key[index]);
        if (!currentNodePointer) {
            currentNodePointer = std::make_unique<Node>(Node{charAtKey, nullptr, nullptr, nullptr, nullptr});
        }
        if (charAtKey < currentNodePointer->c) {
            TernarySearchSuffixTrie::putStartingOnThisNode(currentNodePointer->left, key, value, index);
        } else if (charAtKey > currentNodePointer->c) {
            TernarySearchSuffixTrie::putStartingOnThisNode(currentNodePointer->right, key, value, index);
        } else if (index < static_cast<int>(key.length()) - 1) {
            TernarySearchSuffixTrie::putStartingOnThisNode(currentNodePointer->mid, key, value, index + 1);
        }
        if (!currentNodePointer->valueUniquePointer) {
            currentNodePointer->valueUniquePointer = std::make_unique<Value>(value);
        }
    }
};

}  // namespace algorithm

}  // namespace alba
