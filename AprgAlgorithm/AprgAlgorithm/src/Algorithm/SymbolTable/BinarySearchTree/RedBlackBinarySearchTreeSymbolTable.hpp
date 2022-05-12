#pragma once

#include <Algorithm/SymbolTable/BinarySearchTree/Common/BaseRedBlackBinarySearchTreeSymbolTable.hpp>
#include <Algorithm/SymbolTable/BinarySearchTree/Common/BinarySearchTreeNode.hpp>

#include <memory>
namespace alba
{
namespace algorithm
{

template <typename Key, typename Value>
class RedBlackBinarySearchTreeSymbolTable
        : public BaseRedBlackBinarySearchTreeSymbolTable<Key, Value, BinarySearchTreeNode::RedBlackTreeNode<Key, Value>>
{
    // same as base

};

}
}