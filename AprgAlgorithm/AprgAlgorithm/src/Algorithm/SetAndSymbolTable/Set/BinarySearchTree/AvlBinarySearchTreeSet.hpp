#pragma once

#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseAvlBinarySearchTreeSet.hpp>

#include <memory>

namespace alba {

namespace algorithm {

template <typename Key>
class AvlBinarySearchTreeSet : public BaseAvlBinarySearchTreeSet<Key> {
public:
    using BaseClass = BaseAvlBinarySearchTreeSet<Key>;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;

protected:
    void putStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key) override {
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (key < currentKey) {
                putStartingOnThisNode(nodePointer->left, key);
                this->updateTreeNodeDetails(*nodePointer);
            } else if (key > currentKey) {
                putStartingOnThisNode(nodePointer->right, key);
                this->updateTreeNodeDetails(*nodePointer);
            }
        } else {
            nodePointer.reset(new Node{key, nullptr, nullptr, 1, 1});
        }
        this->reBalanceTreeOnPutAction(nodePointer);
    }
};

}  // namespace algorithm

}  // namespace alba
