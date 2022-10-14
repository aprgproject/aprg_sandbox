#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseRedBlackBinarySearchTree.hpp>
#include <Algorithm/SymbolTable/BinarySearchTree/Common/BaseSymbolTableWithBaseTree.hpp>
#include <Algorithm/SymbolTable/BaseSymbolTable.hpp>

#include <memory>
namespace alba
{
namespace algorithm
{

template <typename Key, typename Value, typename Node>
class BaseRedBlackBinarySearchTreeSymbolTable
        : public BaseSymbolTableWithBaseTree<Value, BaseRedBlackBinarySearchTree<Key, Node, BaseSymbolTable<Key, Value>>>
{};

}

}