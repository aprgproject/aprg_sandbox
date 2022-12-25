#include "PathSumInGridInRightOrDownWithDiagonalTraversal.hpp"

using namespace std;

namespace alba
{

PathSumInGridInRightOrDownWithDiagonalTraversal::PathSumInGridInRightOrDownWithDiagonalTraversal(
        Type const type,
        Grid const& gridToCheck)
    : m_gridToCheck(gridToCheck)
{
    initialize(type);
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Value PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingRecursion() const
{
    // Naive recursion approach

    Value pathSum(0);
    if(!m_gridToCheck.isEmpty())
    {
        pathSum = getBestPathSumUsingRecursion(m_gridToCheck.getNumberOfColumns()-1, m_gridToCheck.getNumberOfRows()-1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Value PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingTabularDP() const
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

PathSumInGridInRightOrDownWithDiagonalTraversal::Value PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingMemoizationDP() const
{
    Value pathSum(0);
    if(!m_gridToCheck.isEmpty())
    {
        Grid partialSumGrid(m_gridToCheck.getNumberOfColumns(), m_gridToCheck.getNumberOfRows(), UNUSED_VALUE);
        pathSum = getBestPathSumUsingMemoizationDP(partialSumGrid, m_gridToCheck.getNumberOfColumns()-1, m_gridToCheck.getNumberOfRows()-1);
    }
    return pathSum;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Path PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathUsingTabularDP() const
{
    Path path;
    if(!m_gridToCheck.isEmpty())
    {
        Grid partialSumGrid(getPartialSumGridUsingTabularDP());
        Index x=partialSumGrid.getNumberOfColumns()-1, y=partialSumGrid.getNumberOfRows()-1;
        path = {m_gridToCheck.getEntry(x, y)};
        while(true)
        {
            if(x==0 && y==0)
            {
                break;
            }
            else if(x==0)
            {
                path.emplace_back(m_gridToCheck.getEntry(x, --y));
            }
            else if(y==0)
            {
                path.emplace_back(m_gridToCheck.getEntry(--x, y));
            }
            else
            {
                Value bestNeighbor = m_minMaxFunction(
                            m_minMaxFunction(partialSumGrid.getEntry(x-1, y), partialSumGrid.getEntry(x, y-1)),
                            partialSumGrid.getEntry(x-1, y-1));
                if(bestNeighbor == partialSumGrid.getEntry(x-1, y))
                {
                    path.emplace_back(m_gridToCheck.getEntry(--x, y));
                }
                else if(bestNeighbor == partialSumGrid.getEntry(x, y-1))
                {
                    path.emplace_back(m_gridToCheck.getEntry(x, --y));
                }
                else if(bestNeighbor == partialSumGrid.getEntry(x-1, y-1))
                {
                    path.emplace_back(m_gridToCheck.getEntry(--x, --y));
                }
            }
        }
        reverse(path.begin(), path.end());
    }
    return path;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Value PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingRecursion(
        Index const x,
        Index const y) const
{
    // Naive recursion approach


    Value result(m_gridToCheck.getEntry(x, y));
    if(!(x==0 && y==0))
    {
        if(x==0)
        {
            result += getBestPathSumUsingRecursion(x, y-1);
        }
        else if(y==0)
        {
            result += getBestPathSumUsingRecursion(x-1, y);
        }
        else
        {
            // diagonal is included
            result += m_minMaxFunction(
                        m_minMaxFunction(getBestPathSumUsingRecursion(x-1, y), getBestPathSumUsingRecursion(x, y-1)),
                        getBestPathSumUsingRecursion(x-1, y-1));
        }
    }
    return result;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Grid PathSumInGridInRightOrDownWithDiagonalTraversal::getPartialSumGridUsingTabularDP() const
{
    Grid result(m_gridToCheck);
    for(Index x=1; x<result.getNumberOfColumns(); x++)  // first row has only left neighbors
    {
        result.getEntryReference(x, 0) += result.getEntry(x-1, 0);
    }
    for(Index y=1; y<result.getNumberOfRows(); y++) // first column has only up neighbors
    {
        result.getEntryReference(0, y) += result.getEntry(0, y-1);
    }
    for(Index x=1; x<result.getNumberOfColumns(); x++) // the rest of the matrix
    {
        for(Index y=1; y<result.getNumberOfRows(); y++)
        {
            // diagonal is included
            result.getEntryReference(x, y)
                    += m_minMaxFunction(
                        m_minMaxFunction(result.getEntry(x-1, y), result.getEntry(x, y-1)), result.getEntry(x-1, y-1));
        }
    }
    return result;
}

PathSumInGridInRightOrDownWithDiagonalTraversal::Value PathSumInGridInRightOrDownWithDiagonalTraversal::getBestPathSumUsingMemoizationDP(
        Grid & partialSumGrid,
        Index const x,
        Index const y) const
{
    Value result(partialSumGrid.getEntry(x, y));
    if(UNUSED_VALUE == result)
    {
        result = m_gridToCheck.getEntry(x, y);
        if(!(x==0 && y==0))
        {
            if(x==0)
            {
                result += getBestPathSumUsingMemoizationDP(partialSumGrid, x, y-1);
            }
            else if(y==0)
            {
                result += getBestPathSumUsingMemoizationDP(partialSumGrid, x-1, y);
            }
            else
            {
                result += m_minMaxFunction(
                            m_minMaxFunction(getBestPathSumUsingMemoizationDP(partialSumGrid, x-1, y),
                                             getBestPathSumUsingMemoizationDP(partialSumGrid, x, y-1)),
                            getBestPathSumUsingMemoizationDP(partialSumGrid, x-1, y-1));
            }
        }
        partialSumGrid.setEntry(x, y, result);
    }
    return result;
}

void PathSumInGridInRightOrDownWithDiagonalTraversal::initialize(Type const type)
{
    if(Type::MinimumSum == type)
    {
        m_compareFunction = less_equal<Value>();
        m_minMaxFunction = [](Value const& value1, Value const& value2)
        {
            return min(value1, value2);
        };
    }
    else if(Type::MaximumSum == type)
    {
        m_compareFunction = greater_equal<Value>();
        m_minMaxFunction = [](Value const& value1, Value const& value2)
        {
            return max(value1, value2);
        };
    }
}

}
