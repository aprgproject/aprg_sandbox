#pragma once

#include <SymbolTable/BinarySearchTree/BaseBinarySearchTreeSymbolTable.hpp>
#include <SymbolTable/BinarySearchTree/BinarySearchTreeNode.hpp>

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value>
class RedBlackBinarySearchTreeSymbolTable
        : public BaseBinarySearchTreeSymbolTable<Key, Value, BinarySearchTreeNode::RedBlackTreeNode<Key, Value>>{
public:
    using Node = BinarySearchTreeNode::RedBlackTreeNode<Key, Value>;
    using NodeUniquePointer = std::unique_ptr<Node>;
    void put(Key const& key, Value const& value) override
    {
        putStartingOnThisNode(this->m_root, key, value);
    }

protected:
    void putStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key, Value const& value)
    {
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                putStartingOnThisNode(nodePointer->left, key, value);
                nodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
            else if(key > currentKey)
            {
                putStartingOnThisNode(nodePointer->right, key, value);
                nodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
            else
            {
                nodePointer->value = value;
                if(isRed(nodePointer->right) && !isRed(nodePointer->left))
                {
                    rotateLeft(nodePointer);
                }
                if(nodePointer->left && isRed(nodePointer->left) && isRed(nodePointer->left->left))
                {
                    rotateRight(nodePointer);
                }
                if(isRed(nodePointer->left) && isRed(nodePointer->right))
                {
                    setRedNodeAndBlackSubNodes(nodePointer);
                }
            }
        }
        else
        {
            nodePointer.reset(new Node{key, value, nullptr, nullptr, 1U, BinarySearchTreeNode::Color::Red});
        }
    }

    bool isRed(NodeUniquePointer const& nodePointer) const
    {
        bool result(false);
        if(nodePointer)
        {
            result = nodePointer->color == BinarySearchTreeNode::Color::Red;
        }
        return result;
    }

    void rotateLeft(NodeUniquePointer & nodePointer)
    {
        // This switches right child as the parent, switching the old parent as the left child (thus rotate left)
        if(nodePointer)
        {
            if(nodePointer->right)
            {
                NodeUniquePointer oldNodePointer(std::move(nodePointer));
                nodePointer = std::move(oldNodePointer->right);
                oldNodePointer->right = std::move(nodePointer->left);
                nodePointer->left = std::move(oldNodePointer);
                nodePointer->color = oldNodePointer->color;
                oldNodePointer->color = BinarySearchTreeNode::Color::Red;
                nodePointer->numberOfNodesOnThisSubTree = oldNodePointer->numberOfNodesOnThisSubTree;
                oldNodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(oldNodePointer);
            }
        }
    }

    void rotateRight(NodeUniquePointer & nodePointer)
    {
        // This switches left child as the parent, switching the old parent as the right child (thus rotate right)
        if(nodePointer)
        {
            if(nodePointer->left)
            {
                NodeUniquePointer oldNodePointer(std::move(nodePointer));
                nodePointer = std::move(oldNodePointer->left);
                oldNodePointer->left = std::move(nodePointer->right);
                nodePointer->right = std::move(oldNodePointer);
                nodePointer->color = oldNodePointer->color;
                oldNodePointer->color = BinarySearchTreeNode::Color::Red;
                nodePointer->numberOfNodesOnThisSubTree = oldNodePointer->numberOfNodesOnThisSubTree;
                oldNodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(oldNodePointer);
            }
        }
    }

    void setRedNodeAndBlackSubNodes(NodeUniquePointer & nodePointer)
    {
        if(nodePointer)
        {
            nodePointer->color = BinarySearchTreeNode::Color::Red;
            if(nodePointer->left)
            {
                nodePointer->left->color = BinarySearchTreeNode::Color::Black;
            }
            if(nodePointer->right)
            {
                nodePointer->right->color = BinarySearchTreeNode::Color::Black;
            }
        }
    }
};

}

}