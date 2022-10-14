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

    BaseSymbolTableWithBaseSeparateChainingHash() = default;
    virtual ~BaseSymbolTableWithBaseSeparateChainingHash() = default;

    Value get(Key const& key) const override
    {
        return this->m_smallerSymbolTables.at(this->getHash(key)).get(key);
    }

    void put(Key const& key, Value const& value) override
    {
        this->m_smallerSymbolTables[this->getHash(key)].put(key, value);
        this->m_size++;
    }
};

}

}
