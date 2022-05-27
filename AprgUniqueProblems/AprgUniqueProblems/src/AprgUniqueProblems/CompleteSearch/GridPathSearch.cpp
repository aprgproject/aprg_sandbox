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

bool GridPathSearch::isLowerRightCorner(unsigned int const x, unsigned int const y)
{
    return x == m_grid.getNumberOfColumns()-1 && y == m_grid.getNumberOfRows()-1; // lower-right corner
}

bool GridPathSearch::canTraverse(unsigned int const x, unsigned int const y)
{
    return m_grid.isInside(x, y) && !m_grid.getEntry(x, y);
}

bool GridPathSearch::shouldStop(unsigned int const x, unsigned int const y, Movement const previousMovement)
{
    // Optimization 3: If the path touches a wall and can turn either left or right, the grid splits into two parts that contain unvisited squares.
    // Optimization 4: The idea of Optimization 3 can be generalized:
    // if the path cannot continue forward but can turn either left or right, the grid splits into two parts that both contain unvisited squares.

    if(Movement::Left == previousMovement)
    {
        if(!canTraverse(x-1, y) && canTraverse(x, y-1) && canTraverse(x, y+1))
        {
            return true;
        }
    }
    else if(Movement::Right == previousMovement)
    {
        if(!canTraverse(x+1, y) && canTraverse(x, y-1) && canTraverse(x, y+1))
        {
            return true;
        }
    }
    else if(Movement::Up == previousMovement)
    {
        if(!canTraverse(x, y-1) && canTraverse(x-1, y) && canTraverse(x+1, y))
        {
            return true;
        }
    }
    else if(Movement::Down == previousMovement)
    {
        if(!canTraverse(x, y+1) && canTraverse(x-1, y) && canTraverse(x+1, y))
        {
            return true;
        }
    }
    return false;
}
void GridPathSearch::search()
{
    // Optimization 1: In any solution, we first move one step down or right.    // There are always two paths that are symmetric about the diagonal of the grid after the first step.
    // Hence, we can decide that we always first move one step down (or right), and finally multiply the number of solutions by two.

    m_numberTraversedCells=2;
    m_grid.setEntry(0U, 0U, true);
    m_grid.setEntry(1U, 0U, true); // lets pick right

    search(1U, 0U, Movement::Right);

    m_numberOfCompletePaths*=2; // multiply by 2 (optimization 1)
}

void GridPathSearch::search(unsigned int const x, unsigned int const y, Movement const previousMovement)
{
    if(m_numberTraversedCells == m_numberOfCells)
    {
        if(isLowerRightCorner(x, y)) // lower-right corner
        {
            m_numberOfCompletePaths++;
        }
    }
    else if(!isLowerRightCorner(x, y))
    {
        // Optimization 2: If the path reaches the lower-right square before it has visited all other squares of the grid,
        // it is clear that it will not be possible to complete the solution.

        if(!shouldStop(x, y, previousMovement))
        {
            searchNextCoordinate(x-1, y, Movement::Left);
            searchNextCoordinate(x+1, y, Movement::Right);
            searchNextCoordinate(x, y-1, Movement::Up);
            searchNextCoordinate(x, y+1, Movement::Down);
        }
    }
}

void GridPathSearch::searchNextCoordinate(unsigned int const x, unsigned int const y, Movement const movement)
{
    if(canTraverse(x, y))
    {
        m_numberTraversedCells++;
        m_grid.setEntry(x, y, true);
        search(x, y, movement);
        m_grid.setEntry(x, y, false);
        m_numberTraversedCells--;
    }
}
}