#pragma once

#include <SymbolTable/BinarySearchTree/BaseBinarySearchTreeSymbolTable.hpp>
#include <SymbolTable/BinarySearchTree/BinarySearchTreeNode.hpp>

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value>
class BinarySearchTreeSymbolTable
        : public BaseBinarySearchTreeSymbolTable<Key, Value, BinarySearchTreeNode::BasicTreeNode<Key, Value>>{

public:
    using Node = BinarySearchTreeNode::BasicTreeNode<Key, Value>;    using NodeUniquePointer = std::unique_ptr<Node>;

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
            }
        }
        else
        {
            nodePointer.reset(new Node{key, value, nullptr, nullptr, 1U});
        }
    }
};

}

}