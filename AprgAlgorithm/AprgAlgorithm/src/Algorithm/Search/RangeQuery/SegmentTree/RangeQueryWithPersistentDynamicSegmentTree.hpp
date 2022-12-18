#pragma once

#include <Algorithm/Search/Common/DynamicSegmentTreeNode.hpp>
#include <Algorithm/Search/Common/SegmentTreeUtilities.hpp>
#include <Algorithm/Utilities/MidpointOfIndexes.hpp>
#include <Common/Container/AlbaFakeCopyable.hpp>

#include <functional>
#include <list>

namespace alba
{

namespace algorithm
{

template <typename Values>
class RangeQueryWithPersistentDynamicSegmentTree
{
public:
    // This supports "selector" and "accumulator" type queries.

    // Using a dynamic implementation, it is also possible to create a persistent segment tree that stores the modification history of the tree.
    // In such an implementation, we can efficiently access all versions of the tree that have existed during the algorithm.
    // When the modification history is available, we can perform queries in any previous tree like in an ordinary segment tree,
    // because the full structure of each tree is stored. We can also create new trees based on previous trees and modify them independently.

    // After each update, most nodes of the tree remain the same, so an efficient way to store the modification history
    // is to represent each tree in the history as a combination of new nodes and subtrees of previous trees.

    // The structure of each previous tree can be reconstructed by following the pointers starting at the corresponding root node.
    // Since each operation adds only O(logn) new nodes to the tree, it is possible to store the full modification history of the tree.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using Function = std::function<Value(Value const&, Value const&)>;
    using Utilities = SegmentTreeUtilities<Index>;
    using Node = PersistentDynamicSegmentTreeNode<Value>;
    using NodePointer = std::shared_ptr<Node>;
    using NodeRoot = AlbaFakeCopyable<NodePointer>;
    using NodeRoots = std::list<NodeRoot>;
    using StepCount = unsigned int;

    RangeQueryWithPersistentDynamicSegmentTree(
            Values const& valuesToCheck,
            Function const& functionObject)
        : m_maxChildrenIndex(0U)
        , m_numberOfValues(valuesToCheck.size())
        , m_function(functionObject)
    {
        initialize(valuesToCheck);
    }

    Value getValueOnInterval(Index const start, Index const end) const
    {
        // This has log(N) running time
        Value result{};
        if(start<=end && start<m_numberOfValues && end<m_numberOfValues)
        {
            result = getValueOnIntervalFromTopToBottom(start, end, m_roots.back().getObject(), 0, m_maxChildrenIndex);
        }
        return result;
    }

    Value getValueOnIntervalOnPreviousTree(Index const start, Index const end, StepCount const numberOfPreviousSteps) const
    {
        // This has log(N) running time
        Value result{};
        if(start<=end && start<m_numberOfValues && end<m_numberOfValues && numberOfPreviousSteps<m_roots.size())
        {
            StepCount stepCount(0U);
            auto it=m_roots.crbegin();
            for(; it!=m_roots.crend() && stepCount<numberOfPreviousSteps; it++, stepCount++)
            {}
            result = getValueOnIntervalFromTopToBottom(start, end, it->getObject(), 0, m_maxChildrenIndex);
        }
        return result;
    }

    virtual void changeValueAtIndex(Index const index, Value const& newValue)
    {
        // This has log(N) running time
        if(index<m_numberOfValues)
        {
            NodeRoot & previousTreeRoot(m_roots.back());
            m_roots.emplace_back();
            changeValueOnIndexFromTopToBottom(
                        index, newValue, previousTreeRoot.getObjectReference(), m_roots.back().getObjectReference(), 0, m_maxChildrenIndex);
        }
    }

protected:

    Value getValueOnIntervalFromTopToBottom(
            Index const startInterval,
            Index const endInterval,
            NodePointer const& nodePointer,
            Index const baseLeft,
            Index const baseRight) const
    {
        // This has log(N) running time

        Value result{};
        if(startInterval<=baseLeft && baseRight<=endInterval)
        {
            result = nodePointer->value;
        }
        else
        {
            Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            bool isLeftPartIncluded = nodePointer->leftChildPointer && !(endInterval<baseLeft || baseMidPoint<startInterval);
            bool isRightPartIncluded = nodePointer->rightChildPointer && !(endInterval<baseMidPoint+1 || baseRight<startInterval);
            if(isLeftPartIncluded && isRightPartIncluded)
            {
                result = m_function(
                            getValueOnIntervalFromTopToBottom(startInterval, endInterval, nodePointer->leftChildPointer, baseLeft, baseMidPoint),
                            getValueOnIntervalFromTopToBottom(startInterval, endInterval, nodePointer->rightChildPointer, baseMidPoint+1, baseRight));
            }
            else if(isLeftPartIncluded)
            {
                result = getValueOnIntervalFromTopToBottom(startInterval, endInterval, nodePointer->leftChildPointer, baseLeft, baseMidPoint);
            }
            else if(isRightPartIncluded)
            {
                result = getValueOnIntervalFromTopToBottom(startInterval, endInterval, nodePointer->rightChildPointer, baseMidPoint+1, baseRight);
            }
        }
        return result;
    }

    Value getCombinedValueBasedFromChildren(NodePointer const& nodePointer) const
    {
        Value result{};
        if(nodePointer->leftChildPointer && nodePointer->rightChildPointer)
        {
            result = m_function(nodePointer->leftChildPointer->value, nodePointer->rightChildPointer->value);
        }
        else if(nodePointer->leftChildPointer)
        {
            result = nodePointer->leftChildPointer->value;
        }
        else if(nodePointer->rightChildPointer)
        {
            result = nodePointer->rightChildPointer->value;
        }
        return result;
    }

    void initialize(Values const& valuesToCheck)
    {
        if(!valuesToCheck.empty())
        {
            m_maxChildrenIndex = Utilities::getMinimumNumberOfParents(valuesToCheck.size());
            m_roots.emplace_back();
            setValuesFromTopToBottom(valuesToCheck, m_roots.back().getObjectReference(), 0, m_maxChildrenIndex);
        }
    }

    void setValuesFromTopToBottom(
            Values const& values,
            NodePointer & nodePointer,
            Index const baseLeft,
            Index const baseRight)
    {
        // This has log(N) running time

        if(!nodePointer)
        {
            nodePointer.reset(new Node{Value{}, nullptr, nullptr});
        }
        if(baseLeft==baseRight)
        {
            nodePointer->value = values.at(baseLeft);
        }
        else
        {
            Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
            setValuesFromTopToBottom(values, nodePointer->leftChildPointer, baseLeft, baseMidPoint);
            if(baseMidPoint+1<values.size())
            {
                setValuesFromTopToBottom(values, nodePointer->rightChildPointer, baseMidPoint+1, baseRight);
            }
            nodePointer->value = getCombinedValueBasedFromChildren(nodePointer);
        }
    }

    void changeValueOnIndexFromTopToBottom(
            Index const index,
            Value const& newValue,
            NodePointer const& previousTreeNode,
            NodePointer & newTreeNode,
            Index const baseLeft,
            Index const baseRight)
    {
        // This has log(N) running time

        if(previousTreeNode)
        {
            if(baseLeft==baseRight)
            {
                newTreeNode.reset(new Node{newValue, nullptr, nullptr});
            }
            else
            {
                Index baseMidPoint = getMidpointOfIndexes(baseLeft, baseRight);
                if(index <= baseMidPoint)
                {
                    newTreeNode.reset(new Node{Value{}, nullptr, previousTreeNode->rightChildPointer});
                    changeValueOnIndexFromTopToBottom(
                                index, newValue, previousTreeNode->leftChildPointer, newTreeNode->leftChildPointer, baseLeft, baseMidPoint);
                }
                else
                {
                    newTreeNode.reset(new Node{Value{}, previousTreeNode->leftChildPointer, nullptr});
                    changeValueOnIndexFromTopToBottom(
                                index, newValue, previousTreeNode->rightChildPointer, newTreeNode->rightChildPointer, baseMidPoint+1, baseRight);
                }
                newTreeNode->value = getCombinedValueBasedFromChildren(newTreeNode);
            }
        }
    }

    Index m_maxChildrenIndex;
    Index const m_numberOfValues;
    Function m_function;
    NodeRoots m_roots;
};

}

}
