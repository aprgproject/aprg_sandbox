#pragma once

namespace alba
{

namespace algorithm
{

template <typename Value, typename BaseTree>
class BaseSymbolTableWithBaseTree : public BaseTree
{
public:
    using Key = typename BaseTree::Key;
    using Node = typename BaseTree::Node;
    using NodeUniquePointer = typename BaseTree::NodeUniquePointer;
    using Keys = typename BaseTree::Keys;
    using TraverseFunction = typename BaseTree::TraverseFunction;

    BaseSymbolTableWithBaseTree()
        : b_root(BaseTree::m_root)
    {}

    virtual ~BaseSymbolTableWithBaseTree() = default;

    Value get(Key const& key) const override // overrides in BaseSymbolTable
    {
        return getStartingOnThisNode(b_root, key);
    }

    void put(Key const& key, Value const& value) override // overrides in BaseSymbolTable
    {
        putStartingOnThisNode(b_root, key, value);
    }

protected:

    void copyContents(Node & destinationNode, Node const& sourceNode) const override
    {
        destinationNode.key = sourceNode.key;
        destinationNode.value = sourceNode.value;
    }

    virtual Value getStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
    {
        Value result{};
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                result = getStartingOnThisNode(nodePointer->left, key);
            }
            else if(key > currentKey)
            {
                result = getStartingOnThisNode(nodePointer->right, key);
            }
            else
            {
                result = nodePointer->value;
            }
        }
        return result;
    }

    virtual void putStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key, Value const& value) = 0;

private:
    NodeUniquePointer & b_root;
};

}

}
