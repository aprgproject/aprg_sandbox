#pragma once

#include <Algorithm/Search/Common/DynamicSegmentTreeNode.hpp>
#include <Algorithm/Search/Common/SegmentTreeUtilities.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>

#include <functional>

namespace alba {

namespace algorithm {

template <typename Values>
class RangeQueryWithDynamicSegmentTree {
public:
    // This supports "selector" and "accumulator" type queries.

    // An segment tree is dynamic, which means memory is allocated only for nodes
    // that are actually accessed during the algorithm, which can save a large amount of memory.

    using Index = int;
    using Value = typename Values::value_type;
    using Function = std::function<Value(Value const&, Value const&)>;
    using Utilities = SegmentTreeUtilities<Index>;
    using Node = DynamicSegmentTreeNode<Value>;
    using NodePointer = std::unique_ptr<Node>;

    RangeQueryWithDynamicSegmentTree(Values const& valuesToCheck, Function const& functionObject)
        : m_maxChildrenIndex(0), m_numberOfValues(valuesToCheck.size()), m_function(functionObject) {
        initialize(valuesToCheck);
    }

    Value getValueOnInterval(Index const start, Index const end) const {
        // This has log(N) running time
        Value result{};
        if (start <= end && start < m_numberOfValues && end < m_numberOfValues) {
            result = getValueOnIntervalFromTopToBottom(start, end, m_root, 0, m_maxChildrenIndex);
        }
        return result;
    }

    virtual void changeValueAtIndex(Index const index, Value const& newValue) {
        // This has log(N) running time
        if (index < m_numberOfValues) {
            changeValueOnIndexFromTopToBottom(index, newValue, m_root, 0, m_maxChildrenIndex);
        }
    }

protected:
    Value getValueOnIntervalFromTopToBottom(
        Index const startInterval, Index const endInterval, NodePointer const& nodePointer, Index const baseLeft,
        Index const baseRight) const {
        // This has log(N) running time

        Value result{};
        if (startInterval <= baseLeft && baseRight <= endInterval) {
            result = nodePointer->value;
        } else {
            Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            bool isLeftPartIncluded =
                nodePointer->leftChildPointer && !(endInterval < baseLeft || baseMidPoint < startInterval);
            bool isRightPartIncluded =
                nodePointer->rightChildPointer && !(endInterval < baseMidPoint + 1 || baseRight < startInterval);
            if (isLeftPartIncluded && isRightPartIncluded) {
                result = m_function(
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, nodePointer->leftChildPointer, baseLeft, baseMidPoint),
                    getValueOnIntervalFromTopToBottom(
                        startInterval, endInterval, nodePointer->rightChildPointer, baseMidPoint + 1, baseRight));
            } else if (isLeftPartIncluded) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, nodePointer->leftChildPointer, baseLeft, baseMidPoint);
            } else if (isRightPartIncluded) {
                result = getValueOnIntervalFromTopToBottom(
                    startInterval, endInterval, nodePointer->rightChildPointer, baseMidPoint + 1, baseRight);
            }
        }
        return result;
    }

    Value getCombinedValueBasedFromChildren(NodePointer const& nodePointer) const {
        Value result{};
        if (nodePointer->leftChildPointer && nodePointer->rightChildPointer) {
            result = m_function(nodePointer->leftChildPointer->value, nodePointer->rightChildPointer->value);
        } else if (nodePointer->leftChildPointer) {
            result = nodePointer->leftChildPointer->value;
        } else if (nodePointer->rightChildPointer) {
            result = nodePointer->rightChildPointer->value;
        }
        return result;
    }

    void initialize(Values const& valuesToCheck) {
        if (!valuesToCheck.empty()) {
            m_maxChildrenIndex = Utilities::getMinimumNumberOfParents(valuesToCheck.size());
            setValuesFromTopToBottom(valuesToCheck, m_root, 0, m_maxChildrenIndex);
        }
    }

    void setValuesFromTopToBottom(
        Values const& values, NodePointer& nodePointer, Index const baseLeft, Index const baseRight) {
        // This has log(N) running time

        if (!nodePointer) {
            nodePointer.reset(new Node{Value{}, nullptr, nullptr});
        }
        if (baseLeft == baseRight) {
            nodePointer->value = values[baseLeft];
        } else {
            Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            setValuesFromTopToBottom(values, nodePointer->leftChildPointer, baseLeft, baseMidPoint);            if (baseMidPoint + 1 < static_cast<Index>(values.size())) {
                setValuesFromTopToBottom(values, nodePointer->rightChildPointer, baseMidPoint + 1, baseRight);
            }
            nodePointer->value = getCombinedValueBasedFromChildren(nodePointer);        }
    }

    void changeValueOnIndexFromTopToBottom(
        Index const index, Value const& newValue, NodePointer& nodePointer, Index const baseLeft,
        Index const baseRight) {
        // This has log(N) running time

        if (nodePointer) {
            if (baseLeft == baseRight) {
                nodePointer->value = newValue;
            } else {
                Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
                if (index <= baseMidPoint) {
                    changeValueOnIndexFromTopToBottom(
                        index, newValue, nodePointer->leftChildPointer, baseLeft, baseMidPoint);
                } else {
                    changeValueOnIndexFromTopToBottom(
                        index, newValue, nodePointer->rightChildPointer, baseMidPoint + 1, baseRight);
                }
                nodePointer->value = getCombinedValueBasedFromChildren(nodePointer);
            }
        }
    }

    Index m_maxChildrenIndex;
    Index const m_numberOfValues;
    Function m_function;
    NodePointer m_root;
};

}  // namespace algorithm

}  // namespace alba
