#pragma once

#include <Sorter/MergeSorter/MergeSorterUtilities.hpp>
#include <SymbolTable/BaseSymbolTable.hpp>
#include <SymbolTable/OrderedArraySymbolTable.hpp>
#include <SymbolTable/UnorderedLinkedListSymbolTable.hpp>

#include <memory>

namespace alba
{

template <typename Key, typename Value, unsigned int HASH_TABLE_SIZE>
class SeparateChainingHashSymbolTable : public BaseSymbolTable<Key, Value>
{
public:
    using Keys = std::vector<Key>;

    SeparateChainingHashSymbolTable()
        : m_size(0)
    {}

    bool isEmpty() const override
    {
        return m_size == 0;
    }

    bool doesContain(Key const& key) const override
    {
        return m_smallerSymbolTables.at(getHash(key)).doesContain(key);
    }

    unsigned int getSize() const override
    {
        return m_size;
    }

    unsigned int getRank(Key const& key) const override
    {
        Keys keys(getKeys());
        return OrderedArraySymbolTable<Key, Value>::getRank(key, keys);
    }

    Value get(Key const& key) const override
    {
        return m_smallerSymbolTables.at(getHash(key)).get(key);
    }

    Key getMinimum() const override
    {
        Key result;
        bool isFirst(true);
        for(auto const& smallerSymbolTables : m_smallerSymbolTables)
        {
            if(!smallerSymbolTables.isEmpty())
            {
                if(isFirst)
                {
                    result = smallerSymbolTables.getMinimum();
                    isFirst=false;
                }
                else
                {
                    result = std::min(result, smallerSymbolTables.getMinimum());
                }
            }
        }
        return result;
    }

    Key getMaximum() const override
    {
        Key result;
        bool isFirst(true);
        for(auto const& smallerSymbolTables : m_smallerSymbolTables)
        {
            if(!smallerSymbolTables.isEmpty())
            {
                if(isFirst)
                {
                    result = smallerSymbolTables.getMaximum();
                    isFirst=false;
                }
                else
                {
                    result = std::max(result, smallerSymbolTables.getMaximum());
                }
            }
        }
        return result;
    }

    Key selectAt(unsigned int const index) const override
    {
        Keys keys(getKeys());
        return OrderedArraySymbolTable<Key, Value>::selectAt(index, keys);
    }

    Key getFloor(Key const& key) const override
    {
        Keys keys(getKeys());
        return OrderedArraySymbolTable<Key, Value>::getFloor(key, keys);
    }

    Key getCeiling(Key const& key) const override
    {
        Keys keys(getKeys());
        return OrderedArraySymbolTable<Key, Value>::getCeiling(key, keys);
    }

    void put(Key const& key, Value const& value) override
    {
        m_smallerSymbolTables[getHash(key)].put(key, value);
        m_size++;
    }

    void deleteBasedOnKey(Key const& key) override
    {
        m_smallerSymbolTables[getHash(key)].deleteBasedOnKey(key);
        m_size--;
    }

    void deleteMinimum() override
    {
        deleteBasedOnKey(getMinimum());
    }

    void deleteMaximum() override
    {
        deleteBasedOnKey(getMaximum());
    }

    Keys getKeys() const override
    {
        Keys result;
        for(auto const& smallerSymbolTables : m_smallerSymbolTables)
        {
            if(!smallerSymbolTables.isEmpty())
            {
                result = mergeTwoSortedSequences(result, smallerSymbolTables.getKeys());
            }
        }
        return result;
    }

    Keys getKeysInRangeInclusive(Key const& low, Key const& high) const override
    {
        Keys result;
        for(auto const& smallerSymbolTables : m_smallerSymbolTables)
        {
            if(!smallerSymbolTables.isEmpty())
            {
                result = mergeTwoSortedSequences(result, smallerSymbolTables.getKeysInRangeInclusive(low, high));
            }
        }
        return result;
    }

protected:
    unsigned int getHash(Key const& key) const
    {
        return static_cast<unsigned int>(key) % HASH_TABLE_SIZE;
    }

    unsigned int m_size;
    std::array<UnorderedLinkedListSymbolTable<Key, Value>, HASH_TABLE_SIZE> m_smallerSymbolTables;
};

}
