#include "SumRangeQuerySegmentTree.hpp"

#include <Common/Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

SumRangeQuerySegmentTree::SumRangeQuerySegmentTree(Values const& valuesToCheck)
    : m_startOfChildren(0U)
    , m_treeValues()
{
    initialize(valuesToCheck);
}

SumRangeQuerySegmentTree::Value SumRangeQuerySegmentTree::getSumFromStartToEnd(Index const start, Index const end) const
{
    // This has logN running time
    Value result{};
    Index first(m_startOfChildren+start);
    Index last(m_startOfChildren+end);
    if(first<=last && first<m_treeValues.size() && last<m_treeValues.size())
    {
        while(first < last)
        {
            if(isRightChild(first))
            {
                result += m_treeValues.at(first++); // move to next value (right) because current value is added
            }
            if(isLeftChild(last))
            {
                result += m_treeValues.at(last--); // move to next value (left) because current value is added
            }
            first = getParent(first);
            last = getParent(last);
        }
        if(first == last) // add value if it ends on the same place
        {
            result += m_treeValues.at(first);
        }    }
    return result;
}
void SumRangeQuerySegmentTree::changeValueAtIndex(
        Index const index,
        Value const newValue)
{
    // This has logN running time
    Index treeIndex(m_startOfChildren+index);
    m_treeValues[treeIndex] = newValue;

    while(treeIndex>0)
    {
        Index parentIndex(getParent(treeIndex));
        if(isLeftChild(treeIndex))
        {
            m_treeValues[parentIndex] = m_treeValues.at(treeIndex) + m_treeValues.at(treeIndex+1);
        }
        else
        {
            m_treeValues[parentIndex] = m_treeValues.at(treeIndex-1) + m_treeValues.at(treeIndex);
        }
        treeIndex = parentIndex;
    }
    m_treeValues[0] = m_treeValues.at(1) + m_treeValues.at(2);
}

bool SumRangeQuerySegmentTree::isLeftChild(Index const treeIndex) const
{
    return isOdd(treeIndex);
}

bool SumRangeQuerySegmentTree::isRightChild(Index const treeIndex) const
{
    return isEven(treeIndex);
}

SumRangeQuerySegmentTree::Index SumRangeQuerySegmentTree::getParent(Index const treeIndex) const
{
    return ((treeIndex+1)/NUMBER_OF_CHILDREN)-1;
}

SumRangeQuerySegmentTree::Index SumRangeQuerySegmentTree::getCielOfLogarithmOfChildren(Index const value) const
{
    return getIntegerAfterCeilingOfDoubleValue<Index>(getLogarithm(NUMBER_OF_CHILDREN, value));
}

SumRangeQuerySegmentTree::Index SumRangeQuerySegmentTree::getChildrenRaiseToPower(Index const value) const
{
    return getIntegerAfterRoundingADoubleValue<Index>(pow(NUMBER_OF_CHILDREN, value));
}

void SumRangeQuerySegmentTree::initialize(Values const& valuesToCheck)
{
    if(!valuesToCheck.empty())
    {
        Index parentSize = getChildrenRaiseToPower(getCielOfLogarithmOfChildren(valuesToCheck.size()))-1;
        Index totalSize = parentSize + valuesToCheck.size();

        m_treeValues.resize(totalSize);
        m_treeValues.shrink_to_fit();
        m_startOfChildren = parentSize;
        copy(valuesToCheck.cbegin(), valuesToCheck.cend(), m_treeValues.begin()+m_startOfChildren); // copy children

        Index first(m_startOfChildren);
        Index last(totalSize-1);
        while(first<last) // fill up parent values
        {
            if(isLeftChild(last)) // incomplete pair
            {
                m_treeValues[getParent(last)] = m_treeValues.at(last);
                last--;
            }
            for(Index treeIndex=first; treeIndex<last; treeIndex+=NUMBER_OF_CHILDREN) // complete pairs
            {
                m_treeValues[getParent(treeIndex)] = m_treeValues.at(treeIndex) + m_treeValues.at(treeIndex+1);
            }
            first = getParent(first);
            last = getParent(last);
        }
    }
}

}
