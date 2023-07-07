#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>

#include <memory>

namespace alba {

namespace algorithm {

template <typename KeyTemplateType, typename NodeTemplateType, typename BaseDataStructure>
class BaseAvlBinarySearchTree : public BaseBinarySearchTree<KeyTemplateType, NodeTemplateType, BaseDataStructure> {
public:
    using BaseClass = BaseBinarySearchTree<KeyTemplateType, NodeTemplateType, BaseDataStructure>;
    using Key = KeyTemplateType;
    using Node = NodeTemplateType;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;

    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
    ~BaseAvlBinarySearchTree() override = default;

protected:
    virtual void updateTreeNodeDetails(Node& node) const override {
        node.sizeOfThisSubTree = this->calculateSizeOfThisSubTree(node);
        node.heightOfThisSubTree = calculateHeightOfSubTree(node);
    }

    virtual void deleteBasedOnKeyStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key) override {
        BaseClass::deleteBasedOnKeyStartingOnThisNode(nodePointer, key);
        reBalanceTreeOnDeleteAction(nodePointer);
    }

    virtual void deleteMinimumStartingOnThisNode(NodeUniquePointer& nodePointer) override {
        BaseClass::deleteMinimumStartingOnThisNode(nodePointer);
        reBalanceTreeOnDeleteAction(nodePointer);
    }

    virtual void deleteMaximumStartingOnThisNode(NodeUniquePointer& nodePointer) override {
        BaseClass::deleteMaximumStartingOnThisNode(nodePointer);
        reBalanceTreeOnDeleteAction(nodePointer);
    }

    int getHeightOfSubTree(NodeUniquePointer const& nodePointer) const {
        int size(0);
        if (nodePointer) {
            size = nodePointer->heightOfThisSubTree;
        }
        return size;
    }

    int calculateHeightOfSubTree(Node const& node) const {
        return std::max(getHeightOfSubTree(node.left), getHeightOfSubTree(node.right)) + 1;
    }

    int calculateBalanceFactor(Node const& node) const {
        return getHeightOfSubTree(node.left) - getHeightOfSubTree(node.right);
    }

    void rotateLeft(NodeUniquePointer& nodePointer) {
        // This switches right child as the parent, switching the old parent as the left child (thus rotate left)
        if (nodePointer) {
            if (nodePointer->right) {
                NodeUniquePointer nodeToMove(std::move(nodePointer));

                // rotation happens here:
                nodePointer = std::move(nodeToMove->right);
                nodeToMove->right = std::move(nodePointer->left);
                nodePointer->left = std::move(nodeToMove);

                // update other things:
                NodeUniquePointer& previousNodePointer(nodePointer->left);
                this->updateTreeNodeDetails(*previousNodePointer);
                this->updateTreeNodeDetails(*nodePointer);
            }
        }
    }

    void rotateRight(NodeUniquePointer& nodePointer) {
        // This switches left child as the parent, switching the old parent as the right child (thus rotate right)
        if (nodePointer) {
            if (nodePointer->left) {
                NodeUniquePointer nodeToMove(std::move(nodePointer));

                // rotation happens here:
                nodePointer = std::move(nodeToMove->left);
                nodeToMove->left = std::move(nodePointer->right);
                nodePointer->right = std::move(nodeToMove);

                // update other things:
                NodeUniquePointer& previousNodePointer(nodePointer->right);
                this->updateTreeNodeDetails(*previousNodePointer);
                this->updateTreeNodeDetails(*nodePointer);
            }
        }
    }

    void reBalanceTreeOnPutAction(NodeUniquePointer& nodePointer) {
        if (nodePointer) {
            Node& node(*nodePointer);
            int balanceFactor = this->calculateBalanceFactor(node);
            if (balanceFactor > 1) {
                if (node.key < node.left->key) {
                    this->rotateRight(nodePointer);
                } else if (node.key > node.left->key) {
                    this->rotateLeft(node.left);
                    this->rotateRight(nodePointer);
                }
            }
            if (balanceFactor < -1) {
                if (node.key > node.right->key) {
                    this->rotateLeft(nodePointer);
                } else if (node.key < node.right->key) {
                    this->rotateRight(node.right);
                    this->rotateLeft(nodePointer);
                }
            }
        }
    }

    void reBalanceTreeOnDeleteAction(NodeUniquePointer& nodePointer) {
        if (nodePointer) {
            Node& node(*nodePointer);
            int balanceFactor = this->calculateBalanceFactor(node);
            if (balanceFactor > 1) {
                if (this->calculateBalanceFactor(*(node.left)) >= 0) {
                    this->rotateRight(nodePointer);
                } else {
                    this->rotateLeft(node.left);
                    this->rotateRight(nodePointer);
                }
            }
            if (balanceFactor < -1) {
                if (this->calculateBalanceFactor(*(node.right)) <= 0) {
                    this->rotateLeft(nodePointer);
                } else {
                    this->rotateRight(node.right);
                    this->rotateLeft(nodePointer);
                }
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba
