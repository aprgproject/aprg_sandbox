#pragma once

#include <Math/GameTheory/SpecificGames/GameWithMaze.hpp>

#include <map>

namespace alba
{

namespace math
{

class MultipleGamesWithMaze
{
public:
    // Next we will assume that our game consists of subgames, and on each turn,
    // the player first chooses a subgame and then a move in the subgame.
    // The game ends when it is not possible to make any move in any subgame.
    // In this case, the Grundy number of a game is the nim sum of the Grundy numbers of the subgames.
    // The game can be played like a nim game by calculating all Grundy numbers for subgames and then their nim sum.
    // As an example, consider a game that consists of three mazes.
    // In this game, on each turn, the player chooses one of the mazes and then moves the figure in the maze.

    using Game = GameWithMaze;
    using Games = std::vector<GameWithMaze>;
    using BooleanMatrix = Game::BooleanMatrix;
    using Coordinate = Game::Coordinate;
    using Coordinates = Game::Coordinates;
    using GameIndexAndCoordinatePair = std::pair<UnsignedInteger, Coordinate>;

    bool hasNoMoves() const;
    UnsignedInteger getOverallGrundyNumber();
    GameState getGameState();
    GameIndexAndCoordinatePair getOptimalNextGameAndCoordinate();
    std::string getString();

    void setCoordinateAtGame(UnsignedInteger const gameIndex, Coordinate const& newCoordinate);
    void addGameWithMaze(BooleanMatrix const& isBlockedMatrix, Coordinate const& startingCoordinate);

private:
    UnsignedInteger getCombinedGrundyNumber();

    Games m_games;
    Coordinates m_coordinateInGames;};

}

}
