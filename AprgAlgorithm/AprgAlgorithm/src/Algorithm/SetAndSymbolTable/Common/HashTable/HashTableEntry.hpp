#pragma once

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Key>
struct HashTableEntry
{
    Key key;
};

template <typename Key, typename Value>
struct HashTableEntryWithValue
{
    Key key;
    Value value;
};

}

}
