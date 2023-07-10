#pragma once

#include <memory>

namespace alba {

namespace algorithm {

struct TernarySearchTrieSetNode {
    char c;
    std::unique_ptr<TernarySearchTrieSetNode> left;
    std::unique_ptr<TernarySearchTrieSetNode> mid;
    std::unique_ptr<TernarySearchTrieSetNode> right;
};

template <typename Value>
struct TernarySearchTrieSymbolTableNode {
    char c;
    std::unique_ptr<TernarySearchTrieSymbolTableNode> left;
    std::unique_ptr<TernarySearchTrieSymbolTableNode> mid;
    std::unique_ptr<TernarySearchTrieSymbolTableNode> right;
    std::unique_ptr<Value> valueUniquePointer;
};

}  // namespace algorithm

}  // namespace alba
