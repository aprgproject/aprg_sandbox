#pragma once

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Key>
struct LinkedListNode
{
    Key key;
    std::unique_ptr<LinkedListNode> next;
};

template <typename Key, typename Value>
struct LinkedListNodeWithValue
{
    Key key;
    Value value;
    std::unique_ptr<LinkedListNodeWithValue> next;
};

}

}
