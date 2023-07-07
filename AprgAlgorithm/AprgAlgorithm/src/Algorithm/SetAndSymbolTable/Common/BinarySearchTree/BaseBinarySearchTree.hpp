#pragma once

#include <functional>
#include <memory>
#include <vector>

namespace alba {

namespace algorithm {

template <typename KeyTemplateType, typename NodeTemplateType, typename BaseDataStructure>
class BaseBinarySearchTree : public BaseDataStructure {
public:
    using Key = KeyTemplateType;
    using Node = NodeTemplateType;
    using NodeUniquePointer = std::unique_ptr<Node>;
    using Keys = std::vector<Key>;
    using TraverseFunction = std::function<void(Node const&)>;

    virtual ~BaseBinarySearchTree() = default;  // virtual destructor because of virtual functions (vtable exists)

    bool isEmpty() const override { return getSize() == 0; }

    bool doesContain(Key const& key) const override { return doesContainStartingOnThisNode(m_root, key); }

    int getSize() const override { return getSizeOfThisSubTree(m_root); }

    int getRank(Key const& key) const override { return getRankStartingOnThisNode(m_root, key); }

    Key getMinimum() const override {
        Key result{};
        Node const* const nodePointer(getMinimumNodeStartingOnThisNode(m_root));
        if (nodePointer != nullptr) {
            result = nodePointer->key;
        }
        return result;
    }

    Key getMaximum() const override {
        Key result{};
        Node const* const nodePointer(getMaximumNodeStartingOnThisNode(m_root));
        if (nodePointer != nullptr) {
            result = nodePointer->key;
        }
        return result;
    }

    Key selectAt(int const index) const override {
        Key result{};
        Node const* const nodePointer(selectNodeWithIndexStartingOnThisNode(m_root, index));
        if (nodePointer != nullptr) {
            result = nodePointer->key;
        }
        return result;
    }

    Key getFloor(Key const& key) const override {
        Key result{};
        Node const* const nodePointer(getNodeWithFloorStartingOnThisNode(m_root, key));
        if (nodePointer != nullptr) {
            result = nodePointer->key;
        }
        return result;
    }

    Key getCeiling(Key const& key) const override {
        Key result{};
        Node const* const nodePointer(getNodeWithCeilingStartingOnThisNode(m_root, key));
        if (nodePointer != nullptr) {
            result = nodePointer->key;
        }
        return result;
    }

    NodeUniquePointer const& getRoot() const { return m_root; }

    void deleteBasedOnKey(Key const& key) override { deleteBasedOnKeyStartingOnThisNode(m_root, key); }

    void deleteMinimum() override { deleteMinimumStartingOnThisNode(m_root); }

    void deleteMaximum() override { deleteMaximumStartingOnThisNode(m_root); }

    Keys getKeys() const override {
        Keys result;
        retrieveKeysStartingOnThisNode(result, m_root);
        return result;
    }

    Keys getKeysInRangeInclusive(Key const& low, Key const& high) const override {
        Keys result;
        retrieveKeysInRangeInclusiveStartingOnThisNode(result, m_root, low, high);
        return result;
    }

    void traverseByPreOrder(TraverseFunction const& traverseFunction) { traverseByPreOrder(m_root, traverseFunction); }

    void traverseByInOrder(TraverseFunction const& traverseFunction) { traverseByInOrder(m_root, traverseFunction); }

    void traverseByPostOrder(TraverseFunction const& traverseFunction) {
        traverseByPostOrder(m_root, traverseFunction);
    }

protected:
    virtual void copyNodeContents(Node& destinationNode, Node const& sourceNode) const = 0;

    int getSizeOfThisSubTree(NodeUniquePointer const& nodePointer) const {
        int size(0);
        if (nodePointer) {
            size = nodePointer->sizeOfThisSubTree;
        }
        return size;
    }

    int calculateSizeOfThisSubTree(Node& node) const {
        return getSizeOfThisSubTree(node.left) + getSizeOfThisSubTree(node.right) + 1;
    }

    virtual void updateTreeNodeDetails(Node& node) const { node.sizeOfThisSubTree = calculateSizeOfThisSubTree(node); }

    virtual bool doesContainStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const {
        bool result(false);
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (key < currentKey) {
                result = doesContainStartingOnThisNode(nodePointer->left, key);
            } else if (key > currentKey) {
                result = doesContainStartingOnThisNode(nodePointer->right, key);
            } else {
                result = true;
            }
        }
        return result;
    }

    Node const* getMinimumNodeStartingOnThisNode(NodeUniquePointer const& nodePointer) const {
        Node const* result(nullptr);
        if (nodePointer) {
            if (nodePointer->left) {
                // find the left most node until null
                result = getMinimumNodeStartingOnThisNode(nodePointer->left);
            } else {
                result = nodePointer.get();
            }
        }
        return result;
    }

    Node const* getMaximumNodeStartingOnThisNode(NodeUniquePointer const& nodePointer) const {
        Node const* result(nullptr);
        if (nodePointer) {
            if (nodePointer->right) {
                // find the right most node until null
                result = getMaximumNodeStartingOnThisNode(nodePointer->right);
            } else {
                result = nodePointer.get();
            }
        }
        return result;
    }

    Node const* selectNodeWithIndexStartingOnThisNode(NodeUniquePointer const& nodePointer, int const index) const {
        Node const* result(nullptr);
        if (nodePointer) {
            int sizeOfThisSubTree = getSizeOfThisSubTree(nodePointer->left);
            if (sizeOfThisSubTree > index) {
                result = selectNodeWithIndexStartingOnThisNode(nodePointer->left, index);
            } else if (sizeOfThisSubTree < index) {
                result = selectNodeWithIndexStartingOnThisNode(nodePointer->right, index - sizeOfThisSubTree - 1);
            } else {
                result = nodePointer.get();
            }
        }
        return result;
    }

    virtual Node const* getNodeWithFloorStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const {
        Node const* result(nullptr);
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (key == currentKey) {
                result = nodePointer.get();
            } else if (key < currentKey) {
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
        return result;
    }

    virtual Node const* getNodeWithCeilingStartingOnThisNode(
        NodeUniquePointer const& nodePointer, Key const& key) const {
        Node const* result(nullptr);
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (key == currentKey) {
                result = nodePointer.get();
            } else if (key > currentKey) {
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
        return result;
    }

    virtual int getRankStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const {
        int result(0);
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (key < currentKey) {
                // recursively check rank on the right side
                result = getRankStartingOnThisNode(nodePointer->left, key);
            } else if (key > currentKey) {
                // get size of left, add one node for this node, and add the rank on the right side
                result =
                    1 + getSizeOfThisSubTree(nodePointer->left) + getRankStartingOnThisNode(nodePointer->right, key);
            } else {
                // if equal, just get size of the subtree
                result = getSizeOfThisSubTree(nodePointer->left);
            }
        }
        return result;
    }

    NodeUniquePointer& getMinimumNodePointerReferenceStartingOnThisNode(NodeUniquePointer& nodePointer) {
        // specialized function to be able to get the minimum and change(delete) it
        // used in deletion (hibbard approach)
        if (nodePointer) {
            if (nodePointer->left) {
                // find the left most node until null
                return getMinimumNodePointerReferenceStartingOnThisNode(nodePointer->left);
            } else {
                return nodePointer;
            }
        }
        return nodePointer;
    }

    virtual void deleteBasedOnKeyStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key) {
        // this is called hibbard deletion
        if (nodePointer) {
            if (key < nodePointer->key) {
                deleteBasedOnKeyStartingOnThisNode(nodePointer->left, key);
            } else if (key > nodePointer->key) {
                deleteBasedOnKeyStartingOnThisNode(nodePointer->right, key);
            } else {
                if (!(nodePointer->left)) {
                    nodePointer = std::move(nodePointer->right);
                } else if (!(nodePointer->right)) {
                    nodePointer = std::move(nodePointer->left);
                } else {
                    NodeUniquePointer& minimumOnTheRight(
                        getMinimumNodePointerReferenceStartingOnThisNode(nodePointer->right));
                    copyNodeContents(*nodePointer, *minimumOnTheRight);
                    deleteMinimumStartingOnThisNode(minimumOnTheRight);
                    // why are we using deletion of minimum on the right instead of deletion of maximum in the left?
                    // -> No real reason.
                }
            }
            if (nodePointer) {
                updateTreeNodeDetails(*nodePointer);
            }
        }
    }

    virtual void deleteMinimumStartingOnThisNode(NodeUniquePointer& nodePointer) {
        if (nodePointer) {
            if (nodePointer->left) {
                deleteMinimumStartingOnThisNode(nodePointer->left);
                updateTreeNodeDetails(*nodePointer);
            } else {
                // delete the left mode node and place the right child in its place (left child is not considered
                // because its the left most node)
                nodePointer = std::move(nodePointer->right);
            }
        }
    }

    virtual void deleteMaximumStartingOnThisNode(NodeUniquePointer& nodePointer) {
        if (nodePointer) {
            if (nodePointer->right) {
                deleteMaximumStartingOnThisNode(nodePointer->right);
                updateTreeNodeDetails(*nodePointer);
            } else {
                nodePointer = std::move(nodePointer->left);
            }
        }
    }

    void retrieveKeysStartingOnThisNode(Keys& keys, NodeUniquePointer const& nodePointer) const {
        // Similar with traverseByInOrder
        if (nodePointer) {
            retrieveKeysStartingOnThisNode(keys, nodePointer->left);
            keys.emplace_back(nodePointer->key);
            retrieveKeysStartingOnThisNode(keys, nodePointer->right);
        }
    }

    virtual void retrieveKeysInRangeInclusiveStartingOnThisNode(
        Keys& keys, NodeUniquePointer const& nodePointer, Key const& low, Key const& high) const {
        if (nodePointer) {
            if (low < nodePointer->key) {
                retrieveKeysInRangeInclusiveStartingOnThisNode(keys, nodePointer->left, low, high);
            }
            if (low <= nodePointer->key && high >= nodePointer->key) {
                keys.emplace_back(nodePointer->key);
            }
            if (high > nodePointer->key) {
                retrieveKeysInRangeInclusiveStartingOnThisNode(keys, nodePointer->right, low, high);
            }
        }
    }

    void traverseByPreOrder(NodeUniquePointer const& nodePointer, TraverseFunction const& traverseFunction) {
        if (nodePointer) {
            traverseFunction(*nodePointer);
            traverseByPreOrder(nodePointer->left, traverseFunction);
            traverseByPreOrder(nodePointer->right, traverseFunction);
        }
    }

    void traverseByInOrder(NodeUniquePointer const& nodePointer, TraverseFunction const& traverseFunction) {
        if (nodePointer) {
            traverseByInOrder(nodePointer->left, traverseFunction);
            traverseFunction(*nodePointer);
            traverseByInOrder(nodePointer->right, traverseFunction);
        }
    }

    void traverseByPostOrder(NodeUniquePointer const& nodePointer, TraverseFunction const& traverseFunction) {
        if (nodePointer) {
            traverseByPostOrder(nodePointer->left, traverseFunction);
            traverseByPostOrder(nodePointer->right, traverseFunction);
            traverseFunction(*nodePointer);
        }
    }

    NodeUniquePointer m_root;
};

}  // namespace algorithm

}  // namespace alba

// BST maintains symmetric order. It means that each node has a key and every node's key is:
// -> Larger than all keys in its left subtree
// -> Smaller than all keys in its right subtree

// Implementation details: subtree counts are stored in each node -> This facilitates efficient implementation of rank()
// and select().

// Tree shape depends on the order of insertion
// -> Best case: They are perfectly balanced.
// -> Worst case: Nodes are only placed on a single side (all are placed in left or all are placed in right).
// --->If the input came in sorted order this will happen.

// BST corresponds to quicksort partitioning
// There is a direct correspondence if the array has no duplicate keys.

// Proposition: if N distinct keys are inserted into a BST in random order, the expected number of compares for a
// search/insert is ~ 2*log2(N) Proof: 1-1 correspondence with quicksort partitioning. Worst case is ~4.311 ln N. This
// is proved by Bruce Reed in 2003.

// Alternating insertion and deletion (randomly) causes the tree to be asymmetric.
// Hibbard deletion approach of deleting the minimum to the right causes the tree to be asymmetric.
// Researchers discovered that after a long sequence of insertion and deletion the height becomes sqrt(N).
// If you randomly change the side of deletion, it does not work either. It still yields to sqrt(N).
// Long standing open problem: Simple and efficient delete for BSTs.
