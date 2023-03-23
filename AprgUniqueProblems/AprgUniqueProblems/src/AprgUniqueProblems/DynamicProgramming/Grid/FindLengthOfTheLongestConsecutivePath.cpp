#include "FindLengthOfTheLongestConsecutivePath.hpp"

using namespace std;

namespace alba
{

namespace
{
vector<pair<int, int>> columnOffsets
{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
}
FindLengthOfTheLongestConsecutivePath::FindLengthOfTheLongestConsecutivePath(
        ValueGrid const& inputGrid)
    : m_inputGrid(inputGrid)
{}

FindLengthOfTheLongestConsecutivePath::Count FindLengthOfTheLongestConsecutivePath::getLongestLengthUsingNaiveRecursion() const
{
    Count result(0);
    if(!m_inputGrid.isEmpty())
    {
        m_inputGrid.iterateAllThroughYAndThenX(
                    [&](Index const x, Index const y)
        {
            result = max(result, getLongestLengthStartingAtUsingNaiveRecursion(x, y));
        });
    }
    return result;
}

FindLengthOfTheLongestConsecutivePath::Count FindLengthOfTheLongestConsecutivePath::getLongestLengthUsingMemoizationDP() const
{
    Count result(0);
    if(!m_inputGrid.isEmpty())
    {
        CountGrid countGrid(m_inputGrid.getNumberOfColumns(), m_inputGrid.getNumberOfRows(), UNUSED_COUNT);
        m_inputGrid.iterateAllThroughYAndThenX(
                    [&](Index const x, Index const y)
        {
            result = max(result, getLongestLengthStartingAtUsingMemoizationDP(countGrid, x, y));
        });
    }
    return result;
}

FindLengthOfTheLongestConsecutivePath::Count FindLengthOfTheLongestConsecutivePath::getLongestLengthStartingAtUsingNaiveRecursion(
        Index const x,
        Index const y) const
{
    Count result(0);
    Value nextValue = m_inputGrid.getEntry(x,y)+1;

    for(auto const& neighborOffset : columnOffsets)
    {
        Index neighborX = x+neighborOffset.first, neighborY = y+neighborOffset.second;
        if(m_inputGrid.isInside(neighborX, neighborY) && m_inputGrid.getEntry(neighborX, neighborY)==nextValue)        {
            result = max(result, getLongestLengthStartingAtUsingNaiveRecursion(neighborX, neighborY));
        }
    }
    result++; // count this node
    return result;
}

FindLengthOfTheLongestConsecutivePath::Count FindLengthOfTheLongestConsecutivePath::getLongestLengthStartingAtUsingMemoizationDP(
        Index const x,
        Index const y) const
{
    Count result(0);
    if(!m_inputGrid.isEmpty())
    {
        CountGrid countGrid(m_inputGrid.getNumberOfColumns(), m_inputGrid.getNumberOfRows(), UNUSED_COUNT);
        result = getLongestLengthStartingAtUsingMemoizationDP(countGrid, x, y);
    }
    return result;
}

FindLengthOfTheLongestConsecutivePath::Count FindLengthOfTheLongestConsecutivePath::getLongestLengthStartingAtUsingMemoizationDP(
        CountGrid & countGrid,
        Index const x,
        Index const y) const
{
    Count result(countGrid.getEntry(x, y));
    if(UNUSED_COUNT == result)
    {
        result = 0;
        Value nextValue = m_inputGrid.getEntry(x,y)+1;

        for(auto const& neighborOffset : columnOffsets)
        {
            Index neighborX = x+neighborOffset.first, neighborY = y+neighborOffset.second;
            if(m_inputGrid.isInside(neighborX, neighborY) && m_inputGrid.getEntry(neighborX, neighborY)==nextValue)            {
                result = max(result, getLongestLengthStartingAtUsingNaiveRecursion(neighborX, neighborY));
            }
        }
        result++; // count this node
        countGrid.setEntry(x, y, result);
    }
    return result;
}

}
