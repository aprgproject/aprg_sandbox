#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseAvlBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BinarySearchTree/Common/BaseSymbolTableWithBaseTree.hpp>

namespace alba {

namespace algorithm {

template <typename Key, typename Value>
class BaseAvlBinarySearchTreeSymbolTable
    : public BaseSymbolTableWithBaseTree<
          Value, BaseAvlBinarySearchTree<Key, AvlTreeNodeWithValue<Key, Value>, BaseSymbolTable<Key, Value>>> {
public:
    ~BaseAvlBinarySearchTreeSymbolTable() override = default;  // no need for virtual destructor because base destructor
                                                               // is virtual (similar to other virtual functions)
};

}  // namespace algorithm

}  // namespace alba
