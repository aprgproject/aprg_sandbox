#pragma once

#include <memory>

namespace alba
{

template <typename Key, typename Object>
class BinarySearchTreeSymbolTable
{
public:
    struct Node;
    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node
    {
        Key key;
        Object object;
        NodeUniquePointer left;
        NodeUniquePointer right;
        unsigned int numberOfSubNodes;
    };

    BinarySearchTreeSymbolTable()
    {}

    bool isEmpty() const
    {
        return getSize() == 0;
    }

    unsigned int getSize() const
    {
        return getSizeOnThisNode(m_root);
    }

    Object get(Key const& key) const
    {
        return getOnThisNode(m_root.get(), key);
    }

    unsigned int getRank(Key const& key) const
    {
        return getRankOnThisNode(m_root.get(), key);
    }

    Key getMinimum() const
    {
        return getMinimumOnThisNode(m_root.get());
    }

    Key getMaximum() const
    {
        return getMaximumOnThisNode(m_root.get());
    }

    Key selectAt(unsigned int const index) const
    {
        Key result{};
        Node const*const nodePointer(selectNodeWithIndexOnThisNode(m_root.get(), index));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getFloor(Key const& key) const
    {
        Key result{};
        Node const*const nodePointer(getNodeWithFloorOnThisNode(m_root.get(), key));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    Key getCeiling(Key const& key) const
    {
        Key result{};
        Node const*const nodePointer(getNodeWithCeilingOnThisNode(m_root.get(), key));
        if(nodePointer != nullptr)
        {
            result = nodePointer->key;
        }
        return result;
    }

    void putOnThisNode(Key const& key, Object const& object)
    {
        putOnThisNode(m_root, key, object);
    }

    void deleteBasedOnKey(Key const& key)
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

    Object getOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        Object result{};
        if(nodePointer != nullptr)
        {
            Object const& currentKey(nodePointer->key);
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
                result = nodePointer->object;
            }
        }
        return result;
    }

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
            Object const& currentKey(nodePointer->key);
            if(key == currentKey)
            {
                result = nodePointer->key;
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

    Node const*const getNodeWithCeilingOnThisNode(Node const*const nodePointer, Key const& key) const
    {
        Node const* result(nullptr);
        if(nodePointer != nullptr)
        {
            Object const& currentKey(nodePointer->key);
            if(key == currentKey)
            {
                result = nodePointer->key;
            }
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
            Object const& currentKey(nodePointer->key);
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

    void putOnThisNode(NodeUniquePointer & nodePointer, Key const& key, Object const& object) const
    {
        if(nodePointer)
        {
            Object const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                putOnThisNode(nodePointer->left, key, object);
            }
            else if(key > currentKey)
            {
                putOnThisNode(nodePointer->right, key, object);
            }
            else
            {
                nodePointer->object = object;
            }
        }
        else
        {
            nodePointer.reset(new Node{key, object, nullptr, nullptr, 1U});
        }
    }
    NodeUniquePointer m_root;
};

}
