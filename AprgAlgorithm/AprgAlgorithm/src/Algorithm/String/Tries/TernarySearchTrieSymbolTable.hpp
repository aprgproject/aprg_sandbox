#pragma once

#include <Algorithm/String/Tries/BaseStringSymbolTable.hpp>
#include <Algorithm/String/Tries/BaseTernarySearchTrie.hpp>
#include <Algorithm/String/Tries/TernarySearchTrieNodes.hpp>

namespace alba {

namespace algorithm {

template <typename ValueTemplateType>
class TernarySearchTrieSymbolTable
    : public BaseTernarySearchTrie<
          TernarySearchTrieSymbolTableNode<ValueTemplateType>, BaseStringSymbolTable<ValueTemplateType>> {
public:
    using BaseClass = BaseTernarySearchTrie<
        TernarySearchTrieSymbolTableNode<ValueTemplateType>, BaseStringSymbolTable<ValueTemplateType>>;
    using Key = typename BaseClass::Key;
    using Strings = typename BaseClass::Strings;
    using Node = typename BaseClass::Node;
    using Value = ValueTemplateType;
    using NodeUniquePointer = std::unique_ptr<Node>;
    using ValueUniquePointer = std::unique_ptr<Value>;

    TernarySearchTrieSymbolTable() : b_root(BaseClass::m_root) {}

    Value get(Key const& key) const override {
        Value result{};
        Node const* const nodePointer(this->getStartingOnThisNode(b_root, key, 0));
        if (nodePointer != nullptr) {
            ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
            if (valueUniquePointer) {
                result = *valueUniquePointer;
            }
        }
        return result;
    }

    Strings getAllKeysWithPrefix(Key const& prefix) const override {
        Strings result;
        Node const* const firstNode(this->getStartingOnThisNode(b_root, prefix, 0));
        if (firstNode != nullptr) {
            ValueUniquePointer const& valueUniquePointer(firstNode->valueUniquePointer);
            if (valueUniquePointer) {
                result.emplace_back(prefix);
            }
            collectAllKeysAtNode(firstNode->mid.get(), std::string(prefix), result);
        }
        return result;
    }

    void put(Key const& key, Value const& value) override {
        if (!key.empty()) {
            putStartingOnThisNode(b_root, key, value, 0);
        }
    }

protected:
    virtual void putStartingOnThisNode(
        NodeUniquePointer& currentNodePointer, Key const& key, Value const& value, int const index) {
        char charAtKey(key[index]);
        if (!currentNodePointer) {
            currentNodePointer = std::make_unique<Node>(Node{charAtKey, nullptr, nullptr, nullptr, nullptr});
        }
        if (charAtKey < currentNodePointer->c) {
            putStartingOnThisNode(currentNodePointer->left, key, value, index);
        } else if (charAtKey > currentNodePointer->c) {
            putStartingOnThisNode(currentNodePointer->right, key, value, index);
        } else if (index < static_cast<int>(key.length()) - 1) {
            putStartingOnThisNode(currentNodePointer->mid, key, value, index + 1);
        } else {
            currentNodePointer->valueUniquePointer = std::make_unique<Value>(value);
        }
    }

    int getSizeStartingOnThisNode(NodeUniquePointer const& currentNodePointer) const override {
        int result(0);
        if (currentNodePointer) {
            ValueUniquePointer const& valueUniquePointer(currentNodePointer->valueUniquePointer);
            if (valueUniquePointer) {
                result++;
            }
            result += getSizeStartingOnThisNode(currentNodePointer->left);
            result += getSizeStartingOnThisNode(currentNodePointer->right);
            result += getSizeStartingOnThisNode(currentNodePointer->mid);
        }
        return result;
    }

    int getLengthOfLongestPrefixStartingOnThisNode(
        NodeUniquePointer const& currentNodePointer, Key const& keyToCheck, int const index) const override {
        if (currentNodePointer && index < static_cast<int>(keyToCheck.length())) {
            char c(keyToCheck[index]);
            if (c < currentNodePointer->c) {
                return getLengthOfLongestPrefixStartingOnThisNode(currentNodePointer->left, keyToCheck, index);
            } else if (c > currentNodePointer->c) {
                return getLengthOfLongestPrefixStartingOnThisNode(currentNodePointer->right, keyToCheck, index);
            } else {
                int lengthWithValue = 0;
                if (currentNodePointer->valueUniquePointer) {
                    lengthWithValue = index + 1;
                }
                return std::max(
                    lengthWithValue,
                    getLengthOfLongestPrefixStartingOnThisNode(currentNodePointer->mid, keyToCheck, index + 1));
            }
        } else if (index == static_cast<int>(keyToCheck.length())) {
            return index;
        }
        return 0;
    }

    void collectAllKeysAtNode(
        Node const* const currentNodePointer, std::string const& previousPrefix,
        Strings& collectedKeys) const override {
        if (currentNodePointer != nullptr) {
            ValueUniquePointer const& valueUniquePointer(currentNodePointer->valueUniquePointer);
            collectAllKeysAtNode(currentNodePointer->left.get(), previousPrefix, collectedKeys);
            std::string currentPrefix(previousPrefix + currentNodePointer->c);
            if (valueUniquePointer) {
                collectedKeys.emplace_back(currentPrefix);
            }
            collectAllKeysAtNode(currentNodePointer->mid.get(), currentPrefix, collectedKeys);
            collectAllKeysAtNode(currentNodePointer->right.get(), previousPrefix, collectedKeys);
        }
    }

    void collectKeysThatMatchAtNode(
        Node const* const currentNodePointer, std::string const& previousPrefix, Key const& patternToMatch,
        Strings& collectedKeys) const override {
        if (currentNodePointer != nullptr) {
            int previousPrefixLength = previousPrefix.length();
            int lastIndexToMatch = patternToMatch.length() - 1;
            char currentChar = currentNodePointer->c;
            char charToMatch = patternToMatch[previousPrefixLength];
            std::string currentPrefix(previousPrefix + currentNodePointer->c);
            if (charToMatch < currentChar) {
                collectKeysThatMatchAtNode(
                    currentNodePointer->left.get(), previousPrefix, patternToMatch, collectedKeys);
            } else if (charToMatch > currentChar) {
                collectKeysThatMatchAtNode(
                    currentNodePointer->right.get(), previousPrefix, patternToMatch, collectedKeys);
            } else {  // if (charToMatch == currentChar)
                if (previousPrefixLength < lastIndexToMatch) {
                    collectKeysThatMatchAtNode(
                        currentNodePointer->mid.get(), currentPrefix, patternToMatch, collectedKeys);
                } else if (previousPrefixLength == lastIndexToMatch && currentNodePointer->valueUniquePointer) {
                    collectedKeys.emplace_back(currentPrefix);
                }
            }
            if (charToMatch == '.') {
                if (previousPrefixLength < lastIndexToMatch) {
                    collectKeysThatMatchAtNode(
                        currentNodePointer->mid.get(), currentPrefix, patternToMatch, collectedKeys);
                } else if (previousPrefixLength == lastIndexToMatch && currentNodePointer->valueUniquePointer) {
                    collectedKeys.emplace_back(currentPrefix);
                }
            }
        }
    }

    void deleteBasedOnKeyStartingOnThisNode(
        NodeUniquePointer& currentNodePointer, Key const& key, int const index) override {
        if (currentNodePointer) {
            int lastIndex = key.length() - 1;
            ValueUniquePointer& valueUniquePointer(currentNodePointer->valueUniquePointer);
            if (index < lastIndex) {
                char charAtKey(key[index]);
                if (charAtKey < currentNodePointer->c) {
                    deleteBasedOnKeyStartingOnThisNode(currentNodePointer->left, key, index);
                } else if (charAtKey > currentNodePointer->c) {
                    deleteBasedOnKeyStartingOnThisNode(currentNodePointer->right, key, index);
                } else {
                    deleteBasedOnKeyStartingOnThisNode(currentNodePointer->mid, key, index + 1);
                }
            } else if (index == lastIndex) {
                valueUniquePointer.reset();
            }
            if (!currentNodePointer->valueUniquePointer && !currentNodePointer->mid) {
                if (!currentNodePointer->left && !currentNodePointer->right) {
                    currentNodePointer.reset();
                } else if (currentNodePointer->left && !currentNodePointer->right) {
                    currentNodePointer = std::move(currentNodePointer->left);
                } else if (!currentNodePointer->left && currentNodePointer->right) {
                    currentNodePointer = std::move(currentNodePointer->right);
                } else {
                    currentNodePointer->mid = std::move(currentNodePointer->right);
                }
            }
        }
    }

    NodeUniquePointer& b_root;
};

}  // namespace algorithm

}  // namespace alba
