#pragma once

#include <Algorithm/SetAndSymbolTable/SymbolTable/BinarySearchTree/Common/BaseAvlBinarySearchTreeSymbolTable.hpp>

#include <memory>

namespace alba {

namespace algorithm {

template <typename Key, typename Value>
class AvlBinarySearchTreeSymbolTable : public BaseAvlBinarySearchTreeSymbolTable<Key, Value> {
public:
    using BaseClass = BaseAvlBinarySearchTreeSymbolTable<Key, Value>;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;

protected:
    void putStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key, Value const& value) override {
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (key < currentKey) {
                putStartingOnThisNode(nodePointer->left, key, value);
                this->updateTreeNodeDetails(*nodePointer);
            } else if (key > currentKey) {
                putStartingOnThisNode(nodePointer->right, key, value);
                this->updateTreeNodeDetails(*nodePointer);
            } else {
                nodePointer->value = value;
            }
        } else {
            nodePointer.reset(new Node{key, value, nullptr, nullptr, 1, 1});
        }
        this->reBalanceTreeOnPutAction(nodePointer);
    }
};

}  // namespace algorithm

}  // namespace alba
