#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>
#include <Math/GameTheory/Common/GameState.hpp>
#include <Math/Types.hpp>

#include <map>

namespace alba
{

namespace math
{

class GameWithMaze
{
public:

    // As an example, consider a game where the players move a figure in a maze.
    // Each square in the maze is either floor or wall.
    // On each turn, the player has to move the figure some number of steps left or up.
    // The winner of the game is the player who makes the last move.

    enum class Move
    {
        Left,
        Up
    };

    using Coordinate = std::pair<unsigned int, unsigned int>;
    using CoordinateWithMove = std::pair<Coordinate, Move>;
    using Coordinates = std::vector<Coordinate>;
    using BooleanMatrix = matrix::AlbaMatrix<bool>;
    using CoordinateWithMoveToGrundyNumberMap = std::map<CoordinateWithMove, UnsignedInteger>;

    GameWithMaze(BooleanMatrix const& isBlockedMatrix);

    UnsignedInteger getGrundyNumberAt(Coordinate const& coordinate);
    UnsignedInteger getGrundyNumberAt(CoordinateWithMove const& coordinateWithMove);
    GameState getGameStateAt(Coordinate const& coordinate);
    Coordinate getOptimalNextVertexAt(Coordinate const& coordinate);
    std::string getString();

private:
    SetOfUnsignedIntegers getNextGrundyNumbers(CoordinateWithMove const& coordinateWithMove);
    Coordinates getNextCoordinates(CoordinateWithMove const& coordinateWithMove) const;
    Coordinates getNextCoordinates(Coordinate const& coordinate) const;
    Move getPerpendicularMove(Move const move) const;
    void retrieveLeftCoordinates(Coordinates & retrievedCoordinates, Coordinate const& coordinate) const;
    void retrieveUpCoordinates(Coordinates & retrievedCoordinates, Coordinate const& coordinate) const;

    BooleanMatrix const& m_isBlockedMatrix;
    CoordinateWithMoveToGrundyNumberMap m_coordinateWithMoveToGrundyNumberMap; // dynamic programming
};

std::ostream & operator<<(std::ostream & out, GameWithMaze::Move const move);

}

}
