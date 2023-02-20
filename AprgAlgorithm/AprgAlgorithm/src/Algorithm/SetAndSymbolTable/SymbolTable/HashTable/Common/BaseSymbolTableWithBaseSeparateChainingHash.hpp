#pragma once

namespace alba
{

namespace algorithm
{

template <typename Value, typename BaseSeparateChainingHash>
class BaseSymbolTableWithBaseSeparateChainingHash : public BaseSeparateChainingHash
{
public:
    using Key = typename BaseSeparateChainingHash::Key;
    using Entry = typename BaseSeparateChainingHash::Entry;
    using HashTable = typename BaseSeparateChainingHash::HashTable;

    BaseSymbolTableWithBaseSeparateChainingHash()
        : b_size(BaseSeparateChainingHash::m_size)
        , b_smallerSymbolTables(BaseSeparateChainingHash::m_smallerSymbolTables)
    {}

    ~BaseSymbolTableWithBaseSeparateChainingHash() override = default; // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)

    Value get(Key const& key) const override
    {        return b_smallerSymbolTables.at(this->getHash(key)).get(key);
    }

    void put(Key const& key, Value const& value) override    {
        b_smallerSymbolTables[this->getHash(key)].put(key, value);
        b_size++;
    }

private:
    unsigned int & b_size;
    HashTable & b_smallerSymbolTables;
};

}

}
