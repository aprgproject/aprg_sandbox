#pragma once

#include <memory>

namespace alba {

namespace algorithm {

enum class RedBlackColor { Red, Black };

template <typename Key>
struct BasicTreeNode {
    Key key;
    std::unique_ptr<BasicTreeNode> left;
    std::unique_ptr<BasicTreeNode> right;
    int sizeOfThisSubTree;
};

template <typename Key>
struct AvlTreeNode {
    Key key;
    std::unique_ptr<AvlTreeNode> left;
    std::unique_ptr<AvlTreeNode> right;
    int sizeOfThisSubTree;
    int heightOfThisSubTree;
};

template <typename Key>
struct RedBlackTreeNode {
    Key key;
    std::unique_ptr<RedBlackTreeNode> left;
    std::unique_ptr<RedBlackTreeNode> right;
    int sizeOfThisSubTree;
    RedBlackColor parentLinkColor;
};

template <typename Key, typename KeyDataTypeValue>
struct IntervalSearchTreeNode {
    Key key;
    std::unique_ptr<IntervalSearchTreeNode> left;
    std::unique_ptr<IntervalSearchTreeNode> right;
    int sizeOfThisSubTree;
    RedBlackColor parentLinkColor;
    KeyDataTypeValue maxIntervalValueInSubtree;
};

template <typename Key, typename Value>
struct AvlTreeNodeWithValue {
    Key key;
    Value value;
    std::unique_ptr<AvlTreeNodeWithValue> left;
    std::unique_ptr<AvlTreeNodeWithValue> right;
    int sizeOfThisSubTree;
    int heightOfThisSubTree;
};

template <typename Key, typename Value>
struct BasicTreeNodeWithValue {
    Key key;
    Value value;
    std::unique_ptr<BasicTreeNodeWithValue> left;
    std::unique_ptr<BasicTreeNodeWithValue> right;
    int sizeOfThisSubTree;
};

template <typename Key, typename Value>
struct RedBlackTreeNodeWithValue {
    Key key;
    Value value;
    std::unique_ptr<RedBlackTreeNodeWithValue> left;
    std::unique_ptr<RedBlackTreeNodeWithValue> right;
    int sizeOfThisSubTree;
    RedBlackColor parentLinkColor;
};

template <typename Key, typename Value, typename KeyDataTypeValue>
struct IntervalSearchTreeNodeWithValue {
    Key key;
    Value value;
    std::unique_ptr<IntervalSearchTreeNodeWithValue> left;
    std::unique_ptr<IntervalSearchTreeNodeWithValue> right;
    int sizeOfThisSubTree;
    RedBlackColor parentLinkColor;
    KeyDataTypeValue maxIntervalValueInSubtree;
};

}  // namespace algorithm

}  // namespace alba
