#pragma once

namespace alba {

namespace algorithm {

template <typename BaseTree>
class BaseSetWithBaseTree : public BaseTree {
public:
    using Key = typename BaseTree::Key;
    using Node = typename BaseTree::Node;
    using NodeUniquePointer = typename BaseTree::NodeUniquePointer;
    using TraverseFunction = typename BaseTree::TraverseFunction;

    BaseSetWithBaseTree() : b_root(BaseTree::m_root) {}

    virtual ~BaseSetWithBaseTree() = default;  // virtual destructor because of virtual functions (vtable exists)

    // overrides in BaseSet
    void put(Key const& key) override { putStartingOnThisNode(b_root, key); }

protected:
    // overrides in BaseTree
    void copyNodeContents(Node& destinationNode, Node const& sourceNode) const override {
        destinationNode.key = sourceNode.key;
    }

    virtual void putStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key) = 0;

private:
    NodeUniquePointer& b_root;
};

}  // namespace algorithm

}  // namespace alba
