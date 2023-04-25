#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNode.hpp>
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
            if (key < currentKey)  // same as BST
            {
                putStartingOnThisNode(nodePointer->left, key, value);
                this->updateTreeNodeDetails(*nodePointer);
            } else if (key > currentKey)  // same as BST
            {
                putStartingOnThisNode(nodePointer->right, key, value);
                this->updateTreeNodeDetails(*nodePointer);
            } else  // equal to key
            {
                nodePointer->value = value;
            }
            if (this->hasARightLeaningRedLinkOnOneChild(nodePointer))  // rotate a right leaning red link to the left
            {
                // need to maintain: Red links lean left.
                // there is a case that rotating a right leaning red link cause 2 consecutive red links and this is
                // caught in the next condition
                this->rotateLeft(nodePointer);
            }
            if (this->hasTwoLeftLeaningRedLinksInARow(
                    nodePointer))  // rotate one left leaning red link to the right temporarily and then flip colors
            {
                // need to maintain: No node has two red links connected to it.
                // since there are 2 red link in a row, rotate one to the right
                // this causes all children to have red links which satisfy the next condition and then flip colors
                this->rotateRight(nodePointer);
            }
            if (this->hasTwoRedLinksOnItsChildren(nodePointer)) {
                // need to maintain: No node has two red links connected to it.
                // flip colors -> this corresponds in 2-3 trees of splitting a 4 node
                this->setParentAsRedAndChildrenAsBlack(nodePointer);
            }
        } else {
            // every new node created has a red link -> this corresponds in 2-3 trees a change on node number (1 becomes
            // 2, 2 become 3, 3 becomes 4)
            nodePointer.reset(new Node{key, value, nullptr, nullptr, 1U, RedBlackColor::Red});
        }
    }
};

}  // namespace algorithm

}  // namespace alba
