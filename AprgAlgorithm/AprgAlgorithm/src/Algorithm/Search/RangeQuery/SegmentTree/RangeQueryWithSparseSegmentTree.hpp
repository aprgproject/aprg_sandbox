#pragma once

#include <Algorithm/Search/Common/DynamicSegmentTreeNode.hpp>
#include <Algorithm/Search/Common/SegmentTreeUtilities.hpp>
#include <Algorithm/Utilities/IndexHelper.hpp>

#include <functional>
namespace alba {

namespace algorithm {
template <typename Value>
class RangeQueryWithSparseSegmentTree {
public:
    // This supports "selector" and "accumulator" type queries.

    // A dynamic segment tree is useful when the underlying array is sparse, i.e.,
    // the range [0,n-1] of allowed indices is large, but most array values are zeros.
    // While an ordinary segment tree uses O(n) memory, a dynamic segment tree only uses O(klogn) memory,
    // where k is the number of operations performed.

    // A sparse segment tree initially has only one node [0,n-1] whose value is zero, which means that every array value
    // is zero. After updates, new nodes are dynamically added to the tree.

    // Any path from the root node to a leaf contains O(logn) nodes, so each operation adds at most O(logn) new nodes to
    // the tree. Thus, after k operations, the tree contains at most O(klogn) nodes.

    // Note that if we know all elements to be updated at the beginning of the algorithm,
    // a dynamic segment tree is not necessary, because we can use an ordinary segment tree with index compression.
    // However, this is not possible when the indices are generated during the algorithm

    using Index = int;
    using Function = std::function<Value(Value const&, Value const&)>;
    using Utilities = SegmentTreeUtilities<Index>;
    using Node = DynamicSegmentTreeNode<Value>;
    using NodePointer = std::unique_ptr<Node>;

    RangeQueryWithSparseSegmentTree(
        Index const numberOfValues, Value const& defaultValue, Function const& functionObject)
        : m_maxChildrenIndex(0),
          m_numberOfValues(numberOfValues),
          m_defaultValue(defaultValue),
          m_function(functionObject) {
        initialize();
    }

    Value getValueOnInterval(Index const start, Index const end) {
        // This has log(N) running time
        Value result{};
        if (start <= end && start < m_numberOfValues && end < m_numberOfValues) {
            result = getValueOnIntervalFromTopToBottom(start, end, m_root, 0, m_maxChildrenIndex);
        }
        return result;
    }

    void setValueOnIndex(Index const index, Value const& valueToSet) {
        // This has log(N) running time
        if (index < m_numberOfValues) {
            setValueOnIndexFromTopToBottom(index, valueToSet, m_root, 0, m_maxChildrenIndex);
        }
    }

protected:
    Value getCombinedValueBasedFromChildren(NodePointer const& nodePointer) const {
        Value result{};
        if (nodePointer->leftChildPointer && nodePointer->rightChildPointer) {
            result = m_function(nodePointer->leftChildPointer->value, nodePointer->rightChildPointer->value);
        } else if (nodePointer->leftChildPointer) {
            result = m_function(m_defaultValue, nodePointer->leftChildPointer->value);
        } else if (nodePointer->rightChildPointer) {
            result = m_function(m_defaultValue, nodePointer->rightChildPointer->value);
        }
        return result;
    }

    void initialize() { m_maxChildrenIndex = Utilities::getMinimumNumberOfParents(m_numberOfValues); }

    Value getValueOnIntervalFromTopToBottom(
        Index const startInterval, Index const endInterval, NodePointer& nodePointer, Index const baseLeft,
        Index const baseRight) {
        // This has log(N) running time

        Value result{};
        if (!nodePointer) {
            nodePointer.reset(new Node{m_defaultValue, nullptr, nullptr});
        }
        if (startInterval <= baseLeft && baseRight <= endInterval) {
            result = nodePointer->value;
        } else {
            Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            bool doesLeftPartIntersect = !(endInterval < baseLeft || baseMidPoint < startInterval);
            bool doesRightPartIntersect = !(endInterval < baseMidPoint + 1 || baseRight < startInterval);
            if (doesLeftPartIntersect && doesRightPartIntersect) {
                result = m_function(
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, nodePointer->leftChildPointer, baseLeft, baseMidPoint),
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, nodePointer->rightChildPointer, baseMidPoint + 1, baseRight));
            } else if (doesLeftPartIntersect) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, nodePointer->leftChildPointer, baseLeft, baseMidPoint);
            } else if (doesRightPartIntersect) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, nodePointer->rightChildPointer, baseMidPoint + 1, baseRight);
            }
        }
        return result;
    }

    void setValueOnIndexFromTopToBottom(
        Index const index, Value const& valueToSet, NodePointer& nodePointer, Index const baseLeft,
        Index const baseRight) {
        // This has log(N) running time

        if (!nodePointer) {
            nodePointer.reset(new Node{m_defaultValue, nullptr, nullptr});
        }
        if (baseLeft == baseRight) {
            nodePointer->value = valueToSet;
        } else {
            Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            if (index <= baseMidPoint) {
                setValueOnIndexFromTopToBottom(
                    index, valueToSet, nodePointer->leftChildPointer, baseLeft, baseMidPoint);
            } else {
                setValueOnIndexFromTopToBottom(
                    index, valueToSet, nodePointer->rightChildPointer, baseMidPoint + 1, baseRight);
            }
            nodePointer->value = getCombinedValueBasedFromChildren(nodePointer);
        }
    }

    Index m_maxChildrenIndex;
    Index const m_numberOfValues;
    Value const m_defaultValue;
    Function m_function;
    NodePointer m_root;
};

}  // namespace algorithm

}  // namespace alba
