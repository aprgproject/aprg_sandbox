#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseRedBlackBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseSetWithBaseTree.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Node>
class BaseRedBlackBinarySearchTreeSet
        : public BaseSetWithBaseTree<BaseRedBlackBinarySearchTree<Key, Node, BaseSet<Key>>>
{};

}

}
