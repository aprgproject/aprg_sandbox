#include "PathSumInGridInRightOrDownTraversal.hpp"

using namespace std;

namespace alba
{

PathSumInGridInRightOrDownTraversal::PathSumInGridInRightOrDownTraversal(Grid const& gridToCheck)
    : m_gridToCheck(gridToCheck)
{}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getMaxPathSumUsingRecursion() const
{
    // Naive recursion approach

    Value pathSum(0);
    if(!m_gridToCheck.isEmpty())
    {
        pathSum = getMaxPathSumUsingRecursion(m_gridToCheck.getNumberOfColumns()-1, m_gridToCheck.getNumberOfRows()-1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getMaxPathSumUsingTabularDP() const
{
    // Time Complexity of the DP implementation is O(mn) which is much better than Naive Recursive implementation.

    Value pathSum(0);
    if(!m_gridToCheck.isEmpty())
    {
        Grid partialSumGrid(getPartialSumGridUsingTabularDP());
        pathSum = partialSumGrid.getEntry(partialSumGrid.getNumberOfColumns()-1, partialSumGrid.getNumberOfRows()-1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getMaxPathSumUsingMemoizationDP() const
{
    Value pathSum(0);
    if(!m_gridToCheck.isEmpty())
    {
        Grid partialSumGrid(m_gridToCheck.getNumberOfColumns(), m_gridToCheck.getNumberOfRows(), UNUSED_INDEX);
        pathSum = getMaxPathSumUsingMemoizationDP(partialSumGrid, m_gridToCheck.getNumberOfColumns()-1, m_gridToCheck.getNumberOfRows()-1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownTraversal::Path PathSumInGridInRightOrDownTraversal::getMaxPathUsingTabularDP() const
{
    Path path;
    if(!m_gridToCheck.isEmpty())
    {
        Grid partialSumGrid(getPartialSumGridUsingTabularDP());
        Index x=partialSumGrid.getNumberOfColumns()-1, y=partialSumGrid.getNumberOfRows()-1;
        path = {m_gridToCheck.getEntry(x, y)};
        while(true)
        {
            bool isNextXInside = partialSumGrid.isInside(x-1, y);
            bool isNextYInside = partialSumGrid.isInside(x, y-1);
            if(!isNextXInside && !isNextYInside)
            {
                break;
            }
            else if(!isNextXInside)
            {
                path.emplace_back(m_gridToCheck.getEntry(x, --y));
            }
            else if(!isNextYInside)
            {
                path.emplace_back(m_gridToCheck.getEntry(--x, y));
            }
            else if(partialSumGrid.getEntry(x-1, y) >= partialSumGrid.getEntry(x, y-1))
            {
                path.emplace_back(m_gridToCheck.getEntry(--x, y));
            }
            else
            {
                path.emplace_back(m_gridToCheck.getEntry(x, --y));
            }
        }
        reverse(path.begin(), path.end());
    }
    return path;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getMaxPathSumUsingRecursion(
        Index const x,
        Index const y) const
{
    // Naive recursion approach

    Value maxNeighbor(0);
    if(m_gridToCheck.isInside(x-1, y))
    {
        maxNeighbor = max(maxNeighbor, getMaxPathSumUsingRecursion(x-1, y));
    }
    if(m_gridToCheck.isInside(x, y-1))
    {
        maxNeighbor = max(maxNeighbor, getMaxPathSumUsingRecursion(x, y-1));
    }
    return m_gridToCheck.getEntry(x, y) + maxNeighbor;
}

PathSumInGridInRightOrDownTraversal::Grid PathSumInGridInRightOrDownTraversal::getPartialSumGridUsingTabularDP() const
{
    Grid result(m_gridToCheck);
    result.iterateAllThroughYAndThenX([&](Index const x, Index const y)
    {
        Value maxNeighbor(0);
        if(result.isInside(x-1, y))
        {
            maxNeighbor = max(maxNeighbor, result.getEntry(x-1, y));
        }
        if(result.isInside(x, y-1))
        {
            maxNeighbor = max(maxNeighbor, result.getEntry(x, y-1));
        }
        result.getEntryReference(x, y) += maxNeighbor;
    });
    return result;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getMaxPathSumUsingMemoizationDP(
        Grid & partialSumGrid,
        Index const x,
        Index const y) const
{
    Value result(partialSumGrid.getEntryConstReference(x, y));
    if(UNUSED_INDEX == result)
    {
        Value maxNeighbor(0);
        if(m_gridToCheck.isInside(x-1, y))
        {
            maxNeighbor = max(maxNeighbor, getMaxPathSumUsingMemoizationDP(partialSumGrid, x-1, y));
        }
        if(m_gridToCheck.isInside(x, y-1))
        {
            maxNeighbor = max(maxNeighbor, getMaxPathSumUsingMemoizationDP(partialSumGrid, x, y-1));
        }
        result = m_gridToCheck.getEntry(x, y) + maxNeighbor;
        partialSumGrid.setEntry(x, y, result);
    }
    return result;
}

}
