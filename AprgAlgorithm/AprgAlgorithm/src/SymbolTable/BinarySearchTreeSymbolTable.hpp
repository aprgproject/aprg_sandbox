#pragma once

#include <SymbolTable/BaseSymbolTable.hpp>

#include <memory>

namespace alba
{

template <typename Key, typename Value>
class BinarySearchTreeSymbolTable : public BaseSymbolTable<Key, Value>
{
public:
    struct Node;    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node
    {
        Key key;
        Value value;
        NodeUniquePointer left;
        NodeUniquePointer right;
        unsigned int numberOfSubNodes;    };

    BinarySearchTreeSymbolTable()
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
        return getRankOnThisNode(m_root.get(), key);
    }

    Value get(Key const& key) const override
    {
        return getOnThisNode(m_root.get(), key);
    }

    Key getMinimum() const override
    {
        return getMinimumOnThisNode(m_root.get());
    }

    Key getMaximum() const override
    {
        return getMaximumOnThisNode(m_root.get());
    }

    Key selectAt(unsigned int const index) const override
    {
        Key result{};
        Node const*const nodePointer(selectNodeWithIndexOnThisNode(m_root.get(), index));        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getFloor(Key const& key) const override
    {
        Key result{};
        Node const*const nodePointer(getNodeWithFloorOnThisNode(m_root.get(), key));        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getCeiling(Key const& key) const override
    {
        Key result{};
        Node const*const nodePointer(getNodeWithCeilingOnThisNode(m_root.get(), key));        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    void putOnThisNode(Key const& key, Value const& value) override
    {
        putOnThisNode(m_root, key, value);
    }

    void deleteBasedOnKey(Key const& key) override
    {
    }
private:

    unsigned int getSizeOnThisNode(Node const*const nodePointer) const
    {
        unsigned int size(0);
        if(nodePointer)
        {
            size = nodePointer->numberOfSubNodes;
        }
        return size;
    }

    Value getOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        Value result{};
        if(nodePointer != nullptr)
        {
            Value const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                result = getOnThisNode(nodePointer->left.get(), key);            }
            else if(key > currentKey)
            {
                result = getOnThisNode(nodePointer->right.get(), key);
            }
            else
            {
                result = nodePointer->value;
            }
        }
        return result;    }

    Key getMinimumOnThisNode(Node const*const nodePointer) const
    {
        Key result{};
        if(nodePointer != nullptr)
        {
            if(nodePointer->left)
            {
                result = getMinimumOnThisNode(nodePointer->left.get());
            }
            else
            {
                result = nodePointer->key;
            }
        }
        return result;
    }

    Key getMaximumOnThisNode(Node const*const nodePointer) const
    {
        Key result{};
        if(nodePointer != nullptr)
        {
            if(nodePointer->right)
            {
                result = getMaximumOnThisNode(nodePointer->right.get());
            }
            else
            {
                result = nodePointer->key;
            }
        }
        return result;
    }

    Node const*const getNodeWithFloorOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        Node const* result(nullptr);
        if(nodePointer != nullptr)
        {
            Value const& currentKey(nodePointer->key);
            if(key == currentKey)
            {
                result = nodePointer->key;            }
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

    Node const*const getNodeWithCeilingOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        Node const* result(nullptr);
        if(nodePointer != nullptr)
        {
            Value const& currentKey(nodePointer->key);
            if(key == currentKey)
            {
                result = nodePointer->key;            }
            else if(key > currentKey)
            {
                result = getNodeWithFloorOnThisNode(nodePointer->right.get(), key);
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

    Node const*const selectNodeWithIndexOnThisNode(Node const*const nodePointer, unsigned int const index) const
    {
        Node const* result(nullptr);
        if(nodePointer != nullptr)
        {
            unsigned int numberOfSubNodes = getSizeOnThisNode(nodePointer);
            if(numberOfSubNodes > index)
            {
                result = selectNodeWithIndexOnThisNode(nodePointer->left.get(), index);
            }
            else if(numberOfSubNodes < index)
            {
                result = selectNodeWithIndexOnThisNode(nodePointer->right.get(), index-numberOfSubNodes-1);
            }
            else
            {
                result = nodePointer;
            }
        }
        return result;
    }

    unsigned int getRankOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        unsigned int result(0);
        if(nodePointer != nullptr)
        {
            Value const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                result = getRankOnThisNode(nodePointer->left.get(), key);            }
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

    void putOnThisNode(NodeUniquePointer & nodePointer, Key const& key, Value const& value) const
    {
        if(nodePointer)
        {
            Value const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                putOnThisNode(nodePointer->left, key, value);
            }
            else if(key > currentKey)
            {
                putOnThisNode(nodePointer->right, key, value);
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
    NodeUniquePointer m_root;};

}
