#pragma once

#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithStaticSegmentTree.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>

namespace alba {

namespace algorithm {

template <typename Values>
class RangeQueryWithAccumulatorLazySegmentTree : private RangeQueryWithStaticSegmentTree<Values> {
public:
    // Example for "range query with accumulator" is sum queries

    // Using lazy propagation, we can build a segment tree that supports both range updates and range queries in O(logn)
    // time. The idea is to perform updates and queries from top to bottom and perform updates lazily so that they are
    // propagated down the tree only when it is necessary.

    // In a lazy segment tree, nodes contain two types of information.
    // Like in an ordinary segment tree, each node contains the sum or some other value related to the corresponding
    // subarray. In addition, the node may contain information related to lazy updates, which has not been propagated to
    // its children.

    // There are two types of range updates: each array value in the range is either increased by some value or assigned
    // some value. Both operations can be implemented using similar ideas, and it is even possible to construct a tree
    // that supports both operations at the same time.

    // Lazy segment trees
    // Let us consider an example where our goal is to construct a segment tree that supports two operations:
    // increasing each value in [a,b] by a constant and calculating the sum of values in [a,b].

    // We will construct a tree where each node has two values s/z: s denotes the sum of values in the range,
    // and z denotes the value of a lazy update, which means that all values in the range should be increased by z.
    // In the following tree, z=0 in all nodes, so there are no ongoing lazy updates.

    using BaseClass = RangeQueryWithStaticSegmentTree<Values>;
    using Value = typename BaseClass::Value;
    using Index = typename BaseClass::Index;
    using Function = typename BaseClass::Function;
    using Utilities = typename BaseClass::Utilities;

    RangeQueryWithAccumulatorLazySegmentTree(
        Values const& valuesToCheck, Function const& functionObject, Function const& inverseFunction,
        Value const& identityValue)
        : BaseClass(valuesToCheck, functionObject),
          b_startOfChildren(BaseClass::m_startOfChildren),
          b_treeValues(BaseClass::m_treeValues),
          b_function(BaseClass::m_function),
          m_inverseFunction(inverseFunction),
          m_identityValue(identityValue),
          m_pendingUpdates(b_startOfChildren, m_identityValue)  // only parent have pending updates
    {}

    Value getValueOnInterval(Index const start, Index const end) {
        // This has log(N) running time
        Value result{};
        if (start <= end && (b_startOfChildren + start) < static_cast<Index>(b_treeValues.size()) &&
            (b_startOfChildren + end) < static_cast<Index>(b_treeValues.size())) {
            result = getValueOnIntervalFromTopToBottom(
                start, end, Utilities::ROOT_PARENT_INDEX, 0, b_startOfChildren);  // startOfChildren is size of base too
        }
        return result;
    }

    void increaseAtRange(Index const start, Index const end, Value const& incrementValue) {
        if (start <= end && (b_startOfChildren + start) < static_cast<Index>(b_treeValues.size()) &&
            (b_startOfChildren + end) < static_cast<Index>(b_treeValues.size())) {
            increaseAtRangeFromTopToBottom(
                start, end, Utilities::ROOT_PARENT_INDEX, 0, b_startOfChildren,
                incrementValue);  // startOfChildren is size of base too
        }
    }

    void changeValueAtIndex(Index const index, Value const& newValue) {
        // This has log(N) running time
        Index childIndex = b_startOfChildren + index;
        if (childIndex < static_cast<Index>(b_treeValues.size())) {
            increaseAtRange(
                index, index,
                m_inverseFunction(newValue, b_treeValues.at(childIndex)));  // startOfChildren is size of base too
        }
    }

private:
    Value getValueOnIntervalFromTopToBottom(
        Index const startInterval, Index const endInterval, Index const currentChild, Index const baseLeft,
        Index const baseRight) {
        // This has log(N) running time

        // We also calculate the sum of elements in a range [a,b] by walking in the tree from top to bottom.
        // If the range [x, y] of a node completely belongs to [a,b], we add the s value of the node to the sum.
        // Otherwise, we continue the search recursively downwards in the tree.

        Value result{};
        performUpdateAtIndexIfNeeded(currentChild, baseLeft, baseRight);  // propagate current update before processing
        if (startInterval <= baseLeft && baseRight <= endInterval) {
            result = b_treeValues.at(currentChild);
        } else {
            Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            bool doesLeftPartIntersect = !(endInterval < baseLeft || baseMidPoint < startInterval);
            bool doesRightPartIntersect = !(endInterval < baseMidPoint + 1 || baseRight < startInterval);
            if (doesLeftPartIntersect && doesRightPartIntersect) {
                result = b_function(
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint),
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1,
                        baseRight));
            } else if (doesLeftPartIntersect) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint);
            } else if (doesRightPartIntersect) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1, baseRight);
            }
        }
        return result;
    }

    void increaseAtRangeFromTopToBottom(
        Index const startInterval, Index const endInterval, Index const currentChild, Index const baseLeft,
        Index const baseRight, Value const& incrementValue) {
        // This has log(N) running time

        // When the elements in [a,b] are increased by u, we walk from the root towards the leaves
        // and modify the nodes of the tree as follows:
        // If the range [x, y] of a node is completely inside [a,b], we increase the z value of the node by u and stop.
        // If [x, y] only partially belongs to [a,b], we increase the s value of the node by hu,
        // where h is the size of the intersection of [a,b] and [x, y], and continue our walk recursively in the tree.

        // Note that sometimes it is needed to combine lazy updates.
        // This happens when a node that already has a lazy update is assigned another lazy update.
        // When calculating sums, it is easy to combine lazy updates,
        // because the combination of updates z1 and z2 corresponds to an update z1+z2.

        // performUpdateAtIndexIfNeeded(currentChild, baseLeft, baseRight); // propagate current update before
        // processing, but I think its not needed
        if (baseLeft == baseRight) {
            increment(b_treeValues[currentChild], incrementValue);
        } else if (startInterval <= baseLeft && baseRight <= endInterval) {
            increment(m_pendingUpdates[currentChild], incrementValue);
        } else {
            Index intersectionLeft = std::max(startInterval, baseLeft);
            Index intersectionRight = std::min(endInterval, baseRight);
            Index intersectionLength = intersectionRight + 1 - intersectionLeft;
            incrementMultipleTimes(b_treeValues[currentChild], incrementValue, intersectionLength);

            Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            bool doesLeftPartIntersect = !(endInterval < baseLeft || startInterval > baseMidPoint);
            bool doesRightPartIntersect = !(endInterval < baseMidPoint + 1 || startInterval > baseRight);
            if (doesLeftPartIntersect && doesRightPartIntersect) {
                increaseAtRangeFromTopToBottom(
                    startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint,
                    incrementValue);
                increaseAtRangeFromTopToBottom(
                    startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1, baseRight,
                    incrementValue);
            } else if (doesLeftPartIntersect) {
                increaseAtRangeFromTopToBottom(
                    startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint,
                    incrementValue);
            } else if (doesRightPartIntersect) {
                increaseAtRangeFromTopToBottom(
                    startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint + 1, baseRight,
                    incrementValue);
            }
        }
    }

    void performUpdateAtIndexIfNeeded(Index const index, Index const baseLeft, Index const baseRight) {
        // Both in updates and queries, the value of a lazy update is always
        // propagated to the children of the node before processing the node.
        // The idea is that updates will be propagated downwards only when it is necessary,
        // which guarantees that the operations are always efficient.

        if (index < static_cast<Index>(m_pendingUpdates.size())) {
            Value& pendingUpdate = m_pendingUpdates[index];
            if (m_identityValue != pendingUpdate) {
                incrementMultipleTimes(b_treeValues[index], pendingUpdate, baseRight + 1 - baseLeft);
                incrementAtIndex(Utilities::getLeftChild(index), pendingUpdate);
                incrementAtIndex(Utilities::getRightChild(index), pendingUpdate);
                pendingUpdate = m_identityValue;
            }
        }
    }

    inline void incrementAtIndex(Index const index, Value const& incrementValue) {
        if (isAParent(index)) {
            increment(m_pendingUpdates[index], incrementValue);
        } else {
            increment(b_treeValues[index], incrementValue);
        }
    }

    inline void increment(Value& valueToChange, Value const& incrementValue) const {
        valueToChange = b_function(valueToChange, incrementValue);
    }

    void incrementMultipleTimes(Value& valueToChange, Value const& incrementValue, Index const numberOfTimes) const {
        Value doublingValue(incrementValue);
        Index remainingNumberOfTimes(numberOfTimes);
        while (remainingNumberOfTimes > 0) {
            if (mathHelper::isEven(remainingNumberOfTimes)) {
                increment(doublingValue, doublingValue);
                remainingNumberOfTimes /= 2;
            } else {
                increment(valueToChange, doublingValue);
                remainingNumberOfTimes--;
            }
        }
    }

    Index isAParent(Index const treeIndex) const { return treeIndex < b_startOfChildren; }

    Index const b_startOfChildren;
    Values& b_treeValues;
    Function const& b_function;
    Function m_inverseFunction;
    Value const m_identityValue;
    Values m_pendingUpdates;
};

}  // namespace algorithm

}  // namespace alba
