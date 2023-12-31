#pragma once

#include <Algorithm/SetAndSymbolTable/SymbolTable/Array/OrderedArraySymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>

#include <algorithm>
#include <memory>
#include <vector>

namespace alba {

namespace algorithm {

template <
    typename KeyTemplateType, typename EntryTemplateType, typename HashFunction, typename OrderedArray,
    typename BaseDataStructure>
class BaseLinearProbingHash : public BaseDataStructure {
public:
    using Key = KeyTemplateType;
    using Entry = EntryTemplateType;
    using Keys = std::vector<Key>;
    using EntryUniquePointer = std::unique_ptr<Entry>;
    using EntryPointers = EntryUniquePointer*;

    BaseLinearProbingHash() : m_size(0), m_hashTableSize(), m_entryPointers(nullptr) {
        initialize(INITIAL_HASH_TABLE_SIZE);
    }

    virtual ~BaseLinearProbingHash()  // virtual destructor because of virtual functions (vtable exists)
    {
        deleteAllEntries();
    }

    bool isEmpty() const override { return m_size == 0; }

    int getSize() const override { return m_size; }

    bool doesContain(Key const& key) const override {
        bool result(false);
        for (int i(getHash(key)); m_entryPointers[i]; incrementHashTableIndexWithWrapAround(i)) {
            EntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if (key == entryPointer->key) {
                result = true;
                break;
            }
        }
        return result;
    }

    int getRank(Key const& key) const override {
        Keys keys(getKeys());
        return OrderedArray::getRank(key, keys);
    }

    Key getMinimum() const override {
        Key result{};
        bool isFirst(true);
        for (int i = 0; i < m_hashTableSize; i++) {
            EntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if (entryPointer) {
                if (isFirst) {
                    result = entryPointer->key;
                    isFirst = false;
                } else {
                    result = std::min(result, entryPointer->key);
                }
            }
        }
        return result;
    }

    Key getMaximum() const override {
        Key result{};
        bool isFirst(true);
        for (int i = 0; i < m_hashTableSize; i++) {
            EntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if (entryPointer) {
                if (isFirst) {
                    result = entryPointer->key;
                    isFirst = false;
                } else {
                    result = std::max(result, entryPointer->key);
                }
            }
        }
        return result;
    }

    Key selectAt(int const index) const override {
        Keys keys(getKeys());
        return OrderedArray::selectAt(index, keys);
    }

    Key getFloor(Key const& key) const override {
        Keys keys(getKeys());
        return OrderedArray::getFloor(key, keys);
    }

    Key getCeiling(Key const& key) const override {
        Keys keys(getKeys());
        return OrderedArray::getCeiling(key, keys);
    }

    void deleteBasedOnKey(Key const& key) override {
        int i(getHash(key));
        for (; m_entryPointers[i] && m_entryPointers[i]->key != key; incrementHashTableIndexWithWrapAround(i))
            ;
        if (m_entryPointers[i] && m_entryPointers[i]->key == key) {
            deleteEntryOnIndex(i);
            incrementHashTableIndexWithWrapAround(i);
            while (m_entryPointers[i]) {
                Entry entryToReInput(*(m_entryPointers[i]));
                deleteEntryOnIndex(i);
                putEntry(entryToReInput);
                incrementHashTableIndexWithWrapAround(i);
            }
            resizeOnDeleteIfNeeded();
        }
    }

    void deleteMinimum() override { deleteBasedOnKey(getMinimum()); }

    void deleteMaximum() override { deleteBasedOnKey(getMaximum()); }

    Keys getKeys() const override {
        Keys result;
        for (int i = 0; i < m_hashTableSize; i++) {
            EntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if (entryPointer) {
                result.emplace_back(entryPointer->key);
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    Keys getKeysInRangeInclusive(Key const& low, Key const& high) const override {
        Keys result;
        for (int i = 0; i < m_hashTableSize; i++) {
            EntryUniquePointer const& entryPointer(m_entryPointers[i]);
            if (entryPointer) {
                Key const& currentKey(entryPointer->key);
                if (currentKey >= low && currentKey <= high) {
                    result.emplace_back(currentKey);
                }
            }
        }
        std::sort(result.begin(), result.end());
        return result;
    }

    int getHashTableSize() const { return m_hashTableSize; }

protected:
    virtual void putEntry(Entry const& entry) = 0;

    void deleteAllEntries() {
        if (m_entryPointers != nullptr) {
            delete[](m_entryPointers);
        }
    }

    void deleteEntryOnIndex(int const index) {
        m_entryPointers[index].reset();
        m_size--;
    }

    void initialize(int const initialSize) {
        if (m_entryPointers == nullptr) {
            m_entryPointers = new EntryUniquePointer[initialSize];
            m_hashTableSize = initialSize;
        }
    }

    void resize(int const newHashTableSize) {
        EntryPointers oldEntryPointers = m_entryPointers;
        int oldHashTableSize = m_hashTableSize;
        m_size = 0;
        m_entryPointers = new EntryUniquePointer[newHashTableSize]();
        m_hashTableSize = newHashTableSize;
        for (int i = 0; i < oldHashTableSize; i++) {
            EntryUniquePointer const& entryPointer(oldEntryPointers[i]);
            if (entryPointer) {
                putEntry(*entryPointer);
            }
        }
        if (oldEntryPointers != nullptr) {
            delete[](oldEntryPointers);
        }
    }

    void resizeOnPutIfNeeded() {
        if (m_size >= m_hashTableSize / 2) {
            resize(m_hashTableSize * 2);
        }
    }

    void resizeOnDeleteIfNeeded() {
        if (m_size > 0 && m_size == m_hashTableSize / 8) {
            resize(m_hashTableSize / 2);
        }
    }

    int getHash(Key const& key) const { return HashFunction::getHash(key); }

    void incrementHashTableIndexWithWrapAround(int& index) const { index = (index + 1) % m_hashTableSize; }

    static constexpr int INITIAL_HASH_TABLE_SIZE = 1;
    int m_size;
    int m_hashTableSize;
    EntryPointers m_entryPointers;
};

}  // namespace algorithm

}  // namespace alba

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

// Load Factor
// -> The load factor is denoted by the name "alpha".
// -> Its equal to n/m = number of items / number of slots.

// Formulated by Amdahl-Boehme-Rocherster-Samuel IBM 1953
// -> Open addressing: when a new key collides find the next empty slot and put it there.
// -> Open addressing means all elements occupy the hash table itself.
// ---> That is each table, entry contains either an element of the dynamic set or NIL.
// ---> When searching for an element, we systematically examine table slots until either we find the desired element,
// -----> or we have ascertained that the element is not in the table.
// ---> No lists and no elements are stored outside the table unlike in chaining.
// ---> Thus in open addressing, the hash table, can "fillup :so that no further insertions can be made;
// -----> one consequence is that the load factor alpha can never exceed 1.

// Important: Array size M must be greater than number key value pairs N.

// Cluster. A contiguous block of items
// Observation. New keys like to hash into middle of big clusters.

// Knuth's parking problem. -> Linear probing
// Mean displacement is the number of skips done to find an empty spot
// Half-full: With M/2 cars, mean displacement is 3/2.
// Full: With M cars, mean displacement is ~sqrt(pi*M/8)

// Proposition. Under the uniform hashing assumption, the average # of probes in a linear probing hash table of size M
// that contains N = alpha*M keys is
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
// -> Hash key to two positions; insert key into either position;
// if occupied, reinsert displaced key into its alternative position (and recur)
// -> Constant worst case time for search

// -> Hash Table Collision Resolution
// ---> Essentially any hash table can have collisions.
// ---> There are a number of ways of handling this.
// -> (1) Chaining with Linked Lists
// ---> With this approach (which is the most common), the hash table's array maps to a linked list of items.
// ---> We just add items to this linked list.
// ---> As long as the number of collisions is fairly small, this will be quite efficient.
// ---> In the worst case, lookup is O(n), where n is the number of elements in the hash table.
// ---> This would only happen with either some very strange data or a very poor hash function (or both).
// -> (2) Chaining with Binary Search Trees
// ---> Rather than storing collisions in a linked list, we could store collisions in a binary search tree.
// ---> This will bring the worst-case runtime to O(log n).
// ---> In practice, we would rarely take this approach unless we expected an extremely nonuniform distribution.
// -> (3) Open Addressing with Linear Probing
// ---> In this approach, when a collision occurs (there is already an item stored at the designated index),
// ---> we just move on to the next index in the array until we find an open spot.
// ---> (Or, sometimes, some other fixed distance, like the index + 5.)
// ---> If the number of collisions is low, this is a very fast and space-efficient solution.
// ---> One obvious drawback of this is that
// -----> the total number of entries in the hash table is limited by the size of the array.
// ---> This is not the case with chaining.
// ---> There's another issue here.
// ---> Consider a hash table with an underlying array of size 100
// -----> where indexes 20 through 29 are filled (and nothing else).
// ---> What are the odds of the next insertion going to index 30?
// ---> The odds are 10% because an item mapped to any index between 20 and 30 will wind up at index 30.
// ---> This causes an issue called clustering.
// -> (4) Quadratic Probing and Double Hashing
// ---> The distance between probes does not need to be linear.
// ---> You could, for example, increase the probe distance quadratically.
// ---> Or, you could use a second hash function to determine the probe distance.
