#pragma once

#include <Algorithm/SymbolTable/BinarySearchTree/Common/BaseBinarySearchTreeSymbolTable.hpp>
#include <Algorithm/SymbolTable/BinarySearchTree/Common/BinarySearchTreeNode.hpp>

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Key> bool isEqualThanWithDepth(Key const& key1, Key const& key2, unsigned int const depth);
template <typename Key> bool isLessThanWithDepth(Key const& key1, Key const& key2, unsigned int const depth);
template <typename Key> bool isGreaterThanWithDepth(Key const& key1, Key const& key2, unsigned int const depth);

template <typename Key, typename Value>
class KdTree
        : public BaseBinarySearchTreeSymbolTable<Key, Value, BinarySearchTreeNode::BasicTreeNode<Key, Value>>
{
public:
    using BaseClass = BaseBinarySearchTreeSymbolTable<Key, Value, BinarySearchTreeNode::BasicTreeNode<Key, Value>>;
    using Node = BinarySearchTreeNode::BasicTreeNode<Key, Value>;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;
    using Keys = typename BaseClass::Keys;

    KdTree()
        : BaseClass()
    {}

protected:

    bool doesContainStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
    {
        static unsigned int depth=0;
        depth++;
        bool result(false);
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(isLessThanWithDepth(key, currentKey, depth))
            {
                result = doesContainStartingOnThisNode(nodePointer->left, key);
            }
            else if(isGreaterThanWithDepth(key, currentKey, depth))
            {
                result = doesContainStartingOnThisNode(nodePointer->right, key);
            }
            else
            {
                result = true;
            }
        }
        depth--;
        return result;
    }

    Value getStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
    {
        static unsigned int depth=0;
        depth++;
        Value result{};
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(isLessThanWithDepth(key, currentKey, depth))
            {
                result = getStartingOnThisNode(nodePointer->left, key);
            }
            else if(isGreaterThanWithDepth(key, currentKey, depth))
            {
                result = getStartingOnThisNode(nodePointer->right, key);
            }
            else
            {
                result = nodePointer->value;
            }
        }
        depth--;
        return result;
    }

    Node const* getNodeWithFloorStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
    {
        static unsigned int depth=0;
        depth++;
        Node const* result(nullptr);
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(isEqualThanWithDepth(key, currentKey, depth))
            {
                result = nodePointer.get();
            }
            else if(isLessThanWithDepth(key, currentKey, depth))
            {
                // current key is larger -> go the left
                result = getNodeWithFloorStartingOnThisNode(nodePointer->left, key);
            }
            else
            {
                // current key is smaller -> starting in the right child, find the left most node in the subtree
                Node const*const nodeWithFloorAtRight(getNodeWithFloorStartingOnThisNode(nodePointer->right, key));
                if(nodeWithFloorAtRight != nullptr)
                {
                    // return the found value
                    result = nodeWithFloorAtRight;
                }
                else
                {
                    // if no values found then this node is the left most node that is less than the value of the key
                    result = nodePointer.get();
                }
            }
        }
        depth--;
        return result;
    }

    Node const* getNodeWithCeilingStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
    {
        static unsigned int depth=0;
        depth++;
        Node const* result(nullptr);
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(isEqualThanWithDepth(key, currentKey, depth))
            {
                result = nodePointer.get();
            }
            else if(isGreaterThanWithDepth(key, currentKey, depth))
            {
                result = getNodeWithCeilingStartingOnThisNode(nodePointer->right, key);
            }
            else
            {
                Node const*const nodeWithCeilingAtLeft(getNodeWithCeilingStartingOnThisNode(nodePointer->left, key));
                if(nodeWithCeilingAtLeft != nullptr)
                {
                    result = nodeWithCeilingAtLeft;
                }
                else
                {
                    result = nodePointer.get();
                }
            }
        }
        depth--;
        return result;
    }

    unsigned int getRankStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
    {
        static unsigned int depth=0;
        depth++;
        unsigned int result(0);
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(isLessThanWithDepth(key, currentKey, depth))
            {
                result = getRankStartingOnThisNode(nodePointer->left, key); // recursively check rank on the right side
            }
            else if(isGreaterThanWithDepth(key, currentKey, depth))
            {
                // get size of left, add one node for this node, and add the rank on the right side
                result = 1 + this->getSizeOnThisNode(nodePointer->left) + getRankStartingOnThisNode(nodePointer->right, key);
            }
            else
            {
                result = this->getSizeOnThisNode(nodePointer->left); // if equal, just get size of the subtree
            }
        }
        depth--;
        return result;
    }

    void putStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key, Value const& value) override
    {
        static unsigned int depth=0;
        depth++;
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(isLessThanWithDepth(key, currentKey, depth))
            {
                putStartingOnThisNode(nodePointer->left, key, value);
                nodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
            else if(isGreaterThanWithDepth(key, currentKey, depth))
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
        depth--;
    }

    void deleteBasedOnKeyStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key)
    {
        static unsigned int depth=0;
        depth++;
        //this is called hibbard deletion
        if(nodePointer)
        {
            if(isLessThanWithDepth(key, nodePointer->key, depth)) // search for the node in the left in less than
            {
                deleteBasedOnKeyStartingOnThisNode(nodePointer->left, key);
            }
            else if(isGreaterThanWithDepth(key, nodePointer->key, depth)) // search for the node in the right in greater than
            {
                deleteBasedOnKeyStartingOnThisNode(nodePointer->right, key);
            }
            else // if found
            {
                // get the minimum on the right
                // place the values of the minimum on this node and then delete it
                // why are we using deletion of minimum on the right instead of deletion of maximum in the left? No real reason.
                NodeUniquePointer & minimumOnTheRight(this->getMinimumNodePointerReferenceStartingOnThisNode(nodePointer->right));
                if(!minimumOnTheRight)
                {
                    nodePointer.reset(nullptr);
                }
                else
                {
                    nodePointer->key = minimumOnTheRight->key;
                    nodePointer->value = minimumOnTheRight->value;
                    this->deleteMinimumStartingOnThisNode(minimumOnTheRight); // starting from the minimum so less checks
                }
            }
            if(nodePointer)
            {
                nodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
        }
        depth--;
    }

    void retrieveKeysInRangeInclusiveStartingOnThisNode(Keys & keys, NodeUniquePointer const& nodePointer, Key const& low, Key const& high) const
    {
        static unsigned int depth=0;
        depth++;
        if(nodePointer)
        {
            if(isLessThanWithDepth(low, nodePointer->key, depth))
            {
                retrieveKeysInRangeInclusiveStartingOnThisNode(keys, nodePointer->left, low, high);
            }
            if((isLessThanWithDepth(low, nodePointer->key, depth) || isEqualThanWithDepth(low, nodePointer->key, depth))
                    && (isGreaterThanWithDepth(high, nodePointer->key, depth) || isEqualThanWithDepth(high, nodePointer->key, depth)))
            {
                keys.emplace_back(nodePointer->key);
            }
            if(isGreaterThanWithDepth(high, nodePointer->key, depth))
            {
                retrieveKeysInRangeInclusiveStartingOnThisNode(keys, nodePointer->right, low, high);
            }
        }
        depth--;
    }
};

}

}
