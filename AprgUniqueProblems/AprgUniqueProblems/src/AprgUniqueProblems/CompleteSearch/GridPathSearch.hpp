#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba
{

class GridPathSearch
{
public:
    // Calculating the number of paths in an nxn grid from the upper-left corner to the lower-right corner such that the path visits each square exactly once.

    using Grid = matrix::AlbaMatrix<bool>;
    enum class Movement
    {
        Left,
        Right,
        Up,
        Down,
    };

    GridPathSearch(unsigned int const gridSide);

    unsigned int countPaths();

private:
    bool isLowerRightCorner(unsigned int const x, unsigned int const y);
    bool canTraverse(unsigned int const x, unsigned int const y);
    bool shouldStop(unsigned int const x, unsigned int const y, Movement const previousMovement);
    void startSearch();
    void search(unsigned int const x, unsigned int const y, Movement const previousMovement);
    void searchNextCoordinate(unsigned int const x, unsigned int const y, Movement const movement);
    unsigned int const m_gridSide;
    unsigned int const m_numberOfCells;
    unsigned int m_numberTraversedCells;
    unsigned int m_numberOfCompletePaths;
    Grid m_grid;
};

}
