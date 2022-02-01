#pragma once

#include <SymbolTable/BaseSymbolTable.hpp>

#include <memory>

namespace alba
{

template <typename Key, typename Value>
class BinarySearchTreeSymbolTable : public BaseSymbolTable<Key, Value>
{
public:
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node
    {
        Key key;
        Value value;
        NodeUniquePointer left;
        NodeUniquePointer right;
        unsigned int numberOfNodesOnThisSubTree;
    };

    BinarySearchTreeSymbolTable()
    {}

    bool isEmpty() const override
    {        return getSize() == 0;
    }

    unsigned int getSize() const override
    {
        return getSizeOnThisNode(m_root.get());
    }

    unsigned int getRank(Key const& key) const override
    {
        return getRankOnThisNode(m_root.get(), key);
    }

    Value get(Key const& key) const override
    {
        return getOnThisNode(m_root.get(), key);
    }

    Key getMinimum() const override
    {
        Key result{};
        Node const*const nodePointer(getMinimumNodeOnThisNode(m_root.get()));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getMaximum() const override
    {
        Key result{};
        Node const*const nodePointer(getMaximumNodeOnThisNode(m_root.get()));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key selectAt(unsigned int const index) const override
    {
        Key result{};
        Node const*const nodePointer(selectNodeWithIndexOnThisNode(m_root.get(), index));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getFloor(Key const& key) const override
    {
        Key result{};
        Node const*const nodePointer(getNodeWithFloorOnThisNode(m_root.get(), key));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getCeiling(Key const& key) const override
    {
        Key result{};
        Node const*const nodePointer(getNodeWithCeilingOnThisNode(m_root.get(), key));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    void put(Key const& key, Value const& value) override
    {
        putOnThisNode(m_root, key, value);
    }

    void deleteBasedOnKey(Key const& key) override
    {
        deleteBasedOnKeyOnThisNode(m_root, key);
    }

    void deleteMinimum() override
    {
        deleteMinimumOnThisNode(m_root);
    }

    void deleteMaximum() override
    {
        deleteMaximumOnThisNode(m_root);
    }

    template <typename Container>
    void retrieveKeysInRangeInclusive(Container & keys, Key const& low, Key const& high)
    {
        retrieveKeysInRangeInclusiveOnThisNode(keys, m_root.get(), low, high);
    }

private:

    unsigned int getSizeOnThisNode(Node const*const nodePointer) const
    {
        unsigned int size(0);
        if(nodePointer)
        {
            size = nodePointer->numberOfNodesOnThisSubTree;
        }
        return size;
    }

    unsigned int calculateSizeOfNodeBasedFromLeftAndRight(Node const& node) const
    {
        return getSizeOnThisNode(node.left.get()) + getSizeOnThisNode(node.right.get()) + 1;    }

    Value getOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        Value result{};
        if(nodePointer != nullptr)
        {
            Key const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                result = getOnThisNode(nodePointer->left.get(), key);
            }
            else if(key > currentKey)
            {
                result = getOnThisNode(nodePointer->right.get(), key);
            }
            else
            {
                result = nodePointer->value;
            }
        }
        return result;
    }

    Node const* getMinimumNodeOnThisNode(Node const*const nodePointer) const
    {
        Node const* result(nullptr);
        if(nodePointer != nullptr)
        {
            if(nodePointer->left)
            {
                result = getMinimumNodeOnThisNode(nodePointer->left.get());
            }
            else
            {
                result = nodePointer;
            }
        }
        return result;
    }

    Node const* getMaximumNodeOnThisNode(Node const*const nodePointer) const
    {
        Node const* result(nullptr);
        if(nodePointer != nullptr)
        {
            if(nodePointer->right)
            {
                result = getMaximumNodeOnThisNode(nodePointer->right.get());
            }
            else
            {
                result = nodePointer;
            }
        }
        return result;
    }

    Node const* getNodeWithFloorOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        Node const* result(nullptr);
        if(nodePointer != nullptr)
        {
            Key const& currentKey(nodePointer->key);
            if(key == currentKey)
            {
                result = nodePointer;
            }
            else if(key < currentKey)
            {
                result = getNodeWithFloorOnThisNode(nodePointer->left.get(), key);
            }
            else
            {
                Node const*const nodeWithFloorAtRight(getNodeWithFloorOnThisNode(nodePointer->right.get(), key));
                if(nodeWithFloorAtRight != nullptr)
                {
                    result = nodeWithFloorAtRight;
                }
                else
                {
                    result = nodePointer;
                }
            }
        }
        return result;
    }

    Node const* getNodeWithCeilingOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        Node const* result(nullptr);
        if(nodePointer != nullptr)
        {
            Key const& currentKey(nodePointer->key);
            if(key == currentKey)
            {
                result = nodePointer;
            }
            else if(key > currentKey)
            {
                result = getNodeWithCeilingOnThisNode(nodePointer->right.get(), key);
            }
            else
            {
                Node const*const nodeWithCeilingAtLeft(getNodeWithCeilingOnThisNode(nodePointer->left.get(), key));
                if(nodeWithCeilingAtLeft != nullptr)
                {
                    result = nodeWithCeilingAtLeft;
                }
                else
                {
                    result = nodePointer;
                }
            }
        }
        return result;
    }

    Node const* selectNodeWithIndexOnThisNode(Node const*const nodePointer, unsigned int const index) const
    {
        Node const* result(nullptr);
        if(nodePointer != nullptr)
        {
            unsigned int numberOfNodesOnThisSubTree = getSizeOnThisNode(nodePointer->left.get());
            if(numberOfNodesOnThisSubTree > index)
            {
                result = selectNodeWithIndexOnThisNode(nodePointer->left.get(), index);
            }
            else if(numberOfNodesOnThisSubTree < index)
            {
                result = selectNodeWithIndexOnThisNode(nodePointer->right.get(), index-numberOfNodesOnThisSubTree-1);
            }
            else
            {
                result = nodePointer;
            }
        }
        return result;    }

    unsigned int getRankOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        unsigned int result(0);
        if(nodePointer != nullptr)
        {
            Key const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                result = getRankOnThisNode(nodePointer->left.get(), key);
            }
            else if(key > currentKey)
            {
                result = 1 + getSizeOnThisNode(nodePointer->left.get()) + getRankOnThisNode(nodePointer->right.get(), key);
            }
            else
            {
                result = getSizeOnThisNode(nodePointer->left.get());
            }
        }
        return result;
    }

    void putOnThisNode(NodeUniquePointer & nodePointer, Key const& key, Value const& value)
    {
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                putOnThisNode(nodePointer->left, key, value);
                nodePointer->numberOfNodesOnThisSubTree = calculateSizeOfNodeBasedFromLeftAndRight(*(nodePointer.get()));
            }
            else if(key > currentKey)
            {
                putOnThisNode(nodePointer->right, key, value);
                nodePointer->numberOfNodesOnThisSubTree = calculateSizeOfNodeBasedFromLeftAndRight(*(nodePointer.get()));
            }
            else
            {
                nodePointer->value = value;
            }
        }
        else        {
            nodePointer.reset(new Node{key, value, nullptr, nullptr, 1U});
        }
    }

    void deleteBasedOnKeyOnThisNode(NodeUniquePointer & nodePointer, Key const& key)
    {
        if(nodePointer)
        {
            if(key < nodePointer->key)
            {
                deleteBasedOnKeyOnThisNode(nodePointer->left, key);
            }
            else if(key > nodePointer->key)
            {
                deleteBasedOnKeyOnThisNode(nodePointer->right, key);
            }
            else
            {
                Node const*const minimumNodePointer(getMinimumNodeOnThisNode(nodePointer->right.get()));
                if(minimumNodePointer==nullptr)
                {
                    nodePointer = nullptr;
                }
                else
                {
                    nodePointer->key = minimumNodePointer->key;
                    nodePointer->value = minimumNodePointer->value;
                    deleteMinimumOnThisNode(nodePointer->right);
                }
            }
            if(nodePointer)
            {
                nodePointer->numberOfNodesOnThisSubTree = calculateSizeOfNodeBasedFromLeftAndRight(*(nodePointer.get()));
            }
        }
    }

    void deleteMinimumOnThisNode(NodeUniquePointer & nodePointer)
    {
        if(nodePointer)        {
            if(nodePointer->left)
            {
                deleteMinimumOnThisNode(nodePointer->left);
                nodePointer->numberOfNodesOnThisSubTree = calculateSizeOfNodeBasedFromLeftAndRight(*(nodePointer.get()));
            }
            else
            {
                nodePointer = std::move(nodePointer->right);
            }
        }
    }
    void deleteMaximumOnThisNode(NodeUniquePointer & nodePointer)
    {
        if(nodePointer)
        {
            if(nodePointer->right)
            {
                deleteMaximumOnThisNode(nodePointer->right);
                nodePointer->numberOfNodesOnThisSubTree = calculateSizeOfNodeBasedFromLeftAndRight(*(nodePointer.get()));
            }
            else
            {
                nodePointer = std::move(nodePointer->left);
            }
        }
    }
    template <typename Container>
    void retrieveKeysInRangeInclusiveOnThisNode(Container & keys, Node const*const nodePointer, Key const& low, Key const& high)
    {
        if(nodePointer)
        {
            if(low < nodePointer->key)
            {
                retrieveKeysInRangeInclusiveOnThisNode(keys, nodePointer->left.get(), low, high);
            }
            if(low <= nodePointer->key && high >= nodePointer->key)
            {
                keys.emplace_back(nodePointer->key);
            }
            if(high > nodePointer->key)
            {
                retrieveKeysInRangeInclusiveOnThisNode(keys, nodePointer->right.get(), low, high);
            }
        }
    }
    NodeUniquePointer m_root;
};

}
