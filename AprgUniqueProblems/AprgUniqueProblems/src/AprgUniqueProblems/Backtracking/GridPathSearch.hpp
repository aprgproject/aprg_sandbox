#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba
{

class GridPathSearch
{
public:
    // Calculating the number of paths in an nxn grid from the upper-left corner to the lower-right corner such that the path visits each square exactly once.

    using Grid = matrix::AlbaMatrix<bool>;
    struct Position
    {
        unsigned int const x;
        unsigned int const y;
    };

    GridPathSearch(unsigned int const gridSide);

    unsigned int countPaths();

private:
    bool isLowerRightCorner(Position const& position);
    bool canTraverse(Position const& position);
    bool shouldStop(Position const& previous, Position const& current);
    void search();
    void search(Position const& previous, Position const& current);
    void searchNextCoordinate(Position const& current, Position const& next);
    unsigned int m_gridSide;
    unsigned int m_numberOfCells;
    unsigned int m_numberTraversedCells;
    unsigned int m_numberOfCompletePaths;
    Grid m_grid;
};

}