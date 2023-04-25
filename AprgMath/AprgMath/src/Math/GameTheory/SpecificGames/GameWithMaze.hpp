#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

#include <map>

namespace alba {

namespace math {

class GameWithMaze {
public:
    // As an example, consider a game where the players move a figure in a maze.
    // Each square in the maze is either floor or wall.
    // On each turn, the player has to move the figure some number of steps left or up.
    // The winner of the game is the player who makes the last move.

    using GrundyNumberEntry = int;
    using GrundyNumberMatrix = matrix::AlbaMatrix<GrundyNumberEntry>;
    using BooleanMatrix = matrix::AlbaMatrix<bool>;
    using Coordinate = std::pair<unsigned int, unsigned int>;
    using Coordinates = std::vector<Coordinate>;
    static constexpr GrundyNumberEntry INVALID_GRUNDY_NUMBER = -1;

    GameWithMaze(BooleanMatrix const& isBlockedMatrix);

    bool hasNoMoves(Coordinate const& coordinate) const;
    UnsignedInteger getGrundyNumberAt(Coordinate const& coordinate);
    GameState getGameStateAt(Coordinate const& coordinate);
    Coordinate getOptimalNextCoordinateAt(Coordinate const& coordinate);
    Coordinate getNextCoordinateWithGrundyNumber(
        Coordinate const& coordinate, UnsignedInteger const& targetGrundyNumber);
    std::string getString();

private:
    SetOfUnsignedIntegers getNextGrundyNumbers(Coordinate const& coordinate);
    Coordinates getNextCoordinates(Coordinate const& coordinate) const;
    void retrieveLeftCoordinates(Coordinates& retrievedCoordinates, Coordinate const& coordinate) const;
    void retrieveUpCoordinates(Coordinates& retrievedCoordinates, Coordinate const& coordinate) const;

    BooleanMatrix const& m_isBlockedMatrix;
    GrundyNumberMatrix m_grundyNumberMatrix;  // dynamic programming
};

}  // namespace math

}  // namespace alba
