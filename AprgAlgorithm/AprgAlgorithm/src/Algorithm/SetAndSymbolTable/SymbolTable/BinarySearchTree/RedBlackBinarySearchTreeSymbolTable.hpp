#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/SymbolTable/BinarySearchTree/Common/BaseRedBlackBinarySearchTreeSymbolTable.hpp>

namespace alba {

namespace algorithm {

template <typename Key, typename Value>
class RedBlackBinarySearchTreeSymbolTable
    : public BaseRedBlackBinarySearchTreeSymbolTable<Key, Value, RedBlackTreeNodeWithValue<Key, Value>> {
public:
    using BaseClass = BaseRedBlackBinarySearchTreeSymbolTable<Key, Value, RedBlackTreeNodeWithValue<Key, Value>>;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;

protected:
    void putStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key, Value const& value) override {
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (key < currentKey) {  // same as BST
                putStartingOnThisNode(nodePointer->left, key, value);
                this->updateTreeNodeDetails(*nodePointer);
            } else if (key > currentKey) {  // same as BST
                putStartingOnThisNode(nodePointer->right, key, value);
                this->updateTreeNodeDetails(*nodePointer);
            } else {  // equal to key
                nodePointer->value = value;
            }
            this->maintainRedBlackTreePropertyOnPut(nodePointer);
        } else {
            // every new node created has a red link -> this corresponds in 2-3 trees a change on node number (1 becomes
            // 2, 2 become 3, 3 becomes 4)
            nodePointer.reset(new Node{key, value, nullptr, nullptr, 1, RedBlackColor::Red});
        }
    }
};

}  // namespace algorithm

}  // namespace alba
