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
    using HashTable = typename BaseSeparateChainingHash::HashTable;

    BaseSetWithBaseSeparateChainingHash()
        : b_size(BaseSeparateChainingHash::m_size)
        , b_smallerSymbolTables(BaseSeparateChainingHash::m_smallerSymbolTables)
    {}

    virtual ~BaseSetWithBaseSeparateChainingHash() = default;

    void put(Key const& key) override
    {
        b_smallerSymbolTables[this->getHash(key)].put(key);
        b_size++;
    }

private:
    unsigned int & b_size;
    HashTable & b_smallerSymbolTables;
};

}
}