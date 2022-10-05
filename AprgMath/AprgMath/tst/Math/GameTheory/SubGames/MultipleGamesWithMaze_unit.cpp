#include <Math/GameTheory/SubGames/MultipleGamesWithMaze.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

namespace
{
using BooleanMatrix = MultipleGamesWithMaze::BooleanMatrix;
using Coordinate = MultipleGamesWithMaze::Coordinate;
using GameIndexAndCoordinatePair = MultipleGamesWithMaze::GameIndexAndCoordinatePair;
}

TEST(MultipleGamesWithMazeTest, Example1Works)
{
    BooleanMatrix firstGameMatrix(5U, 5U,
    {false, false, true, false, false,
     true, false, false, false, true,
     false, false, true, false, false,
     true, false, false, false, false,
     false, false, false, false, false});
    BooleanMatrix secondGameMatrix(5U, 5U,
    {false, false, false, false, true,
     false, false, true, false, false,
     false, true, false, false, false,
     false, true, false, false, false,
     false, false, false, false, false});
    BooleanMatrix thirdGameMatrix(5U, 5U,
    {false, false, false, false, false,
     false, true, true, true, false,
     false, true, true, true, false,
     false, true, true, true, false,
     false, false, false, false, false});
    MultipleGamesWithMaze games;
    games.addGameWithMaze(firstGameMatrix, {4U, 4U});
    games.addGameWithMaze(secondGameMatrix, {4U, 4U});
    games.addGameWithMaze(thirdGameMatrix, {4U, 4U});

    EXPECT_EQ(GameState::Winning, games.getGameState());
    EXPECT_EQ(GameIndexAndCoordinatePair(0U, {0U, 4U}), games.getOptimalNextGameAndCoordinate());
    EXPECT_FALSE(games.hasNoMoves());
    games.setCoordinateAtGame(0U, {0U, 4U});

    EXPECT_EQ(GameState::Losing, games.getGameState());
    EXPECT_EQ(GameIndexAndCoordinatePair(1U, {1U, 4U}), games.getOptimalNextGameAndCoordinate());
    EXPECT_FALSE(games.hasNoMoves());
    games.setCoordinateAtGame(1U, {1U, 4U});

    EXPECT_EQ(GameState::Winning, games.getGameState());
    EXPECT_EQ(GameIndexAndCoordinatePair(2U, {1U, 4U}), games.getOptimalNextGameAndCoordinate());
    EXPECT_FALSE(games.hasNoMoves());
    games.setCoordinateAtGame(2U, {1U, 4U});

    EXPECT_EQ(GameState::Losing, games.getGameState());
    EXPECT_EQ(GameIndexAndCoordinatePair(1U, {0U, 4U}), games.getOptimalNextGameAndCoordinate());
    EXPECT_FALSE(games.hasNoMoves());
    games.setCoordinateAtGame(1U, {0U, 4U});

    EXPECT_EQ(GameState::Winning, games.getGameState());
    EXPECT_EQ(GameIndexAndCoordinatePair(1U, {0U, 0U}), games.getOptimalNextGameAndCoordinate());
    EXPECT_FALSE(games.hasNoMoves());
    games.setCoordinateAtGame(1U, {0U, 0U});

    EXPECT_EQ(GameState::Losing, games.getGameState());
    EXPECT_EQ(GameIndexAndCoordinatePair(2U, {0U, 4U}), games.getOptimalNextGameAndCoordinate());
    EXPECT_FALSE(games.hasNoMoves());
    games.setCoordinateAtGame(2U, {0U, 4U});

    EXPECT_EQ(GameState::Winning, games.getGameState());
    EXPECT_EQ(GameIndexAndCoordinatePair(2U, {0U, 0U}), games.getOptimalNextGameAndCoordinate());
    EXPECT_FALSE(games.hasNoMoves());
    games.setCoordinateAtGame(2U, {0U, 0U});

    EXPECT_EQ(GameState::Losing, games.getGameState());
    EXPECT_EQ(GameIndexAndCoordinatePair(0U, {0U, 0U}), games.getOptimalNextGameAndCoordinate());
    EXPECT_TRUE(games.hasNoMoves());
    games.setCoordinateAtGame(0U, {0U, 0U});
}

}

}
