#pragma once

#include <Algorithm/String/Tries/BaseStringSymbolTable.hpp>

#include <array>
#include <memory>

namespace alba{

namespace algorithm
{

template <typename Value>
class TrieSymbolTable : public BaseStringSymbolTable<Value>
{
public:
    static constexpr unsigned int RADIX=256U;
    using Key = std::string;
    using Keys = stringHelper::strings;
    using ValueUniquePointer = std::unique_ptr<Value>;
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node
    {
        ValueUniquePointer valueUniquePointer;
        std::array<NodeUniquePointer, RADIX> next;
    };

    TrieSymbolTable()
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
        put(m_root, key, value, 0);
    }

    void deleteBasedOnKey(Key const& key) override
    {
       m_root = deleteBasedOnKey(m_root, key, 0);
    }

    Keys getKeys() const override
    {
        return getAllKeysWithPrefix("");
    }

    Keys getAllKeysWithPrefix(Key const& prefix) const override
    {
        Keys result;
        collectAllKeysAtNode(get(m_root, prefix, 0), prefix, result);
        return result;
    }

    Keys getAllKeysThatMatch(Key const& patternToMatch) const override
    {
        Keys result;
        collectKeysThatMatchAtNode(m_root.get(), "", patternToMatch, result);
        return result;
    }

private:

    unsigned int getSize(NodeUniquePointer const& currentNodePointer) const //override
    {
        unsigned int result(0);
        if(currentNodePointer)
        {
            ValueUniquePointer const& valueUniquePointer(currentNodePointer->valueUniquePointer);
            if(valueUniquePointer)
            {
                result++;
            }
            for(unsigned int c=0; c<RADIX; c++)
            {
                result += getSize(currentNodePointer->next.at(c));
            }
        }
        return result;
    }

    Node const* get(
            NodeUniquePointer const& currentNodePointer,
            Key const& key,
            unsigned int const index) const
    {
        Node const* result(nullptr);        if(currentNodePointer)
        {
            if(index == key.length())
            {                result = currentNodePointer.get();
            }
            else
            {
                result = get(currentNodePointer->next.at(key.at(index)), key, index+1);
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
            if(valueUniquePointer)
            {
                collectedKeys.emplace_back(previousPrefix);
            }
            for(unsigned int c=0; c<RADIX; c++)
            {
                collectAllKeysAtNode(
                            currentNodePointer->next.at(c).get(),
                            previousPrefix + static_cast<char>(c),
                            collectedKeys);
            }
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
            unsigned int prefixLength = previousPrefix.length();
            if(prefixLength == patternToMatch.length() && currentNodePointer->valueUniquePointer)
            {
                collectedKeys.emplace_back(previousPrefix);
            }
            if(prefixLength < patternToMatch.length())
            {
                char nextChar = patternToMatch.at(prefixLength);
                for(unsigned int c=0; c<RADIX; c++)
                {
                    if('.' == nextChar || nextChar == static_cast<char>(c))
                    {
                        collectKeysThatMatchAtNode(
                                    currentNodePointer->next.at(c).get(),
                                    previousPrefix + static_cast<char>(c),
                                    patternToMatch,
                                    collectedKeys);
                    }
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
                currentLongestLength = index;
            }
            if(index < keyToCheck.length())
            {
                char c = keyToCheck.at(index);
                currentLongestLength = getLengthOfLongestPrefix(currentNodePointer->next.at(c).get(), keyToCheck, index+1, currentLongestLength);
            }
        }
        return currentLongestLength;
    }

    void put(
            NodeUniquePointer & currentNodePointer,
            Key const& key,
            Value const& value,
            unsigned int const index)
    {        if(!currentNodePointer)
        {
            currentNodePointer = std::make_unique<Node>();
        }        if(index == key.length())
        {
            currentNodePointer->valueUniquePointer = std::make_unique<Value>(value);
        }
        else
        {
            put(currentNodePointer->next.at(key.at(index)), key, value, index+1);
        }
    }

    NodeUniquePointer deleteBasedOnKey(
            NodeUniquePointer & currentNodePointer,
            Key const& key,
            unsigned int const index)
    {
        NodeUniquePointer result;        if(currentNodePointer)
        {
            ValueUniquePointer & valueUniquePointer(currentNodePointer->valueUniquePointer);
            if(index == key.length())            {
                valueUniquePointer.reset();
            }
            else
            {
                char c = key.at(index);
                currentNodePointer->next[c] = deleteBasedOnKey(currentNodePointer->next.at(c), key, index+1);
            }
            if(valueUniquePointer)
            {
                result = std::move(currentNodePointer);
            }
            else
            {
                for(unsigned int c=0; c<RADIX; c++)
                {
                    if(currentNodePointer->next.at(c))
                    {
                        result = std::move(currentNodePointer);
                        break;
                    }
                }
            }
        }
        return result;
    }

    NodeUniquePointer m_root;
};

}
}