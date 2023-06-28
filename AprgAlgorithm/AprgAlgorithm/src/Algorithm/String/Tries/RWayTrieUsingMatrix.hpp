#pragma once

#include <Algorithm/String/Tries/BaseStringSymbolTable.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <set>

namespace alba {

namespace algorithm {

template <typename Value, int MAX_NUMBER_NODES>
class RWayTrieUsingMatrix : public BaseStringSymbolTable<Value> {
public:
    static constexpr int RADIX = 256;
    static constexpr int INVALID_NODE_ID = MAX_NUMBER_NODES;
    using Key = std::string;
    using Keys = stringHelper::strings;
    using NodeId = int;
    using SetOfNodeIds = std::set<NodeId>;
    using ValueUniquePointer = std::unique_ptr<Value>;
    struct Node {
        NodeId nextNodeId;
        ValueUniquePointer valueUniquePointer;
    };
    using NodePointer = std::unique_ptr<Node>;
    using NodePointerMatrix = matrix::AlbaMatrix<NodePointer>;
    using Coordinate = std::pair<int, NodeId>;
    using Coordinates = std::vector<Coordinate>;

    RWayTrieUsingMatrix()
        : m_size(0), m_nextNodeId(0), m_unusedNodeIds(), m_nodePointerMatrix(RADIX, MAX_NUMBER_NODES) {}

    bool isEmpty() const override { return m_size == 0; }

    bool doesContain(Key const& key) const override { return static_cast<bool>(getValuePointer(0, key, 0)); }

    int getSize() const override { return m_size; }

    Value get(Key const& key) const override {
        Value result{};
        ValueUniquePointer valueUniquePointer(getValuePointer(0, key, 0));
        if (valueUniquePointer) {
            result = *valueUniquePointer;
        }
        return result;
    }

    Key getLongestPrefixOf(Key const& keyToCheck) const override {
        int longestPrefixLength(getLengthOfLongestPrefix(0, keyToCheck, 0));
        return keyToCheck.substr(0, longestPrefixLength);
    }

    void put(Key const& key, Value const& value) override { put(0, key, value, 0); }

    void deleteBasedOnKey(Key const& key) override { deleteBasedOnKeyAndReturnIfDeleted(0, key, 0); }

    Keys getKeys() const override {
        Keys result;
        collectAllKeysAtNode(0, std::string(), result);
        return result;
    }

    Keys getAllKeysWithPrefix(Key const& prefix) const override {
        Keys result;
        Coordinate coordinateOfPrefix(getCoordinate(0, prefix, 0));
        NodePointer const& nodePointerOfPrefix(
            m_nodePointerMatrix.getEntryConstReference(coordinateOfPrefix.first, coordinateOfPrefix.second));
        if (nodePointerOfPrefix) {
            ValueUniquePointer const& valueUniquePointer(nodePointerOfPrefix->valueUniquePointer);
            if (valueUniquePointer) {
                result.emplace_back(prefix);
            }
            collectAllKeysAtNode(nodePointerOfPrefix->nextNodeId, prefix, result);
        }
        return result;
    }

    Keys getAllKeysThatMatch(Key const& patternToMatch) const override {
        Keys result;
        collectKeysThatMatchAtNode(0, std::string(), patternToMatch, result);
        return result;
    }

    SetOfNodeIds const& getUnusedNodeIds() const { return m_unusedNodeIds; }

    std::string getMatrixString() const {
        DisplayTable table;
        table.setBorders("-", "|");
        table.addRow();
        table.getLastRow().addCell(" ");
        for (int c = 0; c < RADIX; c++) {
            if (stringHelper::isDisplayableCharacter(c)) {
                table.getLastRow().addCell(stringHelper::convertToString(static_cast<char>(c)));
            } else {
                table.getLastRow().addCell(" ");
            }
        }
        for (int y = 0; y < m_nodePointerMatrix.getNumberOfRows(); y++) {
            table.addRow();
            table.getLastRow().addCell(stringHelper::convertToString(y));
            for (int x = 0; x < m_nodePointerMatrix.getNumberOfColumns(); x++) {
                NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(x, y).getObject());
                if (nodePointer) {
                    table.getLastRow().addCell(stringHelper::convertToString(nodePointer->nextNodeId));
                } else {
                    table.getLastRow().addCell(" ");
                }
            }
        }
        std::stringstream ss;
        ss << "Next node matrix:\n" << table;
        return ss.str();
    }

private:
    bool isValidNodeId(NodeId const nodeId) const {
        return nodeId < static_cast<NodeId>(m_nodePointerMatrix.getNumberOfRows());
    }

    bool isNodeEmpty(NodeId const nodeId) const {
        bool result(true);
        for (int c = 0; result && c < RADIX; c++) {
            NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(c, nodeId));
            result = result && !nodePointer;
        }
        return result;
    }

    NodeId getNextNodeId() {
        NodeId result{};
        if (!m_unusedNodeIds.empty()) {
            auto firstIt = m_unusedNodeIds.cbegin();
            result = *firstIt;
            m_unusedNodeIds.erase(firstIt);
        } else {
            result = ++m_nextNodeId;
        }
        assert(result < MAX_NUMBER_NODES);
        return result;
    }

    Coordinate getCoordinate(NodeId const nodeId, Key const& key, int const startingIndex) const {
        Coordinate result{INVALID_NODE_ID, 0};
        NodeId currentNodeId(nodeId);
        for (int keyIndex = startingIndex; keyIndex < static_cast<NodeId>(key.length()); keyIndex++) {
            char c(key[keyIndex]);
            bool isNextNodeFound(false);
            if (isValidNodeId(currentNodeId)) {
                NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(c, currentNodeId));
                if (nodePointer) {
                    isNextNodeFound = true;
                    if (keyIndex + 1 == static_cast<int>(key.length())) {
                        result = {c, currentNodeId};
                    }
                    currentNodeId = nodePointer->nextNodeId;
                }
            }
            if (!isNextNodeFound) {
                break;
            }
        }
        return result;
    }

    ValueUniquePointer getValuePointer(NodeId const nodeId, Key const& key, int const startingIndex) const {
        ValueUniquePointer result;
        NodeId currentNodeId(nodeId);
        for (int keyIndex = startingIndex; keyIndex < static_cast<NodeId>(key.length()); keyIndex++) {
            char c(key[keyIndex]);
            bool isNextNodeFound(false);
            if (isValidNodeId(currentNodeId)) {
                NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(c, currentNodeId));
                if (nodePointer) {
                    isNextNodeFound = true;
                    currentNodeId = nodePointer->nextNodeId;
                    ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
                    if (keyIndex + 1 == static_cast<NodeId>(key.length()) && valueUniquePointer) {
                        result = std::make_unique<Value>(*valueUniquePointer);
                    }
                }
            }
            if (!isNextNodeFound) {
                break;
            }
        }
        return result;
    }

    int getLengthOfLongestPrefix(NodeId const nodeId, Key const& keyToCheck, int const startingIndex) const {
        int currentLongestLength(0);
        NodeId currentNodeId(nodeId);
        for (int keyIndex = startingIndex; keyIndex < static_cast<NodeId>(keyToCheck.length()); keyIndex++) {
            char c(keyToCheck[keyIndex]);
            bool isNextNodeFound(false);
            if (isValidNodeId(currentNodeId)) {
                NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(c, currentNodeId));
                if (nodePointer) {
                    isNextNodeFound = true;
                    currentNodeId = nodePointer->nextNodeId;
                    ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
                    if (valueUniquePointer) {
                        currentLongestLength = keyIndex + 1;
                    }
                }
            }
            if (!isNextNodeFound) {
                break;
            }
        }
        return currentLongestLength;
    }

    void collectAllKeysAtNode(NodeId const nodeId, Key const& previousPrefix, Keys& collectedKeys) const {
        if (isValidNodeId(nodeId)) {
            for (int c = 0; c < RADIX; c++) {
                NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(c, nodeId));
                if (nodePointer) {
                    Key newPrefix = previousPrefix + static_cast<char>(c);
                    ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
                    if (valueUniquePointer) {
                        collectedKeys.emplace_back(newPrefix);
                    }
                    collectAllKeysAtNode(nodePointer->nextNodeId, newPrefix, collectedKeys);
                }
            }
        }
    }

    void collectKeysThatMatchAtNode(
        NodeId const nodeId, Key const& previousPrefix, Key const& patternToMatch, Keys& collectedKeys) const {
        if (isValidNodeId(nodeId)) {
            int prefixLength = previousPrefix.length();
            if (prefixLength < static_cast<NodeId>(patternToMatch.length())) {
                char charToMatch = patternToMatch[prefixLength];
                for (int c = 0; c < RADIX; c++) {
                    if ('.' == charToMatch || charToMatch == static_cast<char>(c)) {
                        NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(c, nodeId));
                        if (nodePointer) {
                            Key newPrefix = previousPrefix + static_cast<char>(c);
                            if (newPrefix.length() == patternToMatch.length()) {
                                ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
                                if (valueUniquePointer) {
                                    collectedKeys.emplace_back(newPrefix);
                                }
                            } else {
                                collectKeysThatMatchAtNode(
                                    nodePointer->nextNodeId, newPrefix, patternToMatch, collectedKeys);
                            }
                        }
                    }
                }
            }
        }
    }

    void put(NodeId const nodeId, Key const& key, Value const& value, int const startingIndex) {
        NodeId currentNodeId(nodeId);
        for (int keyIndex = startingIndex; keyIndex < static_cast<NodeId>(key.length()); keyIndex++) {
            char c(key[keyIndex]);
            NodePointer& nodePointer(m_nodePointerMatrix.getEntryReference(c, currentNodeId));
            if (!nodePointer) {
                nodePointer = std::make_unique<Node>();
                nodePointer->nextNodeId = INVALID_NODE_ID;
            }
            if (keyIndex + 1 == static_cast<NodeId>(key.length())) {
                ValueUniquePointer& valueUniquePointer(nodePointer->valueUniquePointer);
                if (valueUniquePointer) {
                    *valueUniquePointer = value;
                } else {
                    m_size++;
                    valueUniquePointer = std::make_unique<Value>(value);
                }
            } else if (nodePointer->nextNodeId == INVALID_NODE_ID) {
                nodePointer->nextNodeId = getNextNodeId();
            }
            currentNodeId = nodePointer->nextNodeId;
        }
    }

    bool deleteBasedOnKeyAndReturnIfDeleted(NodeId const nodeId, Key const& key, int const startingIndex) {
        // Deletion does not cleanup other entries on the matrix -> something to improve
        bool isDeleted(false);
        NodeId currentNodeId(nodeId);
        Coordinates traversedCoordinates;
        for (int keyIndex = startingIndex; keyIndex < static_cast<NodeId>(key.length()); keyIndex++) {
            char c(key[keyIndex]);
            bool isNextNodeFound(false);
            if (isValidNodeId(currentNodeId)) {
                NodePointer& nodePointer(m_nodePointerMatrix.getEntryReference(c, currentNodeId));
                traversedCoordinates.emplace_back(Coordinate{c, currentNodeId});
                if (nodePointer) {
                    isNextNodeFound = true;
                    currentNodeId = nodePointer->nextNodeId;
                    ValueUniquePointer& valueUniquePointer(nodePointer->valueUniquePointer);
                    if (keyIndex + 1 == static_cast<NodeId>(key.length()) && valueUniquePointer) {
                        m_size--;
                        isDeleted = true;
                        valueUniquePointer.reset();
                        if (nodePointer->nextNodeId == INVALID_NODE_ID) {
                            nodePointer.reset();
                        }
                    }
                }
            }
            if (!isNextNodeFound) {
                break;
            }
        }
        if (isDeleted && !traversedCoordinates.empty()) {
            Coordinate const& lastCoordinate(traversedCoordinates.back());
            NodeId previousNodeId(lastCoordinate.second);
            bool isPreviousNodeEmpty(isNodeEmpty(previousNodeId));
            addToUnusedNodesIfNeeded(previousNodeId, isPreviousNodeEmpty);
            for (auto it = traversedCoordinates.crbegin() + 1; it != traversedCoordinates.crend(); it++) {
                Coordinate const& coordinate(*it);
                if (isPreviousNodeEmpty) {
                    NodePointer& nodePointer(
                        m_nodePointerMatrix.getEntryReference(coordinate.first, coordinate.second));
                    if (nodePointer) {
                        nodePointer->nextNodeId = INVALID_NODE_ID;
                        if (!nodePointer->valueUniquePointer) {
                            nodePointer.reset();
                        }
                    }
                }
                previousNodeId = coordinate.second;
                isPreviousNodeEmpty = isNodeEmpty(previousNodeId);
                addToUnusedNodesIfNeeded(previousNodeId, isPreviousNodeEmpty);
            }
        }
        return isDeleted;
    }

    void addToUnusedNodesIfNeeded(NodeId const nodeId, bool isEmptyNode) {
        if (isEmptyNode) {
            m_unusedNodeIds.emplace(nodeId);
        }
    }
    int m_size;
    int m_nextNodeId;
    SetOfNodeIds m_unusedNodeIds;
    NodePointerMatrix m_nodePointerMatrix;
};

// A trie is a rooted tree that maintains a set of strings.
// Each string in the set is stored as a chain of characters that starts at the root.
// If two strings have a common prefix, they also have a common chain in the tree.

// We can check in O(n) time whether a trie contains a string of length n, because we can follow the chain that starts
// at the root node. We can also add a string of length n to the trie in O(n) time by first following the chain and then
// adding new nodes to the trie if necessary. Using a trie, we can find the longest prefix of a given string such that
// the prefix belongs to the set. Moreover, by storing additional information in each node, we can calculate the number
// of strings that belong to the set and have a given string as a prefix.

// A trie can be stored in an array "int trie[N][A];" where N is the maximum number of nodes
// (the maximum total length of the strings in the set) and A is the size of the alphabet.
// The nodes of a trie are numbered 0,1,2,... so that the number of the root is 0,
// and trie[s][c] is the next node in the chain when we move from node s using character c.
// Note in the implementation above coordinates are reversed.

}  // namespace algorithm

}  // namespace alba
