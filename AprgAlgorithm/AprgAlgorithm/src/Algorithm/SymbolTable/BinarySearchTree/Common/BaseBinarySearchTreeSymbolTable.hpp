#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNode.hpp>
#include <Algorithm/SymbolTable/BinarySearchTree/Common/BaseSymbolTableWithBaseTree.hpp>
#include <Algorithm/SymbolTable/BaseSymbolTable.hpp>

namespace alba
{
namespace algorithm
{

template <typename Key, typename Value>
class BaseBinarySearchTreeSymbolTable
        : public BaseSymbolTableWithBaseTree<Value, BaseBinarySearchTree<Key, BasicTreeNodeWithValue<Key, Value>, BaseSymbolTable<Key, Value>>>
{};

}

}