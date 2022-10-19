#pragma once

#include <Common/Container/AlbaOptional.hpp>
#include <Common/Math/Helpers/DivisibilityHelpers.hpp>
#include <Algorithm/Search/RangeQuery/SegmentTree/RangeQueryWithSegmentTree.hpp>

namespace alba
{

namespace algorithm
{

template <typename Values>
class RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdate : private RangeQueryWithSegmentTree<Values>
{
public:

    // Example for "range query with accumulator" is sum queries

    using BaseClass = RangeQueryWithSegmentTree<Values>;
    using Value = typename BaseClass::Value;
    using Index = typename BaseClass::Index;
    using Function = typename BaseClass::Function;
    using Utilities = typename BaseClass::Utilities;
    using IncrementFunction = std::function<Value(Index const, Index const)>;
    using UpdateDetail = Index;
    using PendingUpdateDetail = AlbaOptional<UpdateDetail>;
    using PendingUpdateDetails = std::vector<PendingUpdateDetail>;

    RangeQueryWithAccumulatorLazySegmentTreeWithDifferentValuesInUpdate(
            Values const& valuesToCheck,
            Function const& functionObject,
            IncrementFunction const& incrementFunction)
        : BaseClass(valuesToCheck, functionObject)
        , b_startOfChildren(BaseClass::m_startOfChildren)
        , b_treeValues(BaseClass::m_treeValues)
        , b_function(BaseClass::m_function)
        , m_incrementFunction(incrementFunction)
        , m_startIndexesForPendingUpdates(b_startOfChildren, PendingUpdateDetail()) // only parent have pending updates
    {}

    Value getValueOnInterval(Index const start, Index const end)
    {
        // This has log(N) running time
        Value result{};
        if(start<=end && (b_startOfChildren+start)<b_treeValues.size() && (b_startOfChildren+end)<b_treeValues.size())
        {
            result = getValueOnIntervalFromTopToBottom(start, end, Utilities::ROOT_PARENT_INDEX, 0, b_startOfChildren); // startOfChildren is size of base too
        }
        return result;
    }

    void increaseAtRange(Index const start, Index const end)
    {
        if(start<=end && (b_startOfChildren+start)<b_treeValues.size() && (b_startOfChildren+end)<b_treeValues.size())
        {
            increaseAtRangeFromTopToBottom(start, end, Utilities::ROOT_PARENT_INDEX, 0, b_startOfChildren); // startOfChildren is size of base too
        }
    }

private:

    Value getValueOnIntervalFromTopToBottom(
            Index const startInterval,
            Index const endInterval,
            Index const currentChild,
            Index const baseLeft,
            Index const baseRight)
    {
        // This has log(N) running time

        Value result{};
        performUpdateAtIndexIfNeeded(currentChild, baseLeft, baseRight); // propagate current update before processing
        if(startInterval<=baseLeft && baseRight<=endInterval)
        {
            result = b_treeValues.at(currentChild);
        }
        else
        {
            Index baseMidPoint = (baseLeft+baseRight)/2;
            bool isLeftPartOutside = endInterval<baseLeft || startInterval>baseMidPoint;
            bool isRightPartOutside = endInterval<baseMidPoint+1 || startInterval>baseRight;
            if(!isLeftPartOutside && !isRightPartOutside)
            {
                result = b_function(
                            getValueOnIntervalFromTopToBottom(startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint),
                            getValueOnIntervalFromTopToBottom(startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint+1, baseRight));
            }
            else if(!isLeftPartOutside && isRightPartOutside)
            {
                result = getValueOnIntervalFromTopToBottom(startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint);
            }
            else if(isLeftPartOutside && !isRightPartOutside)
            {
                result = getValueOnIntervalFromTopToBottom(startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint+1, baseRight);
            }
        }
        return result;
    }

    void increaseAtRangeFromTopToBottom(
            Index const startInterval,
            Index const endInterval,
            Index const currentChild,
            Index const baseLeft,
            Index const baseRight)
    {
        // This has log(N) running time

        // performUpdateAtIndexIfNeeded(currentChild, baseLeft, baseRight); // propagate current update before processing, but I think its not needed
        if(baseLeft==baseRight)
        {
            increment(b_treeValues[currentChild], startInterval, baseLeft, baseLeft);
        }
        else if(startInterval<=baseLeft && baseRight<=endInterval)
        {
            m_startIndexesForPendingUpdates[currentChild].setValue(startInterval);
        }
        else
        {
            Index intersectionLeft = std::max(startInterval, baseLeft);
            Index intersectionRight = std::min(endInterval, baseRight);
            increment(b_treeValues[currentChild], startInterval, intersectionLeft, intersectionRight);

            Index baseMidPoint = (baseLeft+baseRight)/2;
            bool isLeftPartOutside = endInterval<baseLeft || startInterval>baseMidPoint;
            bool isRightPartOutside = endInterval<baseMidPoint+1 || startInterval>baseRight;
            if(!isLeftPartOutside && !isRightPartOutside)
            {
                increaseAtRangeFromTopToBottom(startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint);
                increaseAtRangeFromTopToBottom(startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint+1, baseRight);
            }
            else if(!isLeftPartOutside && isRightPartOutside)
            {
                increaseAtRangeFromTopToBottom(startInterval, endInterval, Utilities::getLeftChild(currentChild), baseLeft, baseMidPoint);
            }
            else if(isLeftPartOutside && !isRightPartOutside)
            {
                increaseAtRangeFromTopToBottom(startInterval, endInterval, Utilities::getRightChild(currentChild), baseMidPoint+1, baseRight);
            }
        }
    }

    void performUpdateAtIndexIfNeeded(
            Index const index,
            Index const baseLeft,
            Index const baseRight)
    {
        if(index < m_startIndexesForPendingUpdates.size())
        {
            PendingUpdateDetail & startIndexForPendingUpdate = m_startIndexesForPendingUpdates[index];
            if(startIndexForPendingUpdate.hasContent())
            {
                increment(b_treeValues[index], startIndexForPendingUpdate.get(), baseLeft, baseRight);
                Index leftChild = Utilities::getLeftChild(index);
                Index rightChild = Utilities::getRightChild(index);
                Index baseMidPoint = (baseLeft+baseRight)/2;
                if(isAParent(leftChild))
                {
                    performUpdateAtIndexIfNeeded(leftChild, baseLeft, baseMidPoint);
                    m_startIndexesForPendingUpdates[leftChild] = startIndexForPendingUpdate; // copy pending update to children
                }
                else
                {
                    increment(b_treeValues[leftChild], startIndexForPendingUpdate.get(), baseLeft, baseMidPoint);
                }
                if(isAParent(rightChild))
                {
                    performUpdateAtIndexIfNeeded(rightChild, baseMidPoint+1, baseRight);
                    m_startIndexesForPendingUpdates[rightChild] = startIndexForPendingUpdate; // copy pending update to children
                }
                else
                {
                    increment(b_treeValues[rightChild], startIndexForPendingUpdate.get(), baseMidPoint+1, baseRight);
                }
                startIndexForPendingUpdate.clear();
            }
        }
    }

    inline void increment(Value & valueToChange, Index const startIndex, Index const left, Index const right) const
    {
        Index numberOfChildren = b_treeValues.size() - b_startOfChildren;
        Index startInterval = std::min(left, numberOfChildren-1) - startIndex;
        Index endInterval = std::min(right, numberOfChildren-1) - startIndex;
        valueToChange = b_function(valueToChange, m_incrementFunction(startInterval, endInterval));
    }

    Index isAParent(Index const treeIndex) const
    {
        return treeIndex<b_startOfChildren;
    }

    Index const b_startOfChildren;
    Values & b_treeValues;
    Function const& b_function;
    IncrementFunction m_incrementFunction;
    PendingUpdateDetails m_startIndexesForPendingUpdates;
};

}

}
