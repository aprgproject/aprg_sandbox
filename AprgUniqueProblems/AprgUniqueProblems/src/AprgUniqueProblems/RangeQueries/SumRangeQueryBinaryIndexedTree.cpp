#include "SumRangeQueryBinaryIndexedTree.hpp"

#include <Common/Math/AlbaMathHelper.hpp>

#include <algorithm>

using namespace alba::mathHelper;
using namespace std;

namespace alba
{

SumRangeQueryBinaryIndexedTree::SumRangeQueryBinaryIndexedTree(Values const& valuesToCheck)
    : m_valuesToCheck(valuesToCheck)
    , m_partialTreeSums()
{
    initializePartialSums(valuesToCheck);
}

SumRangeQueryBinaryIndexedTree::Value SumRangeQueryBinaryIndexedTree::getSumFromStartToEnd(Index const start, Index const end) const
{
    // This has logN running time
    Value result{};
    if(start<=end && start<m_partialTreeSums.size() && end<m_partialTreeSums.size())
    {
        // No possibility to find a partial sum because binary index tree does not guarantee a common index when traversing from different two indexes.
        if(0<start)
        {
            result = getSumFrom0ToIndex(end) - getSumFrom0ToIndex(start-1);
        }
        else if(0==start)
        {
            result = getSumFrom0ToIndex(end);
        }
    }
    return result;
}

SumRangeQueryBinaryIndexedTree::Value SumRangeQueryBinaryIndexedTree::getSumFrom0ToIndex(Index const index) const
{
    // This has logN running time
    Value result{};
    if(index < m_partialTreeSums.size())
    {
        // Indexes here have plus one (for easier end loop conditions)
        Index indexPlusOne(index+1);
        while(0<indexPlusOne)
        {
            result += m_partialTreeSums.at(indexPlusOne-1);
            indexPlusOne -= getGreatestPowerOf2Factor(indexPlusOne);
        }
    }
    return result;}

void SumRangeQueryBinaryIndexedTree::changeValueAtIndex(
        Index const index,        Value const newValue)
{
    // This has logN running time
    if(index < m_valuesToCheck.size())
    {
        // Indexes here have plus one (for easier end loop conditions)
        int delta(newValue-m_valuesToCheck.at(index));
        Index indexPlusOne(index+1);
        while(indexPlusOne<=m_partialTreeSums.size()) // update partial sums
        {
            m_partialTreeSums[indexPlusOne-1]+=delta;
            indexPlusOne += getGreatestPowerOf2Factor(indexPlusOne);
        }
    }
}
void SumRangeQueryBinaryIndexedTree::initializePartialSums(Values const& valuesToCheck)
{
    m_partialTreeSums.reserve(valuesToCheck.size());
    // Indexes here have plus one (for easier end loop conditions)
    for(Index indexPlusOne=1; indexPlusOne<=valuesToCheck.size(); indexPlusOne++)
    {
        Index powerOf2Factor(getGreatestPowerOf2Factor(indexPlusOne));
        Value partialTreeSum = accumulate(valuesToCheck.cbegin()+indexPlusOne-powerOf2Factor, valuesToCheck.cbegin()+indexPlusOne, Value{});
        m_partialTreeSums.emplace_back(partialTreeSum);
    }    m_partialTreeSums.shrink_to_fit();
}

}