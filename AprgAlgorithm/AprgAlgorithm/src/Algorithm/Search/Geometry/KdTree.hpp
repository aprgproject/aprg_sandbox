#pragma once

#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseBinarySearchTreeSet.hpp>

#include <memory>

namespace alba {

namespace algorithm {

template <typename Key>
bool isEqualThanWithDepth(Key const& key1, Key const& key2, int const depth);
template <typename Key>
bool isLessThanWithDepth(Key const& key1, Key const& key2, int const depth);
template <typename Key>
bool isGreaterThanWithDepth(Key const& key1, Key const& key2, int const depth);

template <typename Key>
class KdTree : public BaseBinarySearchTreeSet<Key> {
public:
    using BaseClass = BaseBinarySearchTreeSet<Key>;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;
    using Keys = typename BaseClass::Keys;

    KdTree() = default;

protected:
    bool doesContainStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const override {
        static int depth = 0;
        depth++;
        bool result(false);
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (isLessThanWithDepth(key, currentKey, depth)) {
                result = doesContainStartingOnThisNode(nodePointer->left, key);
            } else if (isGreaterThanWithDepth(key, currentKey, depth)) {
                result = doesContainStartingOnThisNode(nodePointer->right, key);
            } else {
                result = true;
            }
        }
        depth--;
        return result;
    }

    Node const* getNodeWithFloorStartingOnThisNode(
        NodeUniquePointer const& nodePointer, Key const& key) const override {
        static int depth = 0;
        depth++;
        Node const* result(nullptr);
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (isEqualThanWithDepth(key, currentKey, depth)) {
                result = nodePointer.get();
            } else if (isLessThanWithDepth(key, currentKey, depth)) {
                // current key is larger -> go the left
                result = getNodeWithFloorStartingOnThisNode(nodePointer->left, key);
            } else {
                // current key is smaller -> starting in the right child, find the left most node in the subtree
                Node const* const nodeWithFloorAtRight(getNodeWithFloorStartingOnThisNode(nodePointer->right, key));
                if (nodeWithFloorAtRight != nullptr) {
                    // return if found
                    result = nodeWithFloorAtRight;
                } else {
                    // if no nodes found then this node is the left most node that is less than the key
                    result = nodePointer.get();
                }
            }
        }
        depth--;
        return result;
    }

    Node const* getNodeWithCeilingStartingOnThisNode(
        NodeUniquePointer const& nodePointer, Key const& key) const override {
        static int depth = 0;
        depth++;
        Node const* result(nullptr);
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (isEqualThanWithDepth(key, currentKey, depth)) {
                result = nodePointer.get();
            } else if (isGreaterThanWithDepth(key, currentKey, depth)) {
                result = getNodeWithCeilingStartingOnThisNode(nodePointer->right, key);
            } else {
                Node const* const nodeWithCeilingAtLeft(getNodeWithCeilingStartingOnThisNode(nodePointer->left, key));
                if (nodeWithCeilingAtLeft != nullptr) {
                    result = nodeWithCeilingAtLeft;
                } else {
                    result = nodePointer.get();
                }
            }
        }
        depth--;
        return result;
    }

    int getRankStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const override {
        static int depth = 0;
        depth++;
        int result(0);
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (isLessThanWithDepth(key, currentKey, depth)) {
                result = getRankStartingOnThisNode(nodePointer->left, key);  // recursively check rank on the right side
            } else if (isGreaterThanWithDepth(key, currentKey, depth)) {
                // get size of left, add one node for this node, and add the rank on the right side
                result =
                    1 + this->getSizeOnThisNode(nodePointer->left) + getRankStartingOnThisNode(nodePointer->right, key);
            } else {
                result = this->getSizeOnThisNode(nodePointer->left);  // if equal, just get size of the subtree
            }
        }
        depth--;
        return result;
    }

    void putStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key) override {
        static int depth = 0;
        depth++;
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (isLessThanWithDepth(key, currentKey, depth)) {
                putStartingOnThisNode(nodePointer->left, key);
                this->updateTreeNodeDetails(*nodePointer);
            } else if (isGreaterThanWithDepth(key, currentKey, depth)) {
                putStartingOnThisNode(nodePointer->right, key);
                this->updateTreeNodeDetails(*nodePointer);
            } else {
                // if equal, just pick left
                putStartingOnThisNode(nodePointer->left, key);
                this->updateTreeNodeDetails(*nodePointer);
            }
        } else {
            nodePointer.reset(new Node{key, nullptr, nullptr, 1});
        }
        depth--;
    }

    void deleteBasedOnKeyStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key) override {
        static int depth = 0;
        depth++;
        // this is called hibbard deletion
        if (nodePointer) {
            if (isLessThanWithDepth(key, nodePointer->key, depth)) {
                // search for the node in the left in less than
                deleteBasedOnKeyStartingOnThisNode(nodePointer->left, key);
            } else if (isGreaterThanWithDepth(key, nodePointer->key, depth)) {
                // search for the node in the right in greater than
                deleteBasedOnKeyStartingOnThisNode(nodePointer->right, key);
            } else  // if found
            {
                // get the minimum on the right
                // place the keys of the minimum on this node and then delete it
                // why are we using deletion of minimum on the right instead of deletion of maximum in the left? No real
                // reason.
                NodeUniquePointer& minimumOnTheRight(
                    this->getMinimumNodePointerReferenceStartingOnThisNode(nodePointer->right));
                if (!minimumOnTheRight) {
                    nodePointer.reset(nullptr);
                } else {
                    this->copyContents(*nodePointer, *minimumOnTheRight);
                    // starting from the minimum so less checks
                    this->deleteMinimumStartingOnThisNode(minimumOnTheRight);
                }
            }
            if (nodePointer) {
                this->updateTreeNodeDetails(*nodePointer);
            }
        }
        depth--;
    }

    void retrieveKeysInRangeInclusiveStartingOnThisNode(
        Keys& keys, NodeUniquePointer const& nodePointer, Key const& low, Key const& high) const override {
        static int depth = 0;
        depth++;
        if (nodePointer) {
            if (isLessThanWithDepth(low, nodePointer->key, depth)) {
                retrieveKeysInRangeInclusiveStartingOnThisNode(keys, nodePointer->left, low, high);
            }
            if ((isLessThanWithDepth(low, nodePointer->key, depth) ||
                 isEqualThanWithDepth(low, nodePointer->key, depth)) &&
                (isGreaterThanWithDepth(high, nodePointer->key, depth) ||
                 isEqualThanWithDepth(high, nodePointer->key, depth))) {
                keys.emplace_back(nodePointer->key);
            }
            if (isGreaterThanWithDepth(high, nodePointer->key, depth)) {
                retrieveKeysInRangeInclusiveStartingOnThisNode(keys, nodePointer->right, low, high);
            }
        }
        depth--;
    }
};

}  // namespace algorithm

}  // namespace alba
