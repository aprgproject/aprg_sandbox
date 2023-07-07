#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseRedBlackBinarySearchTreeSet.hpp>

namespace alba {

namespace algorithm {

template <typename Key>
class RedBlackBinarySearchTreeSet : public BaseRedBlackBinarySearchTreeSet<Key, RedBlackTreeNode<Key>> {
public:
    using BaseClass = BaseRedBlackBinarySearchTreeSet<Key, RedBlackTreeNode<Key>>;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;

protected:
    void putStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key) override {
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (key < currentKey)  // same as BST
            {
                putStartingOnThisNode(nodePointer->left, key);
                this->updateTreeNodeDetails(*nodePointer);
            } else if (key > currentKey)  // same as BST
            {
                putStartingOnThisNode(nodePointer->right, key);
                this->updateTreeNodeDetails(*nodePointer);
            }
            this->maintainRedBlackTreePropertyOnPut(nodePointer);
        } else {
            // every new node created has a red link -> this corresponds in 2-3 trees a change on node number (1 becomes
            // 2, 2 become 3, 3 becomes 4)
            nodePointer.reset(new Node{key, nullptr, nullptr, 1, RedBlackColor::Red});
        }
    }
};

}  // namespace algorithm

}  // namespace alba
