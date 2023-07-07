#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseAvlBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseSetWithBaseTree.hpp>

namespace alba {

namespace algorithm {

template <typename Key>
class BaseAvlBinarySearchTreeSet
    : public BaseSetWithBaseTree<BaseAvlBinarySearchTree<Key, AvlTreeNode<Key>, BaseSet<Key>>> {
public:
    ~BaseAvlBinarySearchTreeSet() override = default;
    // no need for virtual destructor because base destructor is virtual
    // (similar to other virtual functions)
};

}  // namespace algorithm

}  // namespace alba
