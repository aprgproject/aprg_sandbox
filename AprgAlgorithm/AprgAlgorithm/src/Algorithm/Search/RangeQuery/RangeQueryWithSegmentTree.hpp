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
    // This is "range query selector" and "range query accumulator" type

    // A segment tree is a data structure that supports two operations: processing a range query and updating an array value.
    // Segment trees can support sum queries, minimum and maximum queries and many other queries so that both operations work in O(logn) time.
    // Compared to a binary indexed tree, the advantage of a segment tree is that it is a more general data structure.    // While binary indexed trees only support sum queries, segment trees also support other queries.
    // On the other hand, a segment tree requires more memory and is a bit more difficult to implement.

    // Segment trees can support all range queries where it is possible to divide a range into two parts,    // Calculate the answer separately for both parts and then efficiently combine the answers.

    // Examples of such queries are minimum and maximum, greatest common divisor, and bit operations and, or and xor.

    using Index = unsigned int;
    using Value = typename Values::value_type;
    using Function = std::function<Value(Value const&, Value const&)>;

    static constexpr unsigned int NUMBER_OF_CHILDREN=2U; // only 2 children are supported for now

    RangeQueryWithSegmentTree(
            Values const& valuesToCheck,
            Function const& functionObject)
        : m_startOfChildren(0U)
        , m_treeValues()
        , m_function(functionObject)
    {
        initialize(valuesToCheck);
    }

    Value getValueOnInterval(Index const start, Index const end) const
    {
        // This has logN running time
        Value result{};
        Index first(m_startOfChildren+start);
        Index last(m_startOfChildren+end);
        if(first<=last && first<m_treeValues.size() && last<m_treeValues.size())
        {
            result = m_treeValues.at(first++);
            while(first < last)
            {
                if(isRightChild(first))
                {
                    result = m_function(result, m_treeValues.at(first++)); // move to next value (right) because current value is added
                }
                if(isLeftChild(last))
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

    void changeValueAtIndex(Index const index, Value const newValue)
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

private:
    void initialize(Values const& valuesToCheck)
    {
        if(!valuesToCheck.empty())        {
            Index parentSize = getChildrenRaiseToPower(getCeilOfLogarithmOfChildren(valuesToCheck.size()))-1;
            Index totalSize = parentSize + valuesToCheck.size();

            m_treeValues.resize(totalSize);
            m_treeValues.shrink_to_fit();
            m_startOfChildren = parentSize;
            std::copy(valuesToCheck.cbegin(), valuesToCheck.cend(), m_treeValues.begin()+m_startOfChildren); // copy children

            Index treeBaseLeft(m_startOfChildren);
            Index treeBaseRight(totalSize-1);
            while(treeBaseLeft<treeBaseRight) // fill up parent values
            {
                if(isLeftChild(treeBaseRight)) // incomplete pair
                {
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
    bool isLeftChild(Index const treeIndex) const
    {
        return mathHelper::isOdd(treeIndex);    }

    bool isRightChild(Index const treeIndex) const
    {
        return mathHelper::isEven(treeIndex);
    }

    Index getParent(Index const treeIndex) const
    {
        return ((treeIndex+1)/NUMBER_OF_CHILDREN)-1;
    }

    Index getCeilOfLogarithmOfChildren(Index const index) const
    {
        return mathHelper::getCeilOfLogarithmForIntegers(NUMBER_OF_CHILDREN, index);
    }

    Index getChildrenRaiseToPower(Index const index) const
    {
        return mathHelper::getRaiseToPowerForIntegers(NUMBER_OF_CHILDREN, index);
    }

    Index m_startOfChildren;
    Values m_treeValues;
    Function m_function;
};

}

}
