#pragma once

#include <SymbolTable/BaseSymbolTable.hpp>
#include <SymbolTable/OrderedArraySymbolTable.hpp>

#include <algorithm>
#include <memory>
#include <vector>

namespace alba
{

template <typename Key, typename Value>
class LinearProbingHashSymbolTable : public BaseSymbolTable<Key, Value>
{
public:
    using Keys = std::vector<Key>;
    struct HashTableEntry
    {
        Key key;
        Value value;
    };
    using HashTableEntryUniquePointer = std::unique_ptr<HashTableEntry>;
    using HashTableEntryPointers = HashTableEntryUniquePointer*;

    LinearProbingHashSymbolTable()
        : m_size(0)
        , m_hashTableSize()
        , m_entryPointers(nullptr)
    {
        initialize(INITIAL_HASH_TABLE_SIZE);
    }

    ~LinearProbingHashSymbolTable()
    {
        deleteAllEntries();
    }

    bool isEmpty() const override
    {
        return m_size == 0;
    }

    unsigned int getSize() const override
    {
        return m_size;
    }

    bool doesContain(Key const& key) const override
    {
        bool result(false);
        for(unsigned int i(getHash(key)); m_entryPointers[i]; incrementHashTableIndexWithWrapAround(i))
        {
            HashTableEntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if(key == entryPointer->key)
            {
                result = true;
                break;
            }
        }
        return result;
    }

    unsigned int getRank(Key const& key) const override
    {
        Keys keys(getKeys());
        return OrderedArraySymbolTable<Key, Value>::getRank(key, keys);
    }

    Value get(Key const& key) const override
    {
        Value result{};
        for(unsigned int i(getHash(key)); m_entryPointers[i]; incrementHashTableIndexWithWrapAround(i))
        {
            HashTableEntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if(key == entryPointer->key)
            {
                result = entryPointer->value;
                break;
            }
        }
        return result;
    }

    Key getMinimum() const override
    {
        Key result{};
        bool isFirst(true);
        for(unsigned int i=0; i<m_hashTableSize; i++)
        {
            HashTableEntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if(entryPointer)
            {
                if(isFirst)
                {
                    result = entryPointer->key;
                    isFirst = false;
                }
                else
                {
                    result = std::min(result, entryPointer->key);
                }
            }
        }
        return result;
    }

    Key getMaximum() const override
    {
        Key result{};
        bool isFirst(true);
        for(unsigned int i=0; i<m_hashTableSize; i++)
        {
            HashTableEntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if(entryPointer)
            {
                if(isFirst)
                {
                    result = entryPointer->key;
                    isFirst = false;
                }
                else
                {
                    result = std::max(result, entryPointer->key);
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
        resizeOnPutIfNeeded();
        bool isFound(false);
        unsigned int i(getHash(key));
        for(; m_entryPointers[i]; incrementHashTableIndexWithWrapAround(i))
        {
            HashTableEntryUniquePointer & entryPointer(m_entryPointers[i]);
            if(key == entryPointer->key)
            {
                entryPointer->value = value;
                isFound = true;
                break;
            }
        }
        if(!isFound)
        {
            m_entryPointers[i].reset(new HashTableEntry{key, value});
        }
        m_size++;
    }

    void deleteBasedOnKey(Key const& key) override
    {
        unsigned int i(getHash(key));
        for(; m_entryPointers[i] && m_entryPointers[i]->key != key; incrementHashTableIndexWithWrapAround(i));
        if(m_entryPointers[i] && m_entryPointers[i]->key == key)
        {
            deleteEntryOnIndex(i);
            incrementHashTableIndexWithWrapAround(i);
            while(m_entryPointers[i])
            {
                HashTableEntry entryToReInput(*(m_entryPointers[i]));
                deleteEntryOnIndex(i);
                put(entryToReInput.key, entryToReInput.value);
                incrementHashTableIndexWithWrapAround(i);
            }
            resizeOnDeleteIfNeeded();
        }
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
        for(unsigned int i=0; i<m_hashTableSize; i++)
        {
            HashTableEntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if(entryPointer)
            {
                result.emplace_back(entryPointer->key);
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    Keys getKeysInRangeInclusive(Key const& low, Key const& high) const override
    {
        Keys result;
        for(unsigned int i=0; i<m_hashTableSize; i++)
        {
            HashTableEntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if(entryPointer)
            {
                Key const& currentKey(entryPointer->key);
                if(currentKey >= low && currentKey <= high)
                {
                    result.emplace_back(currentKey);
                }
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    unsigned int getHashTableSize() const
    {
        return m_hashTableSize;
    }

protected:

    void deleteAllEntries()
    {
        if(m_entryPointers != nullptr)
        {
            delete[](m_entryPointers);
        }
    }

    void deleteEntryOnIndex(unsigned int const index)
    {
        m_entryPointers[index].reset();
        m_size--;
    }

    void initialize(unsigned int const initialSize)
    {
        if(m_entryPointers == nullptr)
        {
            m_entryPointers = new HashTableEntryUniquePointer[initialSize]{};
            m_hashTableSize = initialSize;
        }
    }

    void resize(unsigned int const newHashTableSize)
    {
        HashTableEntryPointers oldEntryPointers = m_entryPointers;
        unsigned int oldHashTableSize = m_hashTableSize;
        m_size = 0;
        m_entryPointers = new HashTableEntryUniquePointer[newHashTableSize]();
        m_hashTableSize = newHashTableSize;
        for(unsigned int i=0; i<oldHashTableSize; i++)
        {
            HashTableEntryUniquePointer const& entryPointer(oldEntryPointers[i]);
            if(entryPointer)
            {
                put(entryPointer->key, entryPointer->value);
            }
        }
        if(oldEntryPointers != nullptr)
        {
            delete[](oldEntryPointers);
        }
    }

    void resizeOnPutIfNeeded()
    {
        if(m_size >= m_hashTableSize/2)
        {
            resize(m_hashTableSize*2);
        }
    }

    void resizeOnDeleteIfNeeded()
    {
        if(m_size > 0 && m_size == m_hashTableSize/8)
        {
            resize(m_hashTableSize/2);
        }
    }

    unsigned int getHash(Key const& key) const
    {
        return static_cast<unsigned int>(key) % m_hashTableSize;
    }

    void incrementHashTableIndexWithWrapAround(unsigned int & index) const
    {
        index = (index+1) % m_hashTableSize;
    }

    static constexpr unsigned int INITIAL_HASH_TABLE_SIZE = 1U;
    unsigned int m_size;
    unsigned int m_hashTableSize;
    HashTableEntryPointers m_entryPointers;
};

}
