#pragma once

#include <Algorithm/SymbolTable/BinarySearchTree/Common/BaseRedBlackBinarySearchTreeSymbolTable.hpp>
#include <Algorithm/SymbolTable/BinarySearchTree/Common/BinarySearchTreeNode.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <vector>

namespace alba
{

namespace algorithm
{

template <typename IntervalUnit>
class Interval
{
public:
    IntervalUnit start;
    IntervalUnit end;
    bool operator<(Interval const& interval) const
    {
        return start < interval.start;
    }
    bool operator>(Interval const& interval) const
    {
        return start > interval.start;
    }
    bool operator==(Interval const& interval) const
    {
        return start == interval.start;
    }
    bool operator<=(Interval const& interval) const
    {
        return start <= interval.start;
    }
    bool operator>=(Interval const& interval) const
    {
        return start >= interval.start;
    }
};

template <typename IntervalUnit, typename Value>
class IntervalSearchTree
        : public BaseRedBlackBinarySearchTreeSymbolTable<Interval<IntervalUnit>, Value, BinarySearchTreeNode::IntervalSearchTreeNode<Interval<IntervalUnit>, Value, IntervalUnit>>
{
public:
    using Key = Interval<IntervalUnit>;
    using Keys = std::vector<Key>;
    using BaseClass = BaseRedBlackBinarySearchTreeSymbolTable<Key, Value, BinarySearchTreeNode::IntervalSearchTreeNode<Key, Value, IntervalUnit>>;
    using Node = BinarySearchTreeNode::IntervalSearchTreeNode<Key, Value, IntervalUnit>;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;

    Keys getIntersectingIntervalsOf(Key const& intervalToCheck) const
    {
        Keys keys;
        searchForIntersectingIntervals(keys, this->m_root, intervalToCheck);
        return keys;
    }

protected:

    bool areIntersectingIntervals(Key const& interval1, Key const& interval2) const
    {
        auto delta1(mathHelper::getPositiveDelta(interval1.start, interval1.end));
        auto delta2(mathHelper::getPositiveDelta(interval2.start, interval2.end));
        auto sumOfDeltas(delta1+delta2);
        auto maxDeltaEndpoints(std::max(mathHelper::getPositiveDelta(interval1.start, interval2.end), mathHelper::getPositiveDelta(interval2.start, interval1.end)));
        return maxDeltaEndpoints <= sumOfDeltas;
    }

    void searchForIntersectingIntervals(Keys & intersectingIntervals, NodeUniquePointer const& nodePointer, Key const& intervalToCheck) const
    {
        if(nodePointer)
        {
            if(areIntersectingIntervals(nodePointer->key, intervalToCheck)) // if interval in node intersect query interval
            {
                intersectingIntervals.emplace_back(nodePointer->key);
            }
            if(!nodePointer->left) // if left subtree is null, go right
            {
                searchForIntersectingIntervals(intersectingIntervals, nodePointer->right, intervalToCheck);
            }
            else if(nodePointer->left->maxValueInSubtree < intervalToCheck.start) // if max endpoint in left subtree is less than low, go right
            {
                searchForIntersectingIntervals(intersectingIntervals, nodePointer->right, intervalToCheck);
            }
            else // else go left
            {
                searchForIntersectingIntervals(intersectingIntervals, nodePointer->left, intervalToCheck);
                searchForIntersectingIntervals(intersectingIntervals, nodePointer->right, intervalToCheck);
            }
        }
    }

    IntervalUnit getMaxValueBasedFromLeftAndRight(Node & node) const
    {
        IntervalUnit maxValue(node.key.end);
        if(node.left)
        {
            maxValue = std::max(maxValue, node.left->key.end);
        }
        if(node.right)
        {
            maxValue = std::max(maxValue, node.right->key.end);
        }
        return maxValue;
    }

    void updateNodeDetails(Node & node) const override
    {
        node.numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(node);
        node.maxValueInSubtree = getMaxValueBasedFromLeftAndRight(node);
    }

    void putStartingOnThisNode(NodeUniquePointer & nodePointer, Key const& key, Value const& value) override
    {
        if(nodePointer)
        {
            Key const& currentKey(nodePointer->key);
            if(key < currentKey)
            {
                putStartingOnThisNode(nodePointer->left, key, value);
                this->updateNodeDetails(*nodePointer);
            }
            else if(key > currentKey)
            {
                putStartingOnThisNode(nodePointer->right, key, value);
                this->updateNodeDetails(*nodePointer);
            }
            else
            {
                nodePointer->value = value;
            }
            if(this->hasARightLeaningRedLinkOnOneChild(nodePointer))
            {
                this->rotateLeft(nodePointer);
            }
            if(this->hasTwoLeftLeaningRedLinksInARow(nodePointer))
            {
                this->rotateRight(nodePointer);
            }
            if(this->hasTwoRedLinksOnItsChildren(nodePointer))
            {
                this->setParentAsRedAndChildrenAsBlack(nodePointer);
            }
        }
        else
        {
            nodePointer.reset(new Node{key, value, nullptr, nullptr, 1U, BinarySearchTreeNode::Color::Red, key.end});
        }
    }
};

}

}
