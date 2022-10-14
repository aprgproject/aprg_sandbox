#pragma once

namespace alba
{

namespace algorithm
{

template <typename BaseLinearProbingHash>
class BaseSetWithBaseLinearProbingHash : public BaseLinearProbingHash
{
public:
    using Key = typename BaseLinearProbingHash::Key;
    using Entry = typename BaseLinearProbingHash::Entry;
    using EntryUniquePointer = typename BaseLinearProbingHash::EntryUniquePointer;

    BaseSetWithBaseLinearProbingHash() = default;
    virtual ~BaseSetWithBaseLinearProbingHash() = default;

    void put(Key const& key) override // overrides in BaseSet
    {
        this->resizeOnPutIfNeeded();
        bool isFound(false);
        unsigned int i(this->getHash(key));
        for(; this->m_entryPointers[i]; this->incrementHashTableIndexWithWrapAround(i))
        {
            EntryUniquePointer & entryPointer(this->m_entryPointers[i]);
            if(key == entryPointer->key)
            {
                isFound = true;
                break;
            }
        }
        if(!isFound)
        {
            this->m_entryPointers[i].reset(new Entry{key});
        }
        this->m_size++;
    }

protected:

    void putEntry(Entry const& entry) override // overrides in BaseLinearProbingHash
    {
        put(entry.key);
    }
};

}

}
