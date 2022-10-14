#pragma once

namespace alba
{

namespace algorithm
{

template <typename BaseSeparateChainingHash>
class BaseSetWithBaseSeparateChainingHash : public BaseSeparateChainingHash
{
public:
    using Key = typename BaseSeparateChainingHash::Key;
    using Entry = typename BaseSeparateChainingHash::Entry;

    BaseSetWithBaseSeparateChainingHash() = default;
    virtual ~BaseSetWithBaseSeparateChainingHash() = default;

    void put(Key const& key) override
    {
        this->m_smallerSymbolTables[this->getHash(key)].put(key);
        this->m_size++;
    }
};

}

}
