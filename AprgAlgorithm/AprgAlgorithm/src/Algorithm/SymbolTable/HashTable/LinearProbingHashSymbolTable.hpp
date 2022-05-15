#pragma once

#include <Algorithm/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SymbolTable/OrderedArraySymbolTable.hpp>

#include <algorithm>
#include <memory>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value, typename HashFunction>
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
        return HashFunction::getHash(key, m_hashTableSize);
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

// General hashing notes:
// Basic plan: Save items in a key-indexed table (index is a function of the key)

// Issues:
// Computing the hash function
// Equality test: Method for checking whether two keys are equal
// Collision resolution: Algorithm and data structure to handle two keys that hash to the same array index

// Hashing is a classic space-time tradeoff
// -> No space limitation: trivial hash function with key as index
// -> No time limitation: trivial collision resolution with sequential search
// -> Space and time limitations: tune hashing in the real world

// Formulated by Amdahl-Boehme-Rocherster-Samuel IBM 1953
// Open addressing: when a new key collides find the next empty slot and put it there.

// Important: Array size M must be greater than number key value pairs N.

// Cluster. A contiguous block of items
// Observation. New keys like to hash into middle of big clusters.

// Knuth's parking problem. -> Linear probing
// Mean displacement is the number of skips done to find an empty spot
// Half-full: With M/2 cars, mean displacement is 3/2.
// Full: With M cars, mean displacement is ~sqrt(pi*M/8)

// Proposition. Under the uniform hashing assumption, the average # of probes in a linear probing hash table of size M that contains N = alpha*M keys is
// For search hit: ~(1/2)(1+(1/(1-alpha)))
// For search miss/insert: ~(1/2)(1+(1/(1-alpha)^2))

// In summary:
// -> M too large -> too many empty array entries
// -> M too small -> search time blows up
// -> Typical choice: alpha = N/M ~ 1/2 (#probes for search hit is about 3/2 and # probes for search miss is about 5/2)

// Performance depends on input: If hash function is known, its vulnerable to attacks (DDOS).


// Separate chaining vs Linear probing
// Separate chaining
// -> Easier to implement delete
// -> Performance degrades grace fully
// -> Clustering less sensistive to poorly designed hash function

// Linear probing
// -> Less wasted space
// -> Better cache performance

// Improved version: Double hashing (linear probing variant)
// -> Use linear probing but skip a variable amount, not just 1 each time.
// -> Effectively eliminates clustering
// -> Can allow table to become nearly full
// -> More difficult to implement delete.

// Improved version: Cuckoo hashing (linear probing variant)
// -> Hash key to two positions; insert key into either position; if occupied, reinsert displaced key into its alternative position (and recur)
// -> Constant worst case time for search

}

}
