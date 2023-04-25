#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseRedBlackBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BaseSet.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseSetWithBaseTree.hpp>

#include <memory>

namespace alba {

namespace algorithm {

template <typename Key, typename Node>
class BaseRedBlackBinarySearchTreeSet
    : public BaseSetWithBaseTree<BaseRedBlackBinarySearchTree<Key, Node, BaseSet<Key>>> {
public:
    ~BaseRedBlackBinarySearchTreeSet() override = default;  // no need for virtual destructor because base destructor is
                                                            // virtual (similar to other virtual functions)
};

}  // namespace algorithm

}  // namespace alba
