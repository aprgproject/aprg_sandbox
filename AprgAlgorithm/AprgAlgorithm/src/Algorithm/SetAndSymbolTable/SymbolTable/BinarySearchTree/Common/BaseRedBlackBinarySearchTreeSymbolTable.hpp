#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseRedBlackBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BaseSymbolTable.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BinarySearchTree/Common/BaseSymbolTableWithBaseTree.hpp>

#include <memory>

namespace alba {

namespace algorithm {

template <typename Key, typename Value, typename Node>
class BaseRedBlackBinarySearchTreeSymbolTable
    : public BaseSymbolTableWithBaseTree<Value, BaseRedBlackBinarySearchTree<Key, Node, BaseSymbolTable<Key, Value>>> {
public:
    ~BaseRedBlackBinarySearchTreeSymbolTable() override =
        default;  // no need for virtual destructor because base destructor is virtual (similar to other virtual
                  // functions)
};

}  // namespace algorithm

}  // namespace alba
