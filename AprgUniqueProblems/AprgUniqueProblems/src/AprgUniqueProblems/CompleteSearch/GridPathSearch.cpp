#include "GridPathSearch.hpp"

namespace alba
{

GridPathSearch::GridPathSearch(
        unsigned int const gridSide)
    : m_gridSide(gridSide)
    , m_numberOfCells(gridSide*gridSide)
    , m_numberTraversedCells(0U)
    , m_numberOfCompletePaths(0U)
    , m_grid(gridSide, gridSide)
{}

unsigned int GridPathSearch::countPaths()
{
    search();
    return m_numberOfCompletePaths;
}

bool GridPathSearch::isLowerRightCorner(Position const& position)
{
    return position.x == m_grid.getNumberOfColumns()-1 && position.y == m_grid.getNumberOfRows()-1; // lower-right corner
}

bool GridPathSearch::canTraverse(Position const& position)
{
    return m_grid.isInside(position.x, position.y) && !m_grid.getEntry(position.x, position.y);
}

bool GridPathSearch::shouldStop(Position const& previous, Position const& current)
{
    // Optimization 3: If the path touches a wall and can turn either left or right, the grid splits into two parts that contain unvisited squares.
    // Optimization 4: The idea of Optimization 3 can be generalized:
    // if the path cannot continue forward but can turn either left or right, the grid splits into two parts that both contain unvisited squares.

    bool isFromLeftAndCantRight = previous.x == current.x-1 && previous.y == current.y && !canTraverse(Position{current.x+1, current.y});
    bool isFromRightAndCantLeft = previous.x == current.x+1 && previous.y == current.y && !canTraverse(Position{current.x-1, current.y});
    if(isFromLeftAndCantRight || isFromRightAndCantLeft) // cannot advance in x
    {
        bool areUpAndDownNeighborsFree = canTraverse(Position{current.x, current.y-1}) && canTraverse(Position{current.x, current.y+1});
        if(areUpAndDownNeighborsFree) // both y neighbors are available
        {
            return true;
        }
    }
    bool isFromUpAndCantDown = previous.x == current.x && previous.y == current.y-1 && !canTraverse(Position{current.x, current.y+1});
    bool isFromDownAndCantUp = previous.x == current.x && previous.y == current.y+1 && !canTraverse(Position{current.x, current.y-1});
    if(isFromUpAndCantDown || isFromDownAndCantUp) // cannot advance in y
    {
        bool isLeftAndRightNeighborsFree = canTraverse(Position{current.x-1, current.y}) && canTraverse(Position{current.x+1, current.y});
        if(isLeftAndRightNeighborsFree) // both x neighbors are available
        {
            return true;
        }
    }
    return false;
}

void GridPathSearch::search()
{
    // Optimization 1: In any solution, we first move one step down or right.
    // There are always two paths that are symmetric about the diagonal of the grid after the first step.
    // Hence, we can decide that we always first move one step down (or right), and finally multiply the number of solutions by two.

    m_numberTraversedCells=2;
    m_grid.setEntry(0U, 0U, true);
    m_grid.setEntry(1U, 0U, true); // lets pick right

    search(Position{0U, 0U}, Position{1U, 0U});

    m_numberOfCompletePaths*=2; // multiply by 2 (optimization 1)
}

void GridPathSearch::search(Position const& previous, Position const& current)
{
    if(m_numberTraversedCells == m_numberOfCells)
    {
        if(isLowerRightCorner(current)) // lower-right corner
        {
            m_numberOfCompletePaths++;
        }
    }
    else if(!isLowerRightCorner(current))
    {
        // Optimization 2: If the path reaches the lower-right square before it has visited all other squares of the grid,
        // it is clear that it will not be possible to complete the solution.

        if(!shouldStop(previous, current))
        {
            searchNextCoordinate(current, Position{current.x-1, current.y});
            searchNextCoordinate(current, Position{current.x, current.y-1});
            searchNextCoordinate(current, Position{current.x+1, current.y});
            searchNextCoordinate(current, Position{current.x, current.y+1});
        }
    }
}

void GridPathSearch::searchNextCoordinate(Position const& current, Position const& next)
{
    if(canTraverse(next))
    {
        m_numberTraversedCells++;
        m_grid.setEntry(next.x, next.y, true);
        search(current, next);
        m_grid.setEntry(next.x, next.y, false);
        m_numberTraversedCells--;
    }
}

}
