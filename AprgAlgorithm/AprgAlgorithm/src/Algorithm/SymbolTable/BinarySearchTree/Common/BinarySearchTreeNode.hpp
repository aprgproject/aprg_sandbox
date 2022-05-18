#pragma once

#include <memory>

namespace alba
{

namespace algorithm
{

namespace BinarySearchTreeNode
{

enum class Color
{
    Red,
    Black
};

template <typename Key, typename Value>
struct BasicTreeNode
{
    Key key;
    Value value;
    std::unique_ptr<BasicTreeNode> left;
    std::unique_ptr<BasicTreeNode> right;
    unsigned int numberOfNodesOnThisSubTree;
};

template <typename Key, typename Value>
struct RedBlackTreeNode
{
    Key key;
    Value value;
    std::unique_ptr<RedBlackTreeNode> left;
    std::unique_ptr<RedBlackTreeNode> right;
    unsigned int numberOfNodesOnThisSubTree;
    Color parentLinkColor;
};

template <typename Key, typename Value, typename KeyDataTypeValue>
struct IntervalSearchTreeNode
{
    Key key;
    Value value;
    std::unique_ptr<IntervalSearchTreeNode> left;
    std::unique_ptr<IntervalSearchTreeNode> right;
    unsigned int numberOfNodesOnThisSubTree;
    Color parentLinkColor;
    KeyDataTypeValue maxValueInSubtree;
};

}

}

}
