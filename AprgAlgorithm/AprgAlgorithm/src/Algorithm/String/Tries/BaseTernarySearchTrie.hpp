#pragma once

#include <memory>
#include <vector>

namespace alba {

namespace algorithm {

template <typename NodeTemplateType, typename BaseDataStructure>
class BaseTernarySearchTrie : public BaseDataStructure {
public:
    using BaseClass = BaseDataStructure;
    using Key = typename BaseClass::Key;
    using Strings = typename BaseClass::Strings;
    using Node = NodeTemplateType;
    using NodeUniquePointer = std::unique_ptr<Node>;

    BaseTernarySearchTrie() : m_root(nullptr) {}

    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
    ~BaseTernarySearchTrie() override = default;

    bool isEmpty() const override { return getSize() == 0; }

    bool doesContain(Key const& key) const override {
        Node const* const nodePointer(getStartingOnThisNode(m_root, key, 0));
        return nodePointer != nullptr;
    }

    int getSize() const override { return getSizeStartingOnThisNode(m_root); }

    int getNumberOfNodes() const {
        return getNumberOfNodes(m_root);  // dont count the root pointer
    }

    Key getLongestPrefixOf(Key const& keyToCheck) const override {
        int longestPrefixLength(getLengthOfLongestPrefixStartingOnThisNode(m_root, keyToCheck, 0));
        return keyToCheck.substr(0, longestPrefixLength);
    }

    void deleteBasedOnKey(Key const& key) override { deleteBasedOnKeyStartingOnThisNode(m_root, key, 0); }

    Strings getKeys() const override {
        Strings result;
        collectAllKeysAtNode(m_root.get(), std::string(), result);
        return result;
    }

    Strings getAllKeysThatMatch(Key const& patternToMatch) const override {
        Strings result;
        collectKeysThatMatchAtNode(m_root.get(), std::string(), patternToMatch, result);
        return result;
    }

protected:
    virtual int getSizeStartingOnThisNode(NodeUniquePointer const& currentNodePointer) const = 0;
    virtual int getLengthOfLongestPrefixStartingOnThisNode(
        NodeUniquePointer const& currentNodePointer, Key const& keyToCheck, int const index) const = 0;
    virtual void collectAllKeysAtNode(
        Node const* const currentNodePointer, std::string const& previousPrefix, Strings& collectedKeys) const = 0;
    virtual void collectKeysThatMatchAtNode(
        Node const* const currentNodePointer, std::string const& previousPrefix, Key const& patternToMatch,
        Strings& collectedKeys) const = 0;
    virtual void deleteBasedOnKeyStartingOnThisNode(
        NodeUniquePointer& currentNodePointer, Key const& key, int const index) = 0;

    int getNumberOfNodes(NodeUniquePointer const& currentNodePointer) const {
        int result(0);
        if (currentNodePointer) {
            result++;
            result += getNumberOfNodes(currentNodePointer->left);
            result += getNumberOfNodes(currentNodePointer->right);
            result += getNumberOfNodes(currentNodePointer->mid);
        }
        return result;
    }

    Node const* getStartingOnThisNode(
        NodeUniquePointer const& currentNodePointer, Key const& key, int const index) const {
        Node const* result(nullptr);
        if (currentNodePointer && index < static_cast<int>(key.length())) {
            char c(key[index]);
            if (c < currentNodePointer->c) {
                result = getStartingOnThisNode(currentNodePointer->left, key, index);  // search left
            } else if (c > currentNodePointer->c) {
                result = getStartingOnThisNode(currentNodePointer->right, key, index);  // search right
            } else if (index < static_cast<int>(key.length()) - 1) {
                result = getStartingOnThisNode(
                    currentNodePointer->mid, key, index + 1);  // only advance index when character is a match
            } else {
                result = currentNodePointer.get();
            }
        }
        return result;
    }

    NodeUniquePointer m_root;
};

}  // namespace algorithm

}  // namespace alba

// Ternary search tries
// -> Store characters and values in nodes (not keys)
// -> Each node has 3 children: smaller (left), equal (middle), larger (right)
// ---> left: Link to TST for all keys that start with a letter before s
// ---> middle: Link to TST for all keys that start with a letter s
// ---> right: Link to TST for all keys that start with a letter after s

// almost like a binary search tree

// Search in a TST
// -> Follow links corresponding to each character in the key.
// ---> If less, take left link
// ---> if greater, take the right link
// ---> If equal, take the middle link and move to the next key character.
// -> Search hit. Node where search ends has a non-null value.
// -> Search miss. Reach a null link or node where search ends has null value.
