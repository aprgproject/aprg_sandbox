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

// Tree shape depends on the order of insertion
// -> Best case: They are perfectly balanced.
// -> Worst case: Nodes are only placed on a single side (all are placed in left or all are placed in right).
// --->If the input came in sorted order this will happen.

// BST corresponds to quicksort partitioning
// There is a direct correspondence if the array has no duplicate keys.

// Proposition: if N distinct keys are inserted into a BST in random order, the expected number of compares for a search/insert is ~ 2*log2(N)
// Proof: 1-1 correspondence with quicksort partitioning.
// Worst case is ~4.311 ln N. This is proved by Bruce Reed in 2003.

// Alternating insertion and deletion (randomly) causes the tree to be asymmetric.
// Hibbard deletion approach of deleting the minimum to the right causes the tree to be asymmetric.
// Researchers discovered that after a long sequence of insertion and deletion the height becomes sqrt(N).
// If you randomly change the side of deletion, it does not work either. It still yields to sqrt(N).
// Long standing open problem: Simple and efficient delete for BSTs.

}

}
