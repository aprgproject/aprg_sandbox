#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BaseBinarySearchTree.hpp>
#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>

#include <memory>

namespace alba {

namespace algorithm {

template <typename KeyTemplateType, typename NodeTemplateType, typename BaseDataStructure>
class BaseRedBlackBinarySearchTree : public BaseBinarySearchTree<KeyTemplateType, NodeTemplateType, BaseDataStructure> {
public:
    using BaseClass = BaseBinarySearchTree<KeyTemplateType, NodeTemplateType, BaseDataStructure>;
    using Key = KeyTemplateType;
    using Node = NodeTemplateType;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;

    // no need for virtual destructor because base destructor is virtual (similar to other virtual functions)
    ~BaseRedBlackBinarySearchTree() override = default;

protected:
    inline bool isRed(NodeUniquePointer const& nodePointer) const {
        bool result(false);
        if (nodePointer) {
            result = nodePointer->parentLinkColor == RedBlackColor::Red;
        }
        return result;
    }

    inline bool hasARightLeaningRedLinkOnOneChild(NodeUniquePointer const& nodePointer) const {
        return isRed(nodePointer->right) && !isRed(nodePointer->left);
    }

    inline bool hasTwoLeftLeaningRedLinksInARow(NodeUniquePointer const& nodePointer) const {
        return nodePointer->left && isRed(nodePointer->left) && isRed(nodePointer->left->left);
    }

    inline bool hasTwoRedLinksOnItsChildren(NodeUniquePointer const& nodePointer) const {
        return isRed(nodePointer->left) && isRed(nodePointer->right);
    }

    void rotateLeft(NodeUniquePointer& nodePointer) {
        // This switches right child as the parent, switching the old parent as the left child (thus rotate left)
        // It also switches the right leaning link to left leaning link (useful to maintain red links lean left)
        if (nodePointer) {
            if (nodePointer->right) {
                NodeUniquePointer nodeToMove(std::move(nodePointer));

                // rotation happens here:
                nodePointer = std::move(nodeToMove->right);
                nodeToMove->right = std::move(nodePointer->left);
                nodePointer->left = std::move(nodeToMove);

                // update other things:
                NodeUniquePointer& previousNodePointer(nodePointer->left);
                nodePointer->parentLinkColor = previousNodePointer->parentLinkColor;
                nodePointer->sizeOfThisSubTree = previousNodePointer->sizeOfThisSubTree;
                previousNodePointer->parentLinkColor = RedBlackColor::Red;
                this->updateTreeNodeDetails(*previousNodePointer);
            }
        }
    }

    void rotateRight(NodeUniquePointer& nodePointer) {
        // This switches left child as the parent, switching the old parent as the right child (thus rotate right)
        // It also switches the left leaning link to right leaning link (useful to change red links lean right)
        if (nodePointer) {
            if (nodePointer->left) {
                NodeUniquePointer nodeToMove(std::move(nodePointer));

                // rotation happens here:
                nodePointer = std::move(nodeToMove->left);
                nodeToMove->left = std::move(nodePointer->right);
                nodePointer->right = std::move(nodeToMove);

                // update other things:
                NodeUniquePointer& previousNodePointer(nodePointer->right);
                nodePointer->parentLinkColor = previousNodePointer->parentLinkColor;
                nodePointer->sizeOfThisSubTree = previousNodePointer->sizeOfThisSubTree;
                previousNodePointer->parentLinkColor = RedBlackColor::Red;
                this->updateTreeNodeDetails(*previousNodePointer);
            }
        }
    }

    void setParentAsRedAndChildrenAsBlack(NodeUniquePointer const& nodePointer) {
        // used to flip colors (split a 4 node in 2-3 trees)
        if (nodePointer) {
            nodePointer->parentLinkColor = RedBlackColor::Red;
            if (nodePointer->left) {
                nodePointer->left->parentLinkColor = RedBlackColor::Black;
            }
            if (nodePointer->right) {
                nodePointer->right->parentLinkColor = RedBlackColor::Black;
            }
        }
    }
};

}  // namespace algorithm

}  // namespace alba

// Motivation: Represent a 2-3 tree as a BST.
// Use internal left leaning link as glue for the 3-nodes (color this link red -> so that we can know which link
// belonging to 3 nodes) which one don't

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
// Insertion: Every time we add a node, create a red link to its parents -> this corresponds in 2-3 trees a change on
// node number (1 becomes 2, 2 become 3, 3 becomes 4)

// Longest path is alternating red and black can be no more as twice as long as the shortest path which is all black

// Proposition: Height of the tree is <= 2*log2(N) in the worst case.
// Proof: correspondence to 2-3 tree
// -> Every path from root to null link has same number black links
// -> Never two red links in a row
// -> Property. Height of tree is ~ 1.00 log2(N) in typical applications.

// Why red black? On Xerox PARC, laser printing -> red color looks best
