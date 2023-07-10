#pragma once

#include <Algorithm/String/Tries/BaseStringSet.hpp>
#include <Algorithm/String/Tries/BaseTernarySearchTrie.hpp>
#include <Algorithm/String/Tries/TernarySearchTrieNodes.hpp>

namespace alba {

namespace algorithm {

class TernarySearchTrieSubstringsSet : public BaseTernarySearchTrie<TernarySearchTrieSetNode, BaseStringSet> {
public:
    using BaseClass = BaseTernarySearchTrie<TernarySearchTrieSetNode, BaseStringSet>;
    using Key = typename BaseClass::Key;
    using Keys = typename BaseClass::Keys;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = std::unique_ptr<Node>;

    TernarySearchTrieSubstringsSet() : b_root(BaseClass::m_root) {}

    void put(Key const& key) override {
        if (!key.empty()) {
            putStartingOnThisNode(b_root, key, 0);
        }
    }

    Keys getAllKeysWithPrefix(Key const& prefix) const override {
        Keys result;
        Node const* const firstNode(this->getStartingOnThisNode(b_root, prefix, 0));
        if (firstNode != nullptr) {
            result.emplace_back(prefix);
            collectAllKeysAtNode(firstNode->mid.get(), prefix, result);
        }
        return result;
    }

protected:
    int getSizeStartingOnThisNode(NodeUniquePointer const& currentNodePointer) const override {
        int result(0);
        if (currentNodePointer) {
            result++;
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
                return getLengthOfLongestPrefixStartingOnThisNode(currentNodePointer->mid, keyToCheck, index + 1);
            }
        }
        return index;
    }

    void collectAllKeysAtNode(
        Node const* const currentNodePointer, Key const& previousPrefix, Keys& collectedKeys) const override {
        if (currentNodePointer != nullptr) {
            collectAllKeysAtNode(currentNodePointer->left.get(), previousPrefix, collectedKeys);
            Key currentPrefix(previousPrefix + currentNodePointer->c);
            collectedKeys.emplace_back(currentPrefix);
            collectAllKeysAtNode(currentNodePointer->mid.get(), currentPrefix, collectedKeys);
            collectAllKeysAtNode(currentNodePointer->right.get(), previousPrefix, collectedKeys);
        }
    }

    void collectKeysThatMatchAtNode(
        Node const* const currentNodePointer, Key const& previousPrefix, Key const& patternToMatch,
        Keys& collectedKeys) const override {
        if (currentNodePointer != nullptr) {
            int previousPrefixLength = previousPrefix.length();
            int lastIndexToMatch = patternToMatch.length() - 1;
            char currentChar = currentNodePointer->c;
            char charToMatch = patternToMatch[previousPrefixLength];
            Key currentPrefix(previousPrefix + currentNodePointer->c);
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
                } else if (previousPrefixLength == lastIndexToMatch) {
                    collectedKeys.emplace_back(currentPrefix);
                }
            }
            if (charToMatch == '.') {
                if (previousPrefixLength < lastIndexToMatch) {
                    collectKeysThatMatchAtNode(
                        currentNodePointer->mid.get(), currentPrefix, patternToMatch, collectedKeys);
                } else if (previousPrefixLength == lastIndexToMatch) {
                    collectedKeys.emplace_back(currentPrefix);
                }
            }
        }
    }

    void deleteBasedOnKeyStartingOnThisNode(
        NodeUniquePointer& currentNodePointer, Key const& key, int const index) override {
        if (currentNodePointer) {
            int lastIndex = key.length() - 1;
            if (index < lastIndex) {
                char charAtKey(key[index]);
                if (charAtKey < currentNodePointer->c) {
                    deleteBasedOnKeyStartingOnThisNode(currentNodePointer->left, key, index);
                } else if (charAtKey > currentNodePointer->c) {
                    deleteBasedOnKeyStartingOnThisNode(currentNodePointer->right, key, index);
                } else {
                    deleteBasedOnKeyStartingOnThisNode(currentNodePointer->mid, key, index + 1);
                }
            }
            if (!currentNodePointer->mid) {
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

    void putStartingOnThisNode(NodeUniquePointer& currentNodePointer, Key const& key, int const index) {
        char charAtKey(key[index]);
        if (!currentNodePointer) {
            currentNodePointer = std::make_unique<Node>(Node{charAtKey, nullptr, nullptr, nullptr});
        }
        if (charAtKey < currentNodePointer->c) {
            putStartingOnThisNode(currentNodePointer->left, key, index);
        } else if (charAtKey > currentNodePointer->c) {
            putStartingOnThisNode(currentNodePointer->right, key, index);
        } else if (index < static_cast<int>(key.length()) - 1) {
            putStartingOnThisNode(currentNodePointer->mid, key, index + 1);
        }
    }

    NodeUniquePointer& b_root;
};

}  // namespace algorithm

}  // namespace alba
