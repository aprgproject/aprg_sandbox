#pragma once

#include <Algorithm/String/Tries/BaseStringSymbolTable.hpp>

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Value>
class TernarySearchTrie : public BaseStringSymbolTable<Value>
{
public:
    using Key = std::string;
    using Keys = stringHelper::strings;
    using ValueUniquePointer = std::unique_ptr<Value>;
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node
    {
        char c;
        ValueUniquePointer valueUniquePointer;
        NodeUniquePointer left;
        NodeUniquePointer mid;
        NodeUniquePointer right;
    };

    TernarySearchTrie()
        : m_root(nullptr)
    {}

    bool isEmpty() const override
    {
        return getSize() == 0;
    }

    bool doesContain(Key const& key) const override
    {
        Node const*const nodePointer(get(m_root, key, 0));
        return nodePointer != nullptr;
    }

    unsigned int getSize() const override
    {
        return getSize(m_root);
    }

    Value get(Key const& key) const override
    {
        Value result{};
        Node const*const nodePointer(get(m_root, key, 0));
        if(nodePointer != nullptr)
        {
            ValueUniquePointer const& valueUniquePointer(nodePointer->valueUniquePointer);
            if(valueUniquePointer)
            {
                result = *valueUniquePointer;
            }
        }
        return result;
    }

    Key getLongestPrefixOf(Key const& keyToCheck) const override
    {
        unsigned int longestPrefixLength(getLengthOfLongestPrefix(m_root.get(), keyToCheck, 0U, 0U));
        return keyToCheck.substr(0, longestPrefixLength);
    }

    void put(Key const& key, Value const& value) override
    {
        if(!key.empty())
        {
            put(m_root, key, value, 0);
        }
    }

    void deleteBasedOnKey(Key const& key) override
    {
        m_root = deleteBasedOnKey(m_root, key, 0);
    }

    Keys getKeys() const override
    {
        Keys result;
        collectAllKeysAtNode(m_root.get(), std::string(), result);
        return result;
    }

    Keys getAllKeysWithPrefix(Key const& prefix) const override
    {
        Keys result;
        Node const*const firstNode(get(m_root, prefix, 0U));
        if(firstNode != nullptr)
        {
            collectAllKeysAtNode(firstNode->mid.get(), prefix, result);
        }
        return result;
    }

    Keys getAllKeysThatMatch(Key const& patternToMatch) const override
    {
        Keys result;
        collectKeysThatMatchAtNode(m_root.get(), "", patternToMatch, result);
        return result;
    }

private:

    unsigned int getSize(NodeUniquePointer const& currentNodePointer) const
    {
        unsigned int result(0);
        if(currentNodePointer)
        {
            ValueUniquePointer const& valueUniquePointer(currentNodePointer->valueUniquePointer);
            if(valueUniquePointer)
            {
                result++;
            }
            result += getSize(currentNodePointer->left);
            result += getSize(currentNodePointer->right);
            result += getSize(currentNodePointer->mid);
        }
        return result;
    }

    Node const* get(
            NodeUniquePointer const& currentNodePointer,
            Key const& key,
            unsigned int const index) const
    {
        Node const* result(nullptr);
        if(currentNodePointer && index<key.length())
        {
            char c(key.at(index));
            if(c < currentNodePointer->c)
            {
                result = get(currentNodePointer->left, key, index);
            }
            else if(c > currentNodePointer->c)
            {
                result = get(currentNodePointer->right, key, index);
            }
            else if(index < key.length() - 1)
            {
                result = get(currentNodePointer->mid, key, index+1);
            }
            else
            {
                result = currentNodePointer.get();
            }
        }
        return result;
    }

    void collectAllKeysAtNode(
            Node const*const currentNodePointer,
            Key const& previousPrefix,
            Keys & collectedKeys) const
    {
        if(currentNodePointer != nullptr)
        {
            ValueUniquePointer const& valueUniquePointer(currentNodePointer->valueUniquePointer);
            Key currentPrefix(previousPrefix + currentNodePointer->c);
            if(valueUniquePointer)
            {
                collectedKeys.emplace_back(currentPrefix);
            }
            collectAllKeysAtNode(currentNodePointer->left.get(), previousPrefix, collectedKeys);
            collectAllKeysAtNode(currentNodePointer->mid.get(), currentPrefix, collectedKeys);
            collectAllKeysAtNode(currentNodePointer->right.get(), previousPrefix, collectedKeys);
        }
    }

    void collectKeysThatMatchAtNode(
            Node const*const currentNodePointer,
            Key const& previousPrefix,
            Key const& patternToMatch,
            Keys & collectedKeys) const
    {
        if(currentNodePointer != nullptr)
        {
            unsigned int previousPrefixLength = previousPrefix.length();
            unsigned int lastIndexToMatch = patternToMatch.length() - 1;
            char currentChar = currentNodePointer->c;
            char nextChar = patternToMatch.at(previousPrefixLength);
            Key currentPrefix(previousPrefix + currentNodePointer->c);
            if(nextChar < currentChar)
            {
                collectKeysThatMatchAtNode(currentNodePointer->left.get(), previousPrefix, patternToMatch, collectedKeys);
            }
            else if(nextChar == currentChar)
            {
                if(previousPrefixLength < lastIndexToMatch)
                {
                    collectKeysThatMatchAtNode(currentNodePointer->mid.get(), currentPrefix, patternToMatch, collectedKeys);
                }
                else if(previousPrefixLength == lastIndexToMatch && currentNodePointer->valueUniquePointer)
                {
                    collectedKeys.emplace_back(currentPrefix);
                }
            }
            else if(nextChar > currentChar)
            {
                collectKeysThatMatchAtNode(currentNodePointer->right.get(), previousPrefix, patternToMatch, collectedKeys);
            }
            if(nextChar == '.')
            {
                if(previousPrefixLength < lastIndexToMatch)
                {
                    collectKeysThatMatchAtNode(currentNodePointer->mid.get(), currentPrefix, patternToMatch, collectedKeys);
                }
                else if(previousPrefixLength == lastIndexToMatch && currentNodePointer->valueUniquePointer)
                {
                    collectedKeys.emplace_back(currentPrefix);
                }
            }
        }
    }

    unsigned int getLengthOfLongestPrefix(
            Node const*const currentNodePointer,
            Key const& keyToCheck,
            unsigned int const index,
            unsigned int const length) const
    {
        unsigned int currentLongestLength(length);
        if(currentNodePointer != nullptr)
        {
            if(currentNodePointer->valueUniquePointer)
            {
                currentLongestLength = index+1;
            }
            if(index < keyToCheck.length())
            {
                char charToCheck = keyToCheck.at(index);
                if(charToCheck < currentNodePointer->c)
                {
                    currentLongestLength = getLengthOfLongestPrefix(currentNodePointer->left.get(), keyToCheck, index, currentLongestLength);
                }
                else if(charToCheck > currentNodePointer->c)
                {
                    currentLongestLength = getLengthOfLongestPrefix(currentNodePointer->right.get(), keyToCheck, index, currentLongestLength);
                }
                else if(index < keyToCheck.length() - 1)
                {
                    currentLongestLength = getLengthOfLongestPrefix(currentNodePointer->mid.get(), keyToCheck, index+1, currentLongestLength);
                }
            }
        }
        return currentLongestLength;
    }

    void put(
            NodeUniquePointer & currentNodePointer,
            Key const& key,
            Value const& value,
            unsigned int const index)
    {
        char charAtKey(key.at(index));
        if(!currentNodePointer)
        {
            currentNodePointer = std::make_unique<Node>(Node{charAtKey, nullptr, nullptr, nullptr, nullptr});
        }
        if(charAtKey < currentNodePointer->c)
        {
            put(currentNodePointer->left, key, value, index);
        }
        else if(charAtKey > currentNodePointer->c)
        {
            put(currentNodePointer->right, key, value, index);
        }
        else if(index < key.length() - 1)
        {
            put(currentNodePointer->mid, key, value, index+1);
        }
        else
        {
            currentNodePointer->valueUniquePointer = std::make_unique<Value>(value);
        }
    }

    NodeUniquePointer deleteBasedOnKey(
            NodeUniquePointer & currentNodePointer,
            Key const& key,
            unsigned int const index)
    {
        NodeUniquePointer result;
        if(currentNodePointer)
        {
            unsigned int lastIndex = key.length() - 1;
            ValueUniquePointer & valueUniquePointer(currentNodePointer->valueUniquePointer);
            if(index < lastIndex)
            {
                char charAtKey(key.at(index));
                if(charAtKey < currentNodePointer->c)
                {
                    currentNodePointer->left = deleteBasedOnKey(currentNodePointer->left, key, index);
                }
                else if(charAtKey > currentNodePointer->c)
                {
                    currentNodePointer->right = deleteBasedOnKey(currentNodePointer->right, key, index);
                }
                else
                {
                    currentNodePointer->mid = deleteBasedOnKey(currentNodePointer->mid, key, index+1);
                }
            }
            else if(index == lastIndex)
            {
                valueUniquePointer.reset();
            }
            if(!currentNodePointer->valueUniquePointer && !currentNodePointer->mid)
            {
                if(!currentNodePointer->left && !currentNodePointer->right)
                {
                    currentNodePointer.reset();
                }
                else if(currentNodePointer->left && !currentNodePointer->right)
                {
                    currentNodePointer = std::move(currentNodePointer->left);
                }
                else if(!currentNodePointer->left && currentNodePointer->right)
                {
                    currentNodePointer = std::move(currentNodePointer->right);
                }
                else
                {
                    currentNodePointer->mid = std::move(currentNodePointer->right);
                }
            }
            result = std::move(currentNodePointer);
        }
        return result;
    }

    NodeUniquePointer m_root;
};

}

}
