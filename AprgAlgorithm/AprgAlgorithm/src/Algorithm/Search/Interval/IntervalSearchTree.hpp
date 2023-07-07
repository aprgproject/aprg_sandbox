#pragma once

#include <Algorithm/SetAndSymbolTable/Common/BinarySearchTree/BinarySearchTreeNodes.hpp>
#include <Algorithm/SetAndSymbolTable/Set/BinarySearchTree/Common/BaseRedBlackBinarySearchTreeSet.hpp>
#include <Common/Math/Helpers/SignRelatedHelpers.hpp>

#include <vector>

namespace alba {

namespace algorithm {

template <typename IntervalUnit>
class Interval {
public:
    IntervalUnit start;
    IntervalUnit end;
    bool operator<(Interval const& interval) const { return start < interval.start; }
    bool operator>(Interval const& interval) const { return start > interval.start; }
    bool operator==(Interval const& interval) const { return start == interval.start; }
    bool operator<=(Interval const& interval) const { return start <= interval.start; }
    bool operator>=(Interval const& interval) const { return start >= interval.start; }
};

template <typename IntervalUnit>
class IntervalSearchTree : public BaseRedBlackBinarySearchTreeSet<
                               Interval<IntervalUnit>, IntervalSearchTreeNode<Interval<IntervalUnit>, IntervalUnit>> {
public:
    using Key = Interval<IntervalUnit>;
    using Keys = std::vector<Key>;
    using BaseClass = BaseRedBlackBinarySearchTreeSet<
        Interval<IntervalUnit>, IntervalSearchTreeNode<Interval<IntervalUnit>, IntervalUnit>>;
    using Node = typename BaseClass::Node;
    using NodeUniquePointer = typename BaseClass::NodeUniquePointer;
    using BooleanBinaryFunction = std::function<bool(Key const&, Key const&)>;

    IntervalSearchTree() : b_root(BaseClass::m_root) {}

    Keys getIntersectingIntervalsOf(Key const& intervalToCheck) const {
        Keys keys;
        searchForIntersectingIntervals(keys, b_root, intervalToCheck);
        return keys;
    }

    void mergeIntervals(BooleanBinaryFunction const& shouldMerge) { mergeIntervals(b_root, shouldMerge); }

protected:
    void updateTreeNodeDetails(Node& node) const override {
        node.numberOfNodesOnThisSubTree = this->calculateSizeOfNodeBasedFromLeftAndRight(node);
        node.maxIntervalValueInSubtree = getMaxValueBasedFromLeftAndRight(node);
    }

    void putStartingOnThisNode(NodeUniquePointer& nodePointer, Key const& key) override {
        if (nodePointer) {
            Key const& currentKey(nodePointer->key);
            if (key < currentKey) {
                putStartingOnThisNode(nodePointer->left, key);
                this->updateTreeNodeDetails(*nodePointer);
            } else if (key > currentKey) {
                putStartingOnThisNode(nodePointer->right, key);
                this->updateTreeNodeDetails(*nodePointer);
            }
            if (this->hasARightLeaningRedLinkOnOneChild(nodePointer)) {
                this->rotateLeft(nodePointer);
            }
            if (this->hasTwoLeftLeaningRedLinksInARow(nodePointer)) {
                this->rotateRight(nodePointer);
            }
            if (this->hasTwoRedLinksOnItsChildren(nodePointer)) {
                this->setParentAsRedAndChildrenAsBlack(nodePointer);
            }
        } else {
            nodePointer.reset(new Node{key, nullptr, nullptr, 1, RedBlackColor::Red, key.end});
        }
    }

    bool areIntersectingIntervals(Key const& interval1, Key const& interval2) const {
        auto delta1(mathHelper::getPositiveDelta(interval1.start, interval1.end));
        auto delta2(mathHelper::getPositiveDelta(interval2.start, interval2.end));
        auto sumOfDeltas(delta1 + delta2);
        auto maxDeltaEndpoints(std::max(
            mathHelper::getPositiveDelta(interval1.start, interval2.end),
            mathHelper::getPositiveDelta(interval2.start, interval1.end)));
        return maxDeltaEndpoints <= sumOfDeltas;
    }

    void searchForIntersectingIntervals(
        Keys& intersectingIntervals, NodeUniquePointer const& nodePointer, Key const& intervalToCheck) const {
        if (nodePointer) {
            if (areIntersectingIntervals(nodePointer->key, intervalToCheck)) {
                // if interval in node intersect query interval
                intersectingIntervals.emplace_back(nodePointer->key);
            }
            if (!nodePointer->left) {
                // if left subtree is null, go right
                searchForIntersectingIntervals(intersectingIntervals, nodePointer->right, intervalToCheck);
            } else if (nodePointer->left->maxIntervalValueInSubtree < intervalToCheck.start) {
                // if max endpoint in left subtree is less than low, go right
                searchForIntersectingIntervals(intersectingIntervals, nodePointer->right, intervalToCheck);
            } else {
                // else go left (and go right as well because all intervals should be collected)
                searchForIntersectingIntervals(intersectingIntervals, nodePointer->left, intervalToCheck);
                searchForIntersectingIntervals(intersectingIntervals, nodePointer->right, intervalToCheck);
            }
        }
    }

    IntervalUnit getMaxValueBasedFromLeftAndRight(Node& node) const {
        IntervalUnit maxIntervalValueInSubtree(node.key.end);
        if (node.left) {
            maxIntervalValueInSubtree = std::max(maxIntervalValueInSubtree, node.left->key.end);
        }
        if (node.right) {
            maxIntervalValueInSubtree = std::max(maxIntervalValueInSubtree, node.right->key.end);
        }
        return maxIntervalValueInSubtree;
    }

    void mergeIntervals(NodeUniquePointer& nodePointer, BooleanBinaryFunction const& shouldMerge) {
        if (nodePointer) {
            if (nodePointer->left) {
                if (shouldMerge(nodePointer->left->key, nodePointer->key)) {
                    nodePointer->key.start = nodePointer->left->key.start;
                    BaseClass::deleteBasedOnKeyStartingOnThisNode(nodePointer->left, nodePointer->left->key);
                }
            }
            if (nodePointer->right) {
                if (shouldMerge(nodePointer->key, nodePointer->right->key)) {
                    nodePointer->key.end = nodePointer->right->key.end;
                    BaseClass::deleteBasedOnKeyStartingOnThisNode(nodePointer->right, nodePointer->right->key);
                }
            }
            mergeIntervals(nodePointer->left, shouldMerge);
            mergeIntervals(nodePointer->right, shouldMerge);
        }
    }

private:
    NodeUniquePointer& b_root;
};

}  // namespace algorithm

}  // namespace alba
