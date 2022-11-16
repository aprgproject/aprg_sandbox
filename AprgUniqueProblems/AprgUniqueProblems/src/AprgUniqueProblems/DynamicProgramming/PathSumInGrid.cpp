#include "PathSumInGrid.hpp"

using namespace std;

namespace alba
{

PathSumInGrid::PathSumInGrid(Grid const& gridToCheck)
    : m_gridToCheck(gridToCheck)
    , m_partialSumGrid(gridToCheck)
{
    calculatePartialSums();
}

PathSumInGrid::Value PathSumInGrid::getMaxSumInRightOrDownTraversal() const
{
    return m_partialSumGrid.getEntry(m_partialSumGrid.getNumberOfColumns()-1, m_partialSumGrid.getNumberOfRows()-1);
}

PathSumInGrid::Path PathSumInGrid::getMaxPathInRightOrDownTraversal() const
{
    unsigned int x=m_partialSumGrid.getNumberOfColumns()-1, y=m_partialSumGrid.getNumberOfRows()-1;
    Path path{m_gridToCheck.getEntry(x, y)};
    bool isNextXInside(true), isNextYInside(true);
    while(true)
    {
        isNextXInside = m_partialSumGrid.isInside(x-1, y);
        isNextYInside = m_partialSumGrid.isInside(x, y-1);
        if(!isNextXInside && !isNextYInside)
        {
            break;
        }
        else if(!isNextXInside)
        {
            path.emplace_back(m_gridToCheck.getEntry(x, y-1));
            y--;
        }
        else if(!isNextYInside)
        {
            path.emplace_back(m_gridToCheck.getEntry(x-1, y));
            x--;
        }
        else
        {
            if(m_partialSumGrid.getEntry(x-1, y) >= m_partialSumGrid.getEntry(x, y-1))
            {
                path.emplace_back(m_gridToCheck.getEntry(x-1, y));
                x--;
            }
            else
            {
                path.emplace_back(m_gridToCheck.getEntry(x, y-1));
                y--;
            }
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

void PathSumInGrid::calculatePartialSums()
{
    m_partialSumGrid.iterateAllThroughYAndThenX([&](unsigned int x, unsigned int y)
    {
        Value maxNeighbor=0;
        if(m_partialSumGrid.isInside(x-1, y))
        {
            maxNeighbor = max(maxNeighbor, m_partialSumGrid.getEntry(x-1, y));
        }
        if(m_partialSumGrid.isInside(x, y-1))
        {
            maxNeighbor = max(maxNeighbor, m_partialSumGrid.getEntry(x, y-1));
        }
        m_partialSumGrid.getEntryReference(x, y) += maxNeighbor;
    });
}

}
