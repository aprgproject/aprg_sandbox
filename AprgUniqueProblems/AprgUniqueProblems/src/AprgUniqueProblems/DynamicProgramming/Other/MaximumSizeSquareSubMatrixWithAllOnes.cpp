#include "MaximumSizeSquareSubMatrixWithAllOnes.hpp"

using namespace std;

namespace alba
{

MaximumSizeSquareSubMatrixWithAllOnes::MaximumSizeSquareSubMatrixWithAllOnes(
        BooleanMatrix const& booleanMatrix)
    : m_booleanMatrix(booleanMatrix)
{}

MaximumSizeSquareSubMatrixWithAllOnes::Unit MaximumSizeSquareSubMatrixWithAllOnes::getMaximumSquareAreaUsingMemoizationDP() const
{
    // Time Complexity: O(m*n*max(m,n)) (same as iterative DP)
    // Auxiliary Space: O(m*n)

    Unit result(0);
    if(!m_booleanMatrix.isEmpty())
    {
        UnitMatrix sideMatrix(m_booleanMatrix.getNumberOfColumns(), m_booleanMatrix.getNumberOfRows(), UNUSED_UNIT);
        for(int x=static_cast<int>(sideMatrix.getNumberOfColumns()-1); x>=0; x--)        {
            for(int y=static_cast<int>(sideMatrix.getNumberOfRows()-1); y>=0; y--)
            {
                getMaximumSideUsingMemoizationDP(sideMatrix, x, y);
            }
        }

        Unit maximumSide(0);
        sideMatrix.iterateAllThroughYAndThenX([&](Index const x, Index const y)
        {
            Unit side = sideMatrix.getEntry(x, y);
            if(side != UNUSED_UNIT)
            {
                maximumSide = max(maximumSide, side);
            }
        });
        result = maximumSide*maximumSide;
    }
    return result;
}

MaximumSizeSquareSubMatrixWithAllOnes::Unit MaximumSizeSquareSubMatrixWithAllOnes::getMaximumSquareAreaUsingIterativeDP() const
{
    // Time Complexity: O(m*n*max(m,n))
    // Auxiliary Space: O(m*n)

    Unit result(0);
    if(!m_booleanMatrix.isEmpty())
    {        UnitMatrix sideMatrix(m_booleanMatrix.getNumberOfColumns(), m_booleanMatrix.getNumberOfRows());
        sideMatrix.iterateAllThroughYAndThenX([&](Index const x, Index const y)
        {
            Unit entryResult(0);
            if(x==0 || y==0)
            {
                entryResult = getUnitAt(x, y);
            }
            else if(m_booleanMatrix.getEntry(x, y))
            {
                Unit maxSideOfSmallerSquare = sideMatrix.getEntry(x-1, y-1);

                int upX = static_cast<int>(x-maxSideOfSmallerSquare);
                int leftY = static_cast<int>(y-maxSideOfSmallerSquare);

                bool areAllOnes(true);
                for(int i=static_cast<int>(x-1); areAllOnes && i>=upX; i--)
                {
                    areAllOnes = areAllOnes && m_booleanMatrix.getEntry(i, y);
                }
                for(int i=static_cast<int>(y-1); areAllOnes && i>=leftY; i--)
                {
                    areAllOnes = areAllOnes && m_booleanMatrix.getEntry(x, i);
                }
                entryResult = areAllOnes ? maxSideOfSmallerSquare+1 : 1;
            }
            sideMatrix.setEntry(x,y,entryResult);
        });

        Unit maximumSide(0);
        sideMatrix.iterateAllThroughYAndThenX([&](Index const x, Index const y)
        {
            Unit side = sideMatrix.getEntry(x, y);
            if(side != UNUSED_UNIT)
            {
                maximumSide = max(maximumSide, side);
            }
        });
        result = maximumSide*maximumSide;
    }
    return result;
}

MaximumSizeSquareSubMatrixWithAllOnes::Unit MaximumSizeSquareSubMatrixWithAllOnes::getMaximumSquareAreaUsingIterativeDPAndTimeEfficient() const
{
    // Time Complexity: O(m*n)
    // Auxiliary Space: O(m*n)

    Unit result(0);
    if(!m_booleanMatrix.isEmpty())
    {        UnitMatrix sideMatrix(m_booleanMatrix.getNumberOfColumns(), m_booleanMatrix.getNumberOfRows());

        for(Index x=0; x<m_booleanMatrix.getNumberOfColumns(); x++)
        {
            sideMatrix.setEntry(x, 0, getUnitAt(x, 0));
        }
        for(Index y=0; y<m_booleanMatrix.getNumberOfRows(); y++)
        {
            sideMatrix.setEntry(0, y, getUnitAt(0, y));
        }

        for(Index x=1; x<m_booleanMatrix.getNumberOfColumns(); x++)
        {
            for(Index y=1; y<m_booleanMatrix.getNumberOfRows(); y++)
            {
                Unit entryResult(0);
                if(m_booleanMatrix.getEntry(x, y))
                {
                    entryResult = 1 + min(min(sideMatrix.getEntry(x-1, y-1), sideMatrix.getEntry(x, y-1)), sideMatrix.getEntry(x-1, y));
                }
                sideMatrix.setEntry(x, y, entryResult);
            }
        }

        Unit maximumSide(0);
        sideMatrix.iterateAllThroughYAndThenX([&](Index const x, Index const y)
        {
            maximumSide = max(maximumSide, sideMatrix.getEntry(x, y));
        });
        result = maximumSide*maximumSide;
    }
    return result;
}

MaximumSizeSquareSubMatrixWithAllOnes::Unit MaximumSizeSquareSubMatrixWithAllOnes::getMaximumSideUsingMemoizationDP(
        UnitMatrix & sideMatrix,
        Index const x,
        Index const y) const
{
    Unit result(sideMatrix.getEntry(x, y));
    if(UNUSED_UNIT == result)
    {
        result=0;
        if(x==0 || y==0)
        {
            result = getUnitAt(x, y);
        }
        else if(m_booleanMatrix.getEntry(x, y))
        {
            Unit maxSideOfSmallerSquare = getMaximumSideUsingMemoizationDP(sideMatrix, x-1, y-1);

            int upX = static_cast<int>(x-maxSideOfSmallerSquare);
            int leftY = static_cast<int>(y-maxSideOfSmallerSquare);

            bool areAllOnes(true);
            for(int i=static_cast<int>(x-1); areAllOnes && i>=upX; i--)
            {
                areAllOnes = areAllOnes && m_booleanMatrix.getEntry(i, y);
            }
            for(int i=static_cast<int>(y-1); areAllOnes && i>=leftY; i--)
            {
                areAllOnes = areAllOnes && m_booleanMatrix.getEntry(x, i);
            }
            result = areAllOnes ? maxSideOfSmallerSquare+1 : 1;
        }
        sideMatrix.setEntry(x, y, result);
    }
    return result;
}

// inline optimization can work here because the usage belongs to same translation unit
inline MaximumSizeSquareSubMatrixWithAllOnes::Unit MaximumSizeSquareSubMatrixWithAllOnes::getUnitAt(
        Index const x,
        Index const y) const
{
    return m_booleanMatrix.getEntry(x, y) ? 1 : 0;
}

}
