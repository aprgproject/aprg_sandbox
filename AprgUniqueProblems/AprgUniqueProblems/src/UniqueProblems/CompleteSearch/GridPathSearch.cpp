#include "GridPathSearch.hpp"

namespace alba {

GridPathSearch::GridPathSearch(int const gridSide)
    : m_gridSide(gridSide),
      m_numberOfCells(gridSide * gridSide),
      m_numberTraversedCells(0),
      m_numberOfCompletePaths(0),
      m_grid()  // just initialize this when searching
{}

int GridPathSearch::countPaths() {
    startSearch();
    return m_numberOfCompletePaths;
}

bool GridPathSearch::isLowerRightCorner(int const x, int const y) {
    // lower-right corner
    return x == static_cast<int>(m_grid.getNumberOfColumns()) - 1 &&
           y == static_cast<int>(m_grid.getNumberOfRows()) - 1;
}

bool GridPathSearch::canTraverse(int const x, int const y) { return m_grid.isInside(x, y) && !m_grid.getEntry(x, y); }

bool GridPathSearch::shouldStop(int const x, int const y, Movement const previousMovement) {
    // Optimization 3: If the path touches a wall and can turn either left or right, the grid splits into two parts that
    // contain unvisited squares. Optimization 4: The idea of Optimization 3 can be generalized: if the path cannot
    // continue forward but can turn either left or right, the grid splits into two parts that both contain unvisited
    // squares.

    if (Movement::Left == previousMovement) {
        if (!canTraverse(x - 1, y) && canTraverse(x, y - 1) && canTraverse(x, y + 1)) {
            return true;
        }
    } else if (Movement::Right == previousMovement) {
        if (!canTraverse(x + 1, y) && canTraverse(x, y - 1) && canTraverse(x, y + 1)) {
            return true;
        }
    } else if (Movement::Up == previousMovement) {
        if (!canTraverse(x, y - 1) && canTraverse(x - 1, y) && canTraverse(x + 1, y)) {
            return true;
        }
    } else if (Movement::Down == previousMovement) {
        if (!canTraverse(x, y + 1) && canTraverse(x - 1, y) && canTraverse(x + 1, y)) {
            return true;
        }
    }
    return false;
}

void GridPathSearch::startSearch() {
    // Optimization 1: In any solution, we first move one step down or right.
    // There are always two paths that are symmetric about the diagonal of the grid after the first step.
    // Hence, we can decide that we always first move one step down (or right), and finally multiply the number of
    // solutions by two.

    m_numberOfCompletePaths = 0;
    m_numberTraversedCells = 2;
    m_grid.clearAndResize(m_gridSide, m_gridSide);
    m_grid.setEntry(0, 0, true);
    m_grid.setEntry(1, 0, true);  // lets pick right

    search(1, 0, Movement::Right);

    m_numberOfCompletePaths *= 2;  // multiply by 2 (optimization 1)
}

void GridPathSearch::search(int const x, int const y, Movement const previousMovement) {
    if (m_numberTraversedCells == m_numberOfCells) {
        if (isLowerRightCorner(x, y))  // lower-right corner
        {
            m_numberOfCompletePaths++;
        }
    } else if (!isLowerRightCorner(x, y)) {
        // Optimization 2: If the path reaches the lower-right square before it has visited all other squares of the
        // grid, it is clear that it will not be possible to complete the solution.

        if (!shouldStop(x, y, previousMovement)) {
            searchNextCoordinate(x - 1, y, Movement::Left);
            searchNextCoordinate(x + 1, y, Movement::Right);
            searchNextCoordinate(x, y - 1, Movement::Up);
            searchNextCoordinate(x, y + 1, Movement::Down);
        }
    }
}

void GridPathSearch::searchNextCoordinate(int const x, int const y, Movement const movement) {
    if (canTraverse(x, y)) {
        m_numberTraversedCells++;
        m_grid.setEntry(x, y, true);
        search(x, y, movement);
        m_grid.setEntry(x, y, false);
        m_numberTraversedCells--;
    }
}

}  // namespace alba
