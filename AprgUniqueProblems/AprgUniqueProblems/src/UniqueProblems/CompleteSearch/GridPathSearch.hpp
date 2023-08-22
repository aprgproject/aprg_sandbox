#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

namespace alba {

class GridPathSearch {
public:
    // Calculating the number of paths in an nxn grid from the upper-left corner to the lower-right corner such that the
    // path visits each square exactly once.

    using Grid = matrix::AlbaMatrix<bool>;
    enum class Movement {
        Left,
        Right,
        Up,
        Down,
    };

    GridPathSearch(int const gridSide);

    int countPaths();

private:
    bool isLowerRightCorner(int const x, int const y);
    bool canTraverse(int const x, int const y);
    bool shouldStop(int const x, int const y, Movement const previousMovement);
    void startSearch();
    void search(int const x, int const y, Movement const previousMovement);
    void searchNextCoordinate(int const x, int const y, Movement const movement);
    int const m_gridSide;
    int const m_numberOfCells;
    int m_numberTraversedCells;
    int m_numberOfCompletePaths;
    Grid m_grid;
};

}  // namespace alba
