#pragma once

namespace alba
{

namespace algorithm
{

template <typename BaseTree>
class BaseSetWithBaseTree : public BaseTree
{
public:
    using Key = typename BaseTree::Key;
    using Node = typename BaseTree::Node;
    using NodeUniquePointer = typename BaseTree::NodeUniquePointer;
    using TraverseFunction = typename BaseTree::TraverseFunction;

    BaseSetWithBaseTree() = default;
    virtual ~BaseSetWithBaseTree() = default;

    void put(Key const& key) override // overrides in BaseSet
    {
        putStartingOnThisNode(this->m_root, key);
    }

protected:

    void copyContents(Node & destinationNode, Node const& sourceNode) const override // overrides in BaseTree
    {
        destinationNode.key = sourceNode.key;
    }

    virtual void putStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key) = 0;
};

}

}
