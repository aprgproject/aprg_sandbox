#pragma once

#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseBinarySearchTreeSet.hpp>

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Key>
class BinarySearchTreeSet
        : public BaseBinarySearchTreeSet<Key>
{
public:
    using BaseClass = BaseBinarySearchTreeSet<Key>;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;

protected:

    void putStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key) override
    {
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                putStartingOnThisNode(nodePointer->left, key);
                this->updateTreeNodeDetails(*nodePointer);
            }
            else if(key > currentKey)
            {
                putStartingOnThisNode(nodePointer->right, key);
                this->updateTreeNodeDetails(*nodePointer);
            }
        }
        else
        {
            nodePointer.reset(new Node{key, nullptr, nullptr, 1U});
        }
    }
};

}

}