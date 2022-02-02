#pragma once

#include <SymbolTable/BaseSymbolTable.hpp>
#include <SymbolTable/UnorderedLinkedListSymbolTable.hpp>

#include <memory>

namespace alba
{

template <typename Key, typename Value, unsigned int HASH_TABLE_SIZE>
class SeparateChainingHashSymbolTable : public BaseSymbolTable<Key, Value>
{
public:

    SeparateChainingHashSymbolTable()
    {}

    bool isEmpty() const override
    {
    }

    unsigned int getSize() const override
    {
    }

    unsigned int getRank(Key const& key) const override
    {
    }

    Value get(Key const& key) const override
    {
    }

    Key getMinimum() const override
    {
    }

    Key getMaximum() const override
    {
    }

    Key selectAt(unsigned int const index) const override
    {
    }

    Key getFloor(Key const& key) const override
    {
    }

    Key getCeiling(Key const& key) const override
    {
    }

    void deleteBasedOnKey(Key const& key) override
    {
    }

    void deleteMinimum() override
    {
    }

    void deleteMaximum() override
    {
    }

protected:
    UnorderedLinkedListSymbolTable

};

}
