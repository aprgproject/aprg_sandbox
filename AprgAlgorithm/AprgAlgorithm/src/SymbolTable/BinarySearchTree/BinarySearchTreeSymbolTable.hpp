#pragma once

#include <SymbolTable/BinarySearchTree/BaseBinarySearchTreeSymbolTable.hpp>
#include <SymbolTable/BinarySearchTree/BinarySearchTreeNode.hpp>

#include <memory>
namespace alba
{

template <typename Key, typename Value>
class BinarySearchTreeSymbolTable
        : public BaseBinarySearchTreeSymbolTable<Key, Value, BinarySearchTreeNode::BasicTreeNode<Key, Value>>
{

};

}