#pragma once

#include <Algorithm/SymbolTable/BinarySearchTree/Common/BaseBinarySearchTreeSymbolTable.hpp>
#include <Algorithm/SymbolTable/BinarySearchTree/Common/BinarySearchTreeNode.hpp>

#include <memory>

namespace alba
{

namespace algorithm
{

template <typename Key, typename Value, typename Node>
class BaseRedBlackBinarySearchTreeSymbolTable
        : public BaseBinarySearchTreeSymbolTable<Key, Value, Node>
{
public:
    using NodeUniquePointer = std::unique_ptr<Node>;

protected:
    void putStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key, Value const& value) override
    {
        if(nodePointer)
        {            Key const& currentKey(nodePointer->key);
            if(key < currentKey) // same as BST
            {
                putStartingOnThisNode(nodePointer->left, key, value);                nodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
            else if(key > currentKey) // same as BST
            {
                putStartingOnThisNode(nodePointer->right, key, value);
                nodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
            else // equal to key
            {
                nodePointer->value = value;
            }
            if(hasARightLeaningRedLinkOnOneChild(nodePointer)) // rotate a right leaning red link to the left
            {
                // need to maintain: Red links lean left.
                // there is a case that rotating a right leaning red link cause 2 consecutive red links and this is caught in the next condition
                rotateLeft(nodePointer);
            }
            if(hasTwoLeftLeaningRedLinksInARow(nodePointer)) // rotate one left leaning red link to the right temporarily and then flip colors
            {
                // need to maintain: No node has two red links connected to it.
                // since there are 2 red link in a row, rotate one to the right
                // this causes all children to have red links which satisfy the next condition and then flip colors
                rotateRight(nodePointer);
            }
            if(hasTwoRedLinksOnItsChildren(nodePointer))
            {
                // need to maintain: No node has two red links connected to it.
                // flip colors -> this corresponds in 2-3 trees of splitting a 4 node
                setParentAsRedAndChildrenAsBlack(nodePointer);
            }
        }
        else
        {
            // every new node created has a red link -> this corresponds in 2-3 trees a change on node number (1 becomes 2, 2 become 3, 3 becomes 4)
            nodePointer.reset(new Node{key, value, nullptr, nullptr, 1U, BinarySearchTreeNode::Color::Red});
        }
    }

    inline bool isRed(NodeUniquePointer const& nodePointer) const
    {
        bool result(false);
        if(nodePointer)        {
            result = nodePointer->parentLinkColor == BinarySearchTreeNode::Color::Red;
        }
        return result;    }

    inline bool hasARightLeaningRedLinkOnOneChild(NodeUniquePointer const& nodePointer) const
    {
        return isRed(nodePointer->right) && !isRed(nodePointer->left);
    }

    inline bool hasTwoLeftLeaningRedLinksInARow(NodeUniquePointer const& nodePointer) const
    {
        return nodePointer->left && isRed(nodePointer->left) && isRed(nodePointer->left->left);
    }

    inline bool hasTwoRedLinksOnItsChildren(NodeUniquePointer const& nodePointer) const
    {
        return isRed(nodePointer->left) && isRed(nodePointer->right);
    }

    void rotateLeft(NodeUniquePointer & nodePointer)
    {
        // This switches right child as the parent, switching the old parent as the left child (thus rotate left)
        // It also switches the right leaning link to left leaning link (useful to maintain red links lean left)
        if(nodePointer)
        {
            if(nodePointer->right)
            {
                NodeUniquePointer nodeToMove(std::move(nodePointer));

                // rotation happens here:
                nodePointer = std::move(nodeToMove->right);
                nodeToMove->right = std::move(nodePointer->left);
                nodePointer->left = std::move(nodeToMove);

                // update other things:
                NodeUniquePointer & previousNodePointer(nodePointer->left);
                nodePointer->parentLinkColor = previousNodePointer->parentLinkColor;
                nodePointer->numberOfNodesOnThisSubTree = previousNodePointer->numberOfNodesOnThisSubTree;
                previousNodePointer->parentLinkColor = BinarySearchTreeNode::Color::Red;
                previousNodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(previousNodePointer);
            }
        }
    }

    void rotateRight(NodeUniquePointer & nodePointer)
    {
        // This switches left child as the parent, switching the old parent as the right child (thus rotate right)
        // It also switches the left leaning link to right leaning link (useful to change red links lean right)
        if(nodePointer)
        {
            if(nodePointer->left)
            {
                NodeUniquePointer nodeToMove(std::move(nodePointer));

                // rotation happens here:
                nodePointer = std::move(nodeToMove->left);
                nodeToMove->left = std::move(nodePointer->right);
                nodePointer->right = std::move(nodeToMove);

                // update other things:
                NodeUniquePointer & previousNodePointer(nodePointer->right);
                nodePointer->parentLinkColor = previousNodePointer->parentLinkColor;
                nodePointer->numberOfNodesOnThisSubTree = previousNodePointer->numberOfNodesOnThisSubTree;
                previousNodePointer->parentLinkColor = BinarySearchTreeNode::Color::Red;
                previousNodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(previousNodePointer);
            }
        }
    }

    void setParentAsRedAndChildrenAsBlack(NodeUniquePointer & nodePointer)
    {
        // used to flip colors (split a 4 node in 2-3 trees)
        if(nodePointer)
        {
            nodePointer->parentLinkColor = BinarySearchTreeNode::Color::Red;
            if(nodePointer->left)
            {
                nodePointer->left->parentLinkColor = BinarySearchTreeNode::Color::Black;
            }
            if(nodePointer->right)
            {
                nodePointer->right->parentLinkColor = BinarySearchTreeNode::Color::Black;
            }
        }
    }
};

// Motivation: Represent a 2-3 tree as a BST.
// Use internal left leaning link as glue for the 3-nodes (color this link red -> so that we can know which link belonging to 3 nodes) which one don't

// An equivalent definition, a BST such that
// -> No node has two red links connected to it.
// -> Every path from root to null link as the same number of black links (perfect black balance)
// -> Red links lean left.

// One to one correspondence to 2-3 tree and red black BST.

// Same code for BST for search (but since its balanced, red-black BSTs are faster)
// Every node has only one parent link, use the node to save the color of the parent link

// Rotation:
// During an insertion operation, sometimes there can be red links that are leaning in the wrong direction.
// Left rotation: take a right leaning red link -> reorient it to lean to the left
// Right rotation: take a left leaning red link -> temporarily reorient it to lean to the right

// Basic strategy. Maintain one to one correspondence with 2-3 trees by applying elementary red black BST operations
// Insertion: Every time we add a node, create a red link to its parents -> this corresponds in 2-3 trees a change on node number (1 becomes 2, 2 become 3, 3 becomes 4)

// Longest path is alternating red and black can be no more as twice as long as the shortest path which is all black

// Proposition: Height of the tree is <= 2*log2(N) in the worst case.
// Proof: correspondence to 2-3 tree
// -> Every path from root to null link has same number black links
// -> Never two red links in a row
// -> Property. Height of tree is ~ 1.00 log2(N) in typical applications.

// Why red black? On Xerox PARC, laser printing -> red color looks best

}

}
