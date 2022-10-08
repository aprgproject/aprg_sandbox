#pragma once

#include <Algorithm/String/Tries/BaseStringSymbolTable.hpp>
#include <Common/Container/AlbaFakeCopyable.hpp>
#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba
{

namespace algorithm
{

template <typename Value, unsigned int MAX_NUMBER_NODES>
class RWayTrieUsingMatrix : public BaseStringSymbolTable<Value>
{
public:
    static constexpr unsigned int RADIX=256U;
    using Key = std::string;
    using Keys = stringHelper::strings;
    using NodeId = unsigned int;
    using ValueUniquePointer = std::unique_ptr<Value>;
    struct Node
    {
        NodeId nextNodeId;
        ValueUniquePointer valueUniquePointer;
    };
    using NodePointer = std::unique_ptr<Node>;
    using MatrixEntry = AlbaFakeCopyable<NodePointer>;
    using NodePointerMatrix = matrix::AlbaMatrix<MatrixEntry>;
    using Coordinate = std::pair<unsigned int, unsigned int>;

    RWayTrieUsingMatrix()
        : m_size(0U)
        , m_nextNodeId(0U)
        , m_nodePointerMatrix(MAX_NUMBER_NODES, RADIX)
    {}

    bool isEmpty() const override
    {
        return m_size == 0U;
    }

    bool doesContain(Key const& key) const override
    {
        return static_cast<bool>(getValuePointer(0U, key, 0U));
    }

    unsigned int getSize() const override
    {
        return m_size;
    }

    Value get(Key const& key) const override
    {
        Value result{};
        ValueUniquePointer valueUniquePointer(getValuePointer(0U, key, 0U));
        if(valueUniquePointer)
        {
            result = *valueUniquePointer;
        }
        return result;
    }

    Key getLongestPrefixOf(Key const& keyToCheck) const override
    {
        unsigned int longestPrefixLength(getLengthOfLongestPrefix(0U, keyToCheck, 0U));
        return keyToCheck.substr(0, longestPrefixLength);
    }

    void put(Key const& key, Value const& value) override
    {
        put(0U, key, value, 0U);
    }

    void deleteBasedOnKey(Key const& key) override
    {
        deleteBasedOnKeyAndReturnIfDeleted(0U, key, 0U);
    }

    Keys getKeys() const override
    {
        Keys result;
        collectAllKeysAtNode(0U, std::string(), result);
        return result;
    }

    Keys getAllKeysWithPrefix(Key const& prefix) const override
    {
        Keys result;
        Coordinate coordinateOfPrefix(getCoordinate(0U, prefix, 0U));
        NodePointer const& nodePointerOfPrefix(
                    m_nodePointerMatrix.getEntryConstReference(coordinateOfPrefix.first, coordinateOfPrefix.second).getObject());
        if(nodePointerOfPrefix)
        {
            ValueUniquePointer const& valueUniquePointer(nodePointerOfPrefix->valueUniquePointer);
            if(valueUniquePointer)
            {
                result.emplace_back(prefix);
            }
            collectAllKeysAtNode(nodePointerOfPrefix->nextNodeId, prefix, result);
        }
        return result;
    }

    Keys getAllKeysThatMatch(Key const& patternToMatch) const override
    {
        Keys result;
        collectKeysThatMatchAtNode(0U, std::string(), patternToMatch, result);
        return result;
    }

private:

    bool isValidNodeId(NodeId const nodeId) const
    {
        return nodeId < m_nodePointerMatrix.getNumberOfColumns();
    }

    NodeId getNextNodeId()
    {
        return ++m_nextNodeId;
    }

    Coordinate getCoordinate(
            NodeId const nodeId,
            Key const& key,
            unsigned int const startingIndex) const
    {
        Coordinate result{};
        NodeId currentNodeId(nodeId);
        for(unsigned int keyIndex=startingIndex; keyIndex<key.length(); keyIndex++)
        {
            char c(key.at(keyIndex));
            bool isNextNodeFound(false);
            if(isValidNodeId(currentNodeId))
            {
                NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(currentNodeId, c).getObject());
                if(nodePointer)
                {
                    isNextNodeFound = true;
                    if(keyIndex+1 == key.length())
                    {
                        result = {currentNodeId, c};
                    }
                    currentNodeId = nodePointer->nextNodeId;
                }
            }
            if(!isNextNodeFound)
            {
                break;
            }
        }
        return result;
    }

    ValueUniquePointer getValuePointer(
            NodeId const nodeId,
            Key const& key,
            unsigned int const startingIndex) const
    {
        ValueUniquePointer result;
        NodeId currentNodeId(nodeId);
        for(unsigned int keyIndex=startingIndex; keyIndex<key.length(); keyIndex++)
        {
            char c(key.at(keyIndex));
            bool isNextNodeFound(false);
            if(isValidNodeId(currentNodeId))
            {
                NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(currentNodeId, c).getObject());
                if(nodePointer)
                {
                    isNextNodeFound = true;
                    currentNodeId = nodePointer->nextNodeId;
                    ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
                    if(keyIndex+1 == key.length() && valueUniquePointer)
                    {
                        result = std::make_unique<Value>(*valueUniquePointer);
                    }
                }
            }
            if(!isNextNodeFound)
            {
                break;
            }
        }
        return result;
    }

    unsigned int getLengthOfLongestPrefix(
            NodeId const nodeId,
            Key const& keyToCheck,
            unsigned int const startingIndex) const
    {
        unsigned int currentLongestLength(0U);
        NodeId currentNodeId(nodeId);
        for(unsigned int keyIndex=startingIndex; keyIndex<keyToCheck.length(); keyIndex++)
        {
            char c(keyToCheck.at(keyIndex));
            bool isNextNodeFound(false);
            if(isValidNodeId(currentNodeId))
            {
                NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(currentNodeId, c).getObject());
                if(nodePointer)
                {
                    isNextNodeFound = true;
                    currentNodeId = nodePointer->nextNodeId;
                    ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
                    if(valueUniquePointer)
                    {
                        currentLongestLength = keyIndex+1;
                    }
                }
            }
            if(!isNextNodeFound)
            {
                break;
            }
        }
        return currentLongestLength;
    }

    void collectAllKeysAtNode(
            NodeId const nodeId,
            Key const& previousPrefix,
            Keys & collectedKeys) const
    {
        if(isValidNodeId(nodeId))
        {
            for(unsigned int c=0; c<RADIX; c++)
            {
                NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(nodeId, c).getObject());
                if(nodePointer)
                {
                    Key newPrefix = previousPrefix + static_cast<char>(c);
                    ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
                    if(valueUniquePointer)
                    {
                        collectedKeys.emplace_back(newPrefix);
                    }
                    collectAllKeysAtNode(nodePointer->nextNodeId, newPrefix, collectedKeys);
                }
            }
        }
    }

    void collectKeysThatMatchAtNode(
            NodeId const nodeId,
            Key const& previousPrefix,
            Key const& patternToMatch,
            Keys & collectedKeys) const
    {
        if(isValidNodeId(nodeId))
        {
            unsigned int prefixLength = previousPrefix.length();
            if(prefixLength < patternToMatch.length())
            {
                char charToMatch = patternToMatch.at(prefixLength);
                for(unsigned int c=0; c<RADIX; c++)
                {
                    if('.' == charToMatch || charToMatch == static_cast<char>(c))
                    {
                        NodePointer const& nodePointer(m_nodePointerMatrix.getEntryConstReference(nodeId, c).getObject());
                        if(nodePointer)
                        {
                            Key newPrefix = previousPrefix + static_cast<char>(c);
                            if(newPrefix.length() == patternToMatch.length())
                            {
                                ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
                                if(valueUniquePointer)
                                {
                                    collectedKeys.emplace_back(newPrefix);
                                }
                            }
                            else
                            {
                                collectKeysThatMatchAtNode(nodePointer->nextNodeId, newPrefix, patternToMatch, collectedKeys);
                            }
                        }
                    }
                }
            }
        }
    }

    void put(
            NodeId const nodeId,
            Key const& key,
            Value const& value,
            unsigned int const startingIndex)
    {
        NodeId currentNodeId(nodeId);
        for(unsigned int keyIndex=startingIndex; keyIndex<key.length(); keyIndex++)
        {
            char c(key.at(keyIndex));
            NodePointer & nodePointer(m_nodePointerMatrix.getEntryReference(currentNodeId, c).getObjectReference());
            if(!nodePointer)
            {
                nodePointer = std::make_unique<Node>();
                nodePointer->nextNodeId = getNextNodeId();
            }
            currentNodeId = nodePointer->nextNodeId;
            if(keyIndex+1 == key.length())
            {
                ValueUniquePointer & valueUniquePointer(nodePointer->valueUniquePointer);
                if(valueUniquePointer)
                {
                    *valueUniquePointer = value;
                }
                else
                {
                    m_size++;
                    valueUniquePointer = std::make_unique<Value>(value);
                }
            }
        }
    }

    bool deleteBasedOnKeyAndReturnIfDeleted(
            NodeId const nodeId,
            Key const& key,
            unsigned int const startingIndex)
    {
        // Deletion does not cleanup other entries on the matrix -> something to improve
        bool isDeleted(false);
        NodeId currentNodeId(nodeId);
        for(unsigned int keyIndex=startingIndex; keyIndex<key.length(); keyIndex++)
        {
            char c(key.at(keyIndex));
            bool isNextNodeFound(false);
            if(isValidNodeId(currentNodeId))
            {
                NodePointer & nodePointer(m_nodePointerMatrix.getEntryReference(currentNodeId, c).getObjectReference());
                if(nodePointer)
                {
                    isNextNodeFound = true;
                    currentNodeId = nodePointer->nextNodeId;
                    ValueUniquePointer & valueUniquePointer(nodePointer->valueUniquePointer);
                    if(keyIndex+1 == key.length() && valueUniquePointer)
                    {
                        m_size--;
                        isDeleted = true;
                        valueUniquePointer.reset();
                    }
                }
            }
            if(!isNextNodeFound)
            {
                break;
            }
        }
        return isDeleted;
    }

    unsigned int m_size;
    unsigned int m_nextNodeId;
    NodePointerMatrix m_nodePointerMatrix;
};

// A trie is a rooted tree that maintains a set of strings.
// Each string in the set is stored as a chain of characters that starts at the root.
// If two strings have a common prefix, they also have a common chain in the tree.

// We can check in O(n) time whether a trie contains a string of length n, because we can follow the chain that starts at the root node.
// We can also add a string of length n to the trie in O(n) time by first following the chain and then adding new nodes to the trie if necessary.
// Using a trie, we can find the longest prefix of a given string such that the prefix belongs to the set.
// Moreover, by storing additional information in each node, we can calculate the number of strings that belong to the set and have a given string as a prefix.

// A trie can be stored in an array "int trie[N][A];" where N is the maximum number of nodes
// (the maximum total length of the strings in the set) and A is the size of the alphabet.
// The nodes of a trie are numbered 0,1,2,... so that the number of the root is 0,
// and trie[s][c] is the next node in the chain when we move from node s using character c.

}

}
