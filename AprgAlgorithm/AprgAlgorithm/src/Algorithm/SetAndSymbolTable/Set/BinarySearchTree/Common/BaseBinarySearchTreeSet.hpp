#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNode.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseSetWithBaseTree.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>

namespace alba
{

namespace algorithm
{

template <typename Key>
class BaseBinarySearchTreeSet
        : public BaseSetWithBaseTree<BaseBinarySearchTree<Key, BasicTreeNode<Key>, BaseSet<Key>>>
{
public:
    virtual ~BaseBinarySearchTreeSet() = default;
};

}
}