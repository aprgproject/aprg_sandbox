#pragma once

#include <SymbolTable/BaseSymbolTable.hpp>

#include <functional>
#include <memory>

namespace alba
{

template <typename Key, typename Value>
class LinkedListSymbolTable : public BaseSymbolTable<Key, Value>
{
public:
    struct Node;    using NodeUniquePointer = std::unique_ptr<Node>;
    struct Node
    {
        Key key;
        Value value;
        NodeUniquePointer next;
    };
    LinkedListSymbolTable()
        : m_currentSize(0)
        , m_first(nullptr)
    {}

    bool isEmpty() const override
    {
        return m_currentSize == 0;
    }

    unsigned int getSize() const override
    {
        return m_currentSize;
    }

    unsigned int getRank(Key const& key) const override
    {
        unsigned int result(0);
        traverseWithNoChange([&](Node const& node, bool &)
        {
            if(key > node.key)
            {
                result++;
            }
        });
        return result;
    }

    Value get(Key const& key) const override
    {
        Value result{};
        traverseWithNoChange([&](Node const& node, bool & shouldBreak)
        {
            if(key == node.key)
            {
                result = node.value;
                shouldBreak = true;
            }
        });
        return result;
    }

    Key getMinimum() const override
    {
        Key result{};
        bool isFirst(true);
        traverseWithNoChange([&](Node const& node, bool &)
        {
            if(isFirst)
            {
                result = node.key;
                isFirst = false;
            }
            else
            {
                result = std::min(result, node.key);
            }
        });
        return result;
    }

    Key getMaximum() const override
    {
        Key result{};
        bool isFirst(true);
        traverseWithNoChange([&](Node const& node, bool &)
        {
            if(isFirst)
            {
                result = node.key;
                isFirst = false;
            }
            else
            {
                result = std::max(result, node.key);
            }
        });
        return result;
    }

    Key selectAt(unsigned int const rank) const override
    {
        Key result{};
        traverseWithNoChange([&](Node const& node, bool & shouldBreak)
        {
            unsigned int const rankAtTraversal(getRank(node.key));
            if(rank == rankAtTraversal)
            {
                result = node.key;
                shouldBreak = true;
            }
        });
        return result;
    }

    Key getFloor(Key const& key) const override
    {
        Key floor{};
        bool isFirst(true);
        traverseWithNoChange([&](Node const& node, bool & shouldBreak)
        {
            if(key == node.key)
            {
                floor = node.key;
                shouldBreak = true;
            }
            else if(isFirst && key > node.key)
            {
                floor = node.key;
                isFirst = false;
            }
            else if(!isFirst && key > node.key && key-node.key < key-floor) // less than key and nearer than key
            {
                floor = node.key;
            }
        });
        return floor;
    }

    Key getCeiling(Key const& key) const override
    {
        Key ceiling{};
        bool isFirst(true);
        traverseWithNoChange([&](Node const& node, bool & shouldBreak)
        {
            if(key == node.key)
            {
                ceiling = node.key;
                shouldBreak = true;
            }
            else if(isFirst && key < node.key)
            {
                ceiling = node.key;
                isFirst = false;
            }
            else if(!isFirst && key < node.key && node.key-key < ceiling-key) // greater than key and nearer than key
            {
                ceiling = node.key;
            }
        });
        return ceiling;
    }

    void put(Key const& key, Value const& value) override
    {
        bool isKeyFound(false);
        traverseWithChange([&](Node & node, bool & shouldBreak)
        {
            if(key == node.key)
            {
                node.value = value;
                isKeyFound = true;
                shouldBreak = true;
            }
        });
        if(!isKeyFound)
        {
            NodeUniquePointer newNext(std::move(m_first));
            m_first.reset(new Node{key, value, std::move(newNext)});
            m_currentSize++;
        }
    }

    void deleteBasedOnKey(Key const& key) override
    {
        Node* previousNodePointer(nullptr);
        for(Node* currentNodePointer=m_first.get(); currentNodePointer!=nullptr; currentNodePointer=currentNodePointer->next.get())
        {
            if(currentNodePointer != nullptr)
            {
                if(key == currentNodePointer->key)
                {
                    previousNodePointer->next = std::move(currentNodePointer->next);
                    break;
                }
            }
            previousNodePointer = currentNodePointer;
        }
    }

    void deleteMinimum() override
    {
        deleteBasedOnKey(getMinimum());
    }

    void deleteMaximum() override
    {
        deleteBasedOnKey(getMaximum());
    }

private:

    using TraverseFunctionWithNoChange=std::function<void(Node const&, bool &)>;
    using TraverseFunctionWithChange=std::function<void(Node &, bool &)>;

    void traverseWithNoChange(TraverseFunctionWithNoChange const& traverseFunction) const
    {
        for(Node const* currentNodePointer=m_first.get(); currentNodePointer!=nullptr; currentNodePointer=currentNodePointer->next.get())
        {
            bool shouldBreak(false);
            traverseFunction(*currentNodePointer, shouldBreak);
            if(shouldBreak)
            {
                break;
            }
        }
    }

    void traverseWithChange(TraverseFunctionWithChange const& traverseFunction)
    {
        for(Node* currentNodePointer=m_first.get(); currentNodePointer!=nullptr; currentNodePointer=currentNodePointer->next.get())
        {
            bool shouldBreak(false);
            traverseFunction(*currentNodePointer, shouldBreak);
            if(shouldBreak)
            {
                break;
            }
        }
    }

    unsigned int m_currentSize;
    NodeUniquePointer m_first;
};
}
