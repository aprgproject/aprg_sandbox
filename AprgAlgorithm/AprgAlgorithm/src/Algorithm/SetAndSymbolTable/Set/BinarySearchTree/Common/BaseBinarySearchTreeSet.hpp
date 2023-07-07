#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseSetWithBaseTree.hpp>

namespace alba {

namespace algorithm {

template <typename Key>
class BaseBinarySearchTreeSet
    : public BaseSetWithBaseTree<BaseBinarySearchTree<Key, BasicTreeNode<Key>, BaseSet<Key>>> {
public:
    ~BaseBinarySearchTreeSet() override = default;
    // no need for virtual destructor because base destructor is virtual
    // (similar to other virtual functions)
};

}  // namespace algorithm
}  // namespace alba