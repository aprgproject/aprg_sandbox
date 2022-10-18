#pragma once

#include <Algorithm/Search/Common/SegmentTreeUtilities.hpp>
#include <Algorithm/Search/Common/DynamicSegmentTreeNode.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Value>
class RangeQueryWithSparseSegmentTree
{
public:

    using Index = unsigned int;
    using Function = std::function<Value(Value const&, Value const&)>;
    using Utilities = SegmentTreeUtilities<Index>;
    using Node = DynamicSegmentTreeNode<Index, Value>;
    using NodePointer = std::unique_ptr<Node>;

    RangeQueryWithSparseSegmentTree(
            Index const numberOfValues,
            Value const defaultValue,
            Function const& functionObject)
        : m_numberOfValues(numberOfValues)
        , m_maxChildrenIndex(0U)
        , m_defaultValue(defaultValue)
        , m_function(functionObject)
    {
        initialize();
    }

    // This supports "selector" and "accumulator" type queries.

    Value getValueOnInterval(Index const start, Index const end)
    {
        // This has log(N) running time
        Value result{};
        if(start<=end && start<m_numberOfValues && end<m_numberOfValues)
        {
            result = getValueOnIntervalFromTopToBottom(start, end, m_root, 0, m_maxChildrenIndex);
        }
        return result;
    }

    void setValueOnIndex(Index const index, Value const valueToSet)
    {
        // This has log(N) running time
        if(index<m_numberOfValues)
        {
            setValueOnIndexFromTopToBottom(index, m_root, 0, m_maxChildrenIndex, valueToSet);
        }
    }

protected:

    void initialize()
    {
        m_maxChildrenIndex = Utilities::getMinimumNumberOfParents(m_numberOfValues);
    }

    Value getValueOnIntervalFromTopToBottom(
            Index const startInterval,
            Index const endInterval,
            NodePointer & currentNodePointer,
            Index const baseLeft,
            Index const baseRight)
    {
        // This has log(N) running time

        Value result{};
        if(!currentNodePointer)
        {
            currentNodePointer.reset(new Node{m_defaultValue, nullptr, nullptr});
        }
        if(startInterval<=baseLeft && baseRight<=endInterval)
        {
            result = currentNodePointer->value;
        }
        else
        {
            Index baseMidPoint = (baseLeft+baseRight)/2;
            bool isLeftPartOutside = endInterval<baseLeft || startInterval>baseMidPoint;
            bool isRightPartOutside = endInterval<baseMidPoint+1 || startInterval>baseRight;
            if(!isLeftPartOutside && !isRightPartOutside)
            {
                result = m_function(
                            getValueOnIntervalFromTopToBottom(startInterval, endInterval, currentNodePointer->leftChildPointer, baseLeft, baseMidPoint),
                            getValueOnIntervalFromTopToBottom(startInterval, endInterval, currentNodePointer->rightChildPointer, baseMidPoint+1, baseRight));
            }
            else if(!isLeftPartOutside && isRightPartOutside)
            {
                result = getValueOnIntervalFromTopToBottom(startInterval, endInterval, currentNodePointer->leftChildPointer, baseLeft, baseMidPoint);
            }
            else if(isLeftPartOutside && !isRightPartOutside)
            {
                result = getValueOnIntervalFromTopToBottom(startInterval, endInterval, currentNodePointer->rightChildPointer, baseMidPoint+1, baseRight);
            }
        }
        return result;
    }

    void setValueOnIndexFromTopToBottom(
            Index const index,
            NodePointer & currentNodePointer,
            Index const baseLeft,
            Index const baseRight,
            Value const valueToSet)
    {
        // This has log(N) running time

        if(!currentNodePointer)
        {
            currentNodePointer.reset(new Node{m_defaultValue, nullptr, nullptr});
        }
        if(baseLeft==baseRight)
        {
            currentNodePointer->value = valueToSet;
        }
        else
        {
            Index baseMidPoint = (baseLeft+baseRight)/2;
            bool isLeftPartOutside = index<baseLeft || index>baseMidPoint;
            bool isRightPartOutside = index<baseMidPoint+1 || index>baseRight;
            if(!isLeftPartOutside)
            {
                currentNodePointer->value = m_function(currentNodePointer->value, valueToSet);
                setValueOnIndexFromTopToBottom(index, currentNodePointer->leftChildPointer, baseLeft, baseMidPoint, valueToSet);
            }
            if(!isRightPartOutside)
            {
                currentNodePointer->value = m_function(currentNodePointer->value, valueToSet);
                setValueOnIndexFromTopToBottom(index, currentNodePointer->rightChildPointer, baseMidPoint+1, baseRight, valueToSet);
            }
        }
    }

    Index const m_numberOfValues;
    Index m_maxChildrenIndex;
    Value const m_defaultValue;
    Function m_function;
    NodePointer m_root;
};

}

}
