#include "PathSumInGridInRightOrDownTraversal.hpp"

using namespace std;

namespace alba
{

PathSumInGridInRightOrDownTraversal::PathSumInGridInRightOrDownTraversal(
        Type const type,
        Grid const& gridToCheck)
    : m_gridToCheck(gridToCheck)
{
    initialize(type);
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingRecursion() const
{
    // Naive recursion approach
    Value pathSum(0);
    if(!m_gridToCheck.isEmpty())
    {
        pathSum = getBestPathSumUsingRecursion(m_gridToCheck.getNumberOfColumns()-1, m_gridToCheck.getNumberOfRows()-1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingTabularDP() const
{
    // Time Complexity of the DP implementation is O(mn) which is much better than Naive Recursive implementation.
    Value pathSum(0);
    if(!m_gridToCheck.isEmpty())
    {        Grid partialSumGrid(getPartialSumGridUsingTabularDP());
        pathSum = partialSumGrid.getEntry(partialSumGrid.getNumberOfColumns()-1, partialSumGrid.getNumberOfRows()-1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingMemoizationDP() const
{
    Value pathSum(0);
    if(!m_gridToCheck.isEmpty())
    {
        Grid partialSumGrid(m_gridToCheck.getNumberOfColumns(), m_gridToCheck.getNumberOfRows(), UNUSED_INDEX);
        pathSum = getBestPathSumUsingMemoizationDP(partialSumGrid, m_gridToCheck.getNumberOfColumns()-1, m_gridToCheck.getNumberOfRows()-1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownTraversal::Path PathSumInGridInRightOrDownTraversal::getBestPathUsingTabularDP() const
{
    Path path;
    if(!m_gridToCheck.isEmpty())    {
        Grid partialSumGrid(getPartialSumGridUsingTabularDP());
        Index x=partialSumGrid.getNumberOfColumns()-1, y=partialSumGrid.getNumberOfRows()-1;
        path = {m_gridToCheck.getEntry(x, y)};        while(true)
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
            else if(m_compareFunction(partialSumGrid.getEntry(x-1, y), partialSumGrid.getEntry(x, y-1)))
            {
                path.emplace_back(m_gridToCheck.getEntry(--x, y));
            }            else
            {
                path.emplace_back(m_gridToCheck.getEntry(x, --y));
            }        }
        reverse(path.begin(), path.end());
    }
    return path;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingRecursion(
        Index const x,
        Index const y) const
{
    // Naive recursion approach

    Value bestNeighbor(m_defaultValue);
    if(m_gridToCheck.isInside(x-1, y))
    {
        bestNeighbor = m_minMaxFunction(bestNeighbor, getBestPathSumUsingRecursion(x-1, y));
    }
    if(m_gridToCheck.isInside(x, y-1))
    {
        bestNeighbor = m_minMaxFunction(bestNeighbor, getBestPathSumUsingRecursion(x, y-1));
    }
    return m_gridToCheck.getEntry(x, y) + bestNeighbor;
}

PathSumInGridInRightOrDownTraversal::Grid PathSumInGridInRightOrDownTraversal::getPartialSumGridUsingTabularDP() const{
    Grid result(m_gridToCheck);
    result.iterateAllThroughYAndThenX([&](Index const x, Index const y)
    {
        Value bestNeighbor(m_defaultValue);
        if(result.isInside(x-1, y))
        {
            bestNeighbor = m_minMaxFunction(bestNeighbor, result.getEntry(x-1, y));
        }
        if(result.isInside(x, y-1))
        {
            bestNeighbor = m_minMaxFunction(bestNeighbor, result.getEntry(x, y-1));
        }
        result.getEntryReference(x, y) += bestNeighbor;
    });
    return result;
}

PathSumInGridInRightOrDownTraversal::Value PathSumInGridInRightOrDownTraversal::getBestPathSumUsingMemoizationDP(
        Grid & partialSumGrid,
        Index const x,
        Index const y) const{
    Value result(partialSumGrid.getEntryConstReference(x, y));
    if(UNUSED_INDEX == result)
    {
        Value bestNeighbor(m_defaultValue);
        if(m_gridToCheck.isInside(x-1, y))
        {
            bestNeighbor = m_minMaxFunction(bestNeighbor, getBestPathSumUsingMemoizationDP(partialSumGrid, x-1, y));
        }
        if(m_gridToCheck.isInside(x, y-1))
        {
            bestNeighbor = m_minMaxFunction(bestNeighbor, getBestPathSumUsingMemoizationDP(partialSumGrid, x, y-1));
        }
        result = m_gridToCheck.getEntry(x, y) + bestNeighbor;
        partialSumGrid.setEntry(x, y, result);
    }
    return result;
}

void PathSumInGridInRightOrDownTraversal::initialize(Type const type)
{
    if(Type::MinimumSum == type)
    {
        m_compareFunction = std::less_equal<Value>();
        m_minMaxFunction = [](Value const& value1, Value const& value2)
        {
            return min(value1, value2);
        };
        m_defaultValue = MAX_VALUE;
    }
    else if(Type::MaximumSum == type)
    {
        m_compareFunction = std::greater_equal<Value>();
        m_minMaxFunction = [](Value const& value1, Value const& value2)
        {
            return max(value1, value2);
        };
        m_defaultValue = MIN_VALUE;
    }
}

}