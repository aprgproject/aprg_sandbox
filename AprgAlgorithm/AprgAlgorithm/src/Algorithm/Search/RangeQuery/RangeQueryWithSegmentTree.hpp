#pragma once

#include <Common/Math/Helpers/LogarithmHelpers.hpp>
#include <Common/Math/Helpers/PowerHelpers.hpp>

#include <functional>

namespace alba
{

namespace algorithm
{

template <typename Values>
class RangeQueryWithSegmentTree
{
public:
    // This supports "selector" and "accumulator" type queries.

    // A segment tree is a data structure that supports two operations: processing a range query and updating an array value.
    // Segment trees can support sum queries, minimum and maximum queries and many other queries so that both operations work in O(logn) time.
    // Compared to a binary indexed tree, the advantage of a segment tree is that it is a more general data structure.
    // While binary indexed trees only support sum queries, segment trees also support other queries.
    // On the other hand, a segment tree requires more memory and is a bit more difficult to implement.

    // Segment trees can support all range queries where it is possible to divide a range into two parts,
    // Calculate the answer separately for both parts and then efficiently combine the answers.

    // Examples of such queries are minimum and maximum, greatest common divisor, and bit operations and, or and xor.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using Function = std::function<Value(Value const&, Value const&)>;

    static constexpr unsigned int ROOT_PARENT=0U; // the first parent
    static constexpr unsigned int NUMBER_OF_CHILDREN=2U; // only 2 children

    RangeQueryWithSegmentTree(
            Values const& valuesToCheck,
            Function const& functionObject)
        : m_smallestPowerOfTwoThatFitsChildren(0U)
        , m_startOfChildren(0U)
        , m_treeValues()
        , m_function(functionObject)
    {        initialize(valuesToCheck);
    }

    Value getValueOnInterval(Index const start, Index const end) const // bottom to top approach
    {
        // This has logN running time
        return getValueOnIntervalFromBottomToTop(start, end);
    }

    Value getValueOnIntervalFromTopToBottom(Index const start, Index const end) const // top to bottom approach
    {
        // This has logN running time
        Value result{};
        Index first(m_startOfChildren+start);
        Index last(m_startOfChildren+end);
        if(first<=last && first<m_treeValues.size() && last<m_treeValues.size())
        {
            result = getValueOnIntervalFromTopToBottom(start, end, ROOT_PARENT, 0, m_startOfChildren); // startOfChildren is size of base too
        }
        return result;
    }
    void changeValueAtIndex(Index const index, Value const newValue)
    {
        // This has logN running time        changeValueAtIndexFromBottomToTop(index, newValue);
    }

private:

    Value getValueOnIntervalFromBottomToTop(Index const start, Index const end) const
    {
        // This has logN running time
        Value result{};        Index first(m_startOfChildren+start);
        Index last(m_startOfChildren+end);
        if(first<=last && first<m_treeValues.size() && last<m_treeValues.size())
        {
            result = m_treeValues.at(first++);
            while(first < last)
            {                if(isRightChild(first))
                {
                    result = m_function(result, m_treeValues.at(first++)); // move to next value (right) because current value is added
                }                if(isLeftChild(last))
                {
                    result = m_function(result, m_treeValues.at(last--)); // move to next value (left) because current value is added
                }
                first = getParent(first);
                last = getParent(last);
            }
            if(first == last) // add value if it ends on the same place
            {
                result = m_function(result, m_treeValues.at(first));
            }
        }
        return result;
    }

    Value getValueOnIntervalFromTopToBottom(
            Index const startInterval,
            Index const endInterval,
            Index const currentChild,
            Index const baseLeft,
            Index const baseRight) const
    {
        // This has logN running time

        // The parameter k indicates the current position in tree.
        // Initially k equals 1, because we begin at the root of the tree.
        // The range [x, y] corresponds to k and is initially [0,n-1].
        // When calculating the sum, if [x, y] is outside [a,b], the sum is 0, and if [x, y] is completely inside [a,b], the sum can be found in tree.
        // If [x, y] is partially inside [a,b], the search continues recursively to the left and right half of [x, y].
        // The left half is [x,d] and the right half is [d+1, y] where d = floor((x+y)/2).

        Value result{};
        if((startInterval==baseLeft && endInterval==baseRight) || baseLeft==baseRight)
        {
            result = m_treeValues.at(currentChild);
        }        else
        {
            Index baseMidPoint = (baseLeft+baseRight)/2;
            bool isLeftPartOutside = endInterval<baseLeft || startInterval>baseMidPoint;            bool isRightPartOutside = endInterval<baseMidPoint+1 || startInterval>baseRight;
            if(!isLeftPartOutside && !isRightPartOutside)
            {
                result = m_function(
                            getValueOnIntervalFromTopToBottom(startInterval, endInterval, getFirstChild(currentChild), baseLeft, baseMidPoint),
                            getValueOnIntervalFromTopToBottom(startInterval, endInterval, getSecondChild(currentChild), baseMidPoint+1, baseRight));
            }
            else if(!isLeftPartOutside && isRightPartOutside)
            {
                result = getValueOnIntervalFromTopToBottom(startInterval, endInterval, getFirstChild(currentChild), baseLeft, baseMidPoint);
            }
            else if(isLeftPartOutside && !isRightPartOutside)
            {
                result = getValueOnIntervalFromTopToBottom(startInterval, endInterval, getSecondChild(currentChild), baseMidPoint+1, baseRight);
            }
        }
        return result;
    }

    void initialize(Values const& valuesToCheck)
    {
        if(!valuesToCheck.empty())
        {
            m_smallestPowerOfTwoThatFitsChildren = getChildrenRaiseToPower(getCeilOfLogarithmOfChildren(valuesToCheck.size()));
            m_startOfChildren = m_smallestPowerOfTwoThatFitsChildren-1;
            Index totalSize = m_startOfChildren + valuesToCheck.size();

            m_treeValues.resize(totalSize);
            m_treeValues.shrink_to_fit();
            std::copy(valuesToCheck.cbegin(), valuesToCheck.cend(), m_treeValues.begin()+m_startOfChildren); // copy children

            Index treeBaseLeft(m_startOfChildren);            Index treeBaseRight(totalSize-1);
            while(treeBaseLeft<treeBaseRight) // fill up parent values
            {
                if(isLeftChild(treeBaseRight)) // incomplete pair                {
                    m_treeValues[getParent(treeBaseRight)] = m_treeValues.at(treeBaseRight);
                    treeBaseRight--;
                }
                for(Index treeIndex=treeBaseLeft; treeIndex<treeBaseRight; treeIndex+=NUMBER_OF_CHILDREN) // complete pairs
                {
                    m_treeValues[getParent(treeIndex)] = m_function(m_treeValues.at(treeIndex), m_treeValues.at(treeIndex+1));
                }
                treeBaseLeft = getParent(treeBaseLeft);
                treeBaseRight = getParent(treeBaseRight);
            }
        }
    }

    void changeValueAtIndexFromBottomToTop(Index const index, Value const newValue)
    {
        // This has logN running time
        Index treeIndex(m_startOfChildren+index);
        if(treeIndex < m_treeValues.size())
        {
            m_treeValues[treeIndex] = newValue;
            if(m_treeValues.size() > 2U)
            {
                while(treeIndex>0)
                {
                    Index parentIndex(getParent(treeIndex));
                    if(isLeftChild(treeIndex))
                    {
                        m_treeValues[parentIndex] = m_function(m_treeValues.at(treeIndex), m_treeValues.at(treeIndex+1));
                    }
                    else
                    {
                        m_treeValues[parentIndex] = m_function(m_treeValues.at(treeIndex-1), m_treeValues.at(treeIndex));
                    }
                    treeIndex = parentIndex;
                }
                m_treeValues[0] = m_function(m_treeValues.at(1U), m_treeValues.at(2U));
            }
            else if(m_treeValues.size() > 1U)
            {
                m_treeValues[0] = m_treeValues.at(1U);
            }
        }
    }

    bool isLeftChild(Index const treeIndex) const
    {
        return mathHelper::isOdd(treeIndex);    }

    bool isRightChild(Index const treeIndex) const
    {
        return mathHelper::isEven(treeIndex);    }

    Index getParent(Index const treeIndex) const
    {
        return ((treeIndex+1)/NUMBER_OF_CHILDREN)-1;
    }

    Index getFirstChild(Index const parent) const
    {
        return (parent*NUMBER_OF_CHILDREN)+1;
    }

    Index getSecondChild(Index const parent) const
    {
        return (parent*NUMBER_OF_CHILDREN)+2;
    }

    Index getCeilOfLogarithmOfChildren(Index const index) const
    {
        return mathHelper::getCeilOfLogarithmForIntegers(NUMBER_OF_CHILDREN, index);    }

    Index getChildrenRaiseToPower(Index const index) const
    {
        return mathHelper::getRaiseToPowerForIntegers(NUMBER_OF_CHILDREN, index);
    }

    Index m_smallestPowerOfTwoThatFitsChildren;
    Index m_startOfChildren;
    Values m_treeValues;
    Function m_function;};

}
}
