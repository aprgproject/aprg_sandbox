#pragma once

#include <SymbolTable/BaseSymbolTable.hpp>

#include <memory>
#include <vector>

namespace alba
{

template <typename Key, typename Value, typename Node>
class BaseBinarySearchTreeSymbolTable : public BaseSymbolTable<Key, Value>
{
public:
    using NodeUniquePointer = std::unique_ptr<Node>;
    using Keys = std::vector<Key>;

    BaseBinarySearchTreeSymbolTable()
    {}

    bool isEmpty() const override
    {
        return getSize() == 0;
    }

    unsigned int getSize() const override
    {
        return getSizeOnThisNode(m_root);
    }

    unsigned int getRank(Key const& key) const override
    {
        return getRankStartingOnThisNode(m_root, key);
    }

    Value get(Key const& key) const override
    {
        return getStartingOnThisNode(m_root, key);
    }

    Key getMinimum() const override
    {
        Key result{};
        Node const*const nodePointer(getMinimumNodeStartingOnThisNode(m_root));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getMaximum() const override
    {
        Key result{};
        Node const*const nodePointer(getMaximumNodeStartingOnThisNode(m_root));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key selectAt(unsigned int const index) const override
    {
        Key result{};
        Node const*const nodePointer(selectNodeWithIndexStartingOnThisNode(m_root, index));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getFloor(Key const& key) const override
    {
        Key result{};
        Node const*const nodePointer(getNodeWithFloorStartingOnThisNode(m_root, key));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getCeiling(Key const& key) const override
    {
        Key result{};
        Node const*const nodePointer(getNodeWithCeilingStartingOnThisNode(m_root, key));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    void deleteBasedOnKey(Key const& key) override
    {
        deleteBasedOnKeyStartingOnThisNode(m_root, key);
    }

    void deleteMinimum() override
    {
        deleteMinimumStartingOnThisNode(m_root);
    }

    void deleteMaximum() override
    {
        deleteMaximumStartingOnThisNode(m_root);
    }

    Keys getKeys() const override
    {
        Keys result;
        retrieveKeysStartingOnThisNode(result, m_root);
        return result;
    }

    Keys getKeysInRangeInclusive(Key const& low, Key const& high) const override
    {
        Keys result;
        retrieveKeysInRangeInclusiveStartingOnThisNode(result, m_root, low, high);
        return result;
    }

protected:

    unsigned int getSizeOnThisNode(NodeUniquePointer const& nodePointer) const
    {
        unsigned int size(0);
        if(nodePointer)
        {
            size = nodePointer->numberOfNodesOnThisSubTree;
        }
        return size;
    }

    unsigned int calculateSizeOfNodeBasedFromLeftAndRight(NodeUniquePointer const& nodePointer) const
    {
        return getSizeOnThisNode(nodePointer->left) + getSizeOnThisNode(nodePointer->right) + 1;
    }

    Value getStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
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

    Node const* getMinimumNodeStartingOnThisNode(NodeUniquePointer const& nodePointer) const
    {
        Node const* result(nullptr);
        if(nodePointer)
        {
            if(nodePointer->left)
            {
                result = getMinimumNodeStartingOnThisNode(nodePointer->left);
            }
            else
            {
                result = nodePointer.get();
            }
        }
        return result;
    }

    Node const* getMaximumNodeStartingOnThisNode(NodeUniquePointer const& nodePointer) const
    {
        Node const* result(nullptr);
        if(nodePointer)
        {
            if(nodePointer->right)
            {
                result = getMaximumNodeStartingOnThisNode(nodePointer->right);
            }
            else
            {
                result = nodePointer.get();
            }
        }
        return result;
    }

    Node const* selectNodeWithIndexStartingOnThisNode(NodeUniquePointer const& nodePointer, unsigned int const index) const
    {
        Node const* result(nullptr);
        if(nodePointer)
        {
            unsigned int numberOfNodesOnThisSubTree = getSizeOnThisNode(nodePointer->left);
            if(numberOfNodesOnThisSubTree > index)
            {
                result = selectNodeWithIndexStartingOnThisNode(nodePointer->left, index);
            }
            else if(numberOfNodesOnThisSubTree < index)
            {
                result = selectNodeWithIndexStartingOnThisNode(nodePointer->right, index-numberOfNodesOnThisSubTree-1);
            }
            else
            {
                result = nodePointer.get();
            }
        }
        return result;
    }

    Node const* getNodeWithFloorStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
    {
        Node const* result(nullptr);
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(key == currentKey)
            {
                result = nodePointer.get();
            }
            else if(key < currentKey)
            {
                result = getNodeWithFloorStartingOnThisNode(nodePointer->left, key);
            }
            else
            {
                Node const*const nodeWithFloorAtRight(getNodeWithFloorStartingOnThisNode(nodePointer->right, key));
                if(nodeWithFloorAtRight != nullptr)
                {
                    result = nodeWithFloorAtRight;
                }
                else
                {
                    result = nodePointer.get();
                }
            }
        }
        return result;
    }

    Node const* getNodeWithCeilingStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
    {
        Node const* result(nullptr);
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(key == currentKey)
            {
                result = nodePointer.get();
            }
            else if(key > currentKey)
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
        return result;
    }

    unsigned int getRankStartingOnThisNode(NodeUniquePointer const& nodePointer, Key const& key) const
    {
        unsigned int result(0);
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                result = getRankStartingOnThisNode(nodePointer->left, key);
            }
            else if(key > currentKey)
            {
                result = 1 + getSizeOnThisNode(nodePointer->left) + getRankStartingOnThisNode(nodePointer->right, key);
            }
            else
            {
                result = getSizeOnThisNode(nodePointer->left);
            }
        }
        return result;
    }

    void putStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key, Value const& value)
    {
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                putStartingOnThisNode(nodePointer->left, key, value);
                nodePointer->numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
            else if(key > currentKey)
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
    }

    void deleteBasedOnKeyStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key)
    {
        if(nodePointer)
        {
            if(key < nodePointer->key)
            {
                deleteBasedOnKeyStartingOnThisNode(nodePointer->left, key);
            }
            else if(key > nodePointer->key)
            {
                deleteBasedOnKeyStartingOnThisNode(nodePointer->right, key);
            }
            else
            {
                Node const*const minimumNodePointer(getMinimumNodeStartingOnThisNode(nodePointer->right));
                if(minimumNodePointer==nullptr)
                {
                    nodePointer.reset(nullptr);
                }
                else
                {
                    nodePointer->key = minimumNodePointer->key;
                    nodePointer->value = minimumNodePointer->value;
                    deleteMinimumStartingOnThisNode(nodePointer->right);
                }
            }
            if(nodePointer)
            {
                nodePointer->numberOfNodesOnThisSubTree = calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
        }
    }

    void deleteMinimumStartingOnThisNode(NodeUniquePointer & nodePointer)
    {
        if(nodePointer)
        {
            if(nodePointer->left)
            {
                deleteMinimumStartingOnThisNode(nodePointer->left);
                nodePointer->numberOfNodesOnThisSubTree = calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
            else
            {
                nodePointer = std::move(nodePointer->right);
            }
        }
    }

    void deleteMaximumStartingOnThisNode(NodeUniquePointer & nodePointer)
    {
        if(nodePointer)
        {
            if(nodePointer->right)
            {
                deleteMaximumStartingOnThisNode(nodePointer->right);
                nodePointer->numberOfNodesOnThisSubTree = calculateSizeOfNodeBasedFromLeftAndRight(nodePointer);
            }
            else
            {
                nodePointer = std::move(nodePointer->left);
            }
        }
    }

    void retrieveKeysStartingOnThisNode(Keys & keys, NodeUniquePointer const& nodePointer) const
    {
        if(nodePointer)
        {
            retrieveKeysStartingOnThisNode(keys, nodePointer->left);
            keys.emplace_back(nodePointer->key);
            retrieveKeysStartingOnThisNode(keys, nodePointer->right);
        }
    }

    void retrieveKeysInRangeInclusiveStartingOnThisNode(Keys & keys, NodeUniquePointer const& nodePointer, Key const& low, Key const& high) const
    {
        if(nodePointer)
        {
            if(low < nodePointer->key)
            {
                retrieveKeysInRangeInclusiveStartingOnThisNode(keys, nodePointer->left, low, high);
            }
            if(low <= nodePointer->key && high >= nodePointer->key)
            {
                keys.emplace_back(nodePointer->key);
            }
            if(high > nodePointer->key)
            {
                retrieveKeysInRangeInclusiveStartingOnThisNode(keys, nodePointer->right, low, high);
            }
        }
    }

    NodeUniquePointer m_root;
};

}
