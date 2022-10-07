#include <Math/GameTheory/SpecificGames/GameWithMaze.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

namespace
{
using BooleanMatrix = GameWithMaze::BooleanMatrix;
using Coordinate = GameWithMaze::Coordinate;
}

TEST(GameWithMazeTest, Example1Works)
{
    BooleanMatrix isBlockedMatrix(5U, 5U,
    {false, false, true, false, false,
     true, false, false, false, true,
     false, false, true, false, false,
     true, false, false, false, false,
     false, false, false, false, false});
    GameWithMaze gameWithMaze(isBlockedMatrix);
    EXPECT_TRUE(gameWithMaze.hasNoMoves({0U, 0U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({0U, 1U}));
    EXPECT_TRUE(gameWithMaze.hasNoMoves({0U, 2U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({0U, 3U}));
    EXPECT_TRUE(gameWithMaze.hasNoMoves({0U, 4U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({1U, 0U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({1U, 1U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({1U, 2U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({1U, 3U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({1U, 4U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({2U, 0U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({2U, 1U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({2U, 2U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({2U, 3U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({2U, 4U}));
    EXPECT_TRUE(gameWithMaze.hasNoMoves({3U, 0U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({3U, 1U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({3U, 2U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({3U, 3U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({3U, 4U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({4U, 0U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({4U, 1U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({4U, 2U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({4U, 3U}));
    EXPECT_FALSE(gameWithMaze.hasNoMoves({4U, 4U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 0U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 1U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 2U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 3U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 4U}));
    EXPECT_EQ(1U, gameWithMaze.getGrundyNumberAt({1U, 0U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({1U, 1U}));    EXPECT_EQ(2U, gameWithMaze.getGrundyNumberAt({1U, 2U}));
    EXPECT_EQ(3U, gameWithMaze.getGrundyNumberAt({1U, 3U}));
    EXPECT_EQ(4U, gameWithMaze.getGrundyNumberAt({1U, 4U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({2U, 0U}));
    EXPECT_EQ(1U, gameWithMaze.getGrundyNumberAt({2U, 1U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({2U, 2U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({2U, 3U}));
    EXPECT_EQ(1U, gameWithMaze.getGrundyNumberAt({2U, 4U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({3U, 0U}));
    EXPECT_EQ(2U, gameWithMaze.getGrundyNumberAt({3U, 1U}));
    EXPECT_EQ(1U, gameWithMaze.getGrundyNumberAt({3U, 2U}));
    EXPECT_EQ(4U, gameWithMaze.getGrundyNumberAt({3U, 3U}));
    EXPECT_EQ(3U, gameWithMaze.getGrundyNumberAt({3U, 4U}));
    EXPECT_EQ(1U, gameWithMaze.getGrundyNumberAt({4U, 0U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({4U, 1U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({4U, 2U}));
    EXPECT_EQ(1U, gameWithMaze.getGrundyNumberAt({4U, 3U}));
    EXPECT_EQ(2U, gameWithMaze.getGrundyNumberAt({4U, 4U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({0U, 0U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({0U, 1U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({0U, 2U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({0U, 3U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({0U, 4U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({1U, 0U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({1U, 1U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({1U, 2U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({1U, 3U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({1U, 4U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({2U, 0U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({2U, 1U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({2U, 2U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({2U, 3U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({2U, 4U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({3U, 0U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({3U, 1U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({3U, 2U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({3U, 3U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({3U, 4U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({4U, 0U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({4U, 1U}));
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({4U, 2U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({4U, 3U}));
    EXPECT_EQ(GameState::Winning, gameWithMaze.getGameStateAt({4U, 4U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextCoordinateAt({0U, 0U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextCoordinateAt({0U, 1U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextCoordinateAt({0U, 2U}));
    EXPECT_EQ(Coordinate(0U, 2U), gameWithMaze.getOptimalNextCoordinateAt({0U, 3U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextCoordinateAt({0U, 4U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextCoordinateAt({1U, 0U}));
    EXPECT_EQ(Coordinate(1U, 0U), gameWithMaze.getOptimalNextCoordinateAt({1U, 1U}));
    EXPECT_EQ(Coordinate(0U, 2U), gameWithMaze.getOptimalNextCoordinateAt({1U, 2U}));
    EXPECT_EQ(Coordinate(1U, 1U), gameWithMaze.getOptimalNextCoordinateAt({1U, 3U}));
    EXPECT_EQ(Coordinate(0U, 4U), gameWithMaze.getOptimalNextCoordinateAt({1U, 4U}));
    EXPECT_EQ(Coordinate(1U, 0U), gameWithMaze.getOptimalNextCoordinateAt({2U, 0U}));
    EXPECT_EQ(Coordinate(1U, 1U), gameWithMaze.getOptimalNextCoordinateAt({2U, 1U}));
    EXPECT_EQ(Coordinate(1U, 2U), gameWithMaze.getOptimalNextCoordinateAt({2U, 2U}));
    EXPECT_EQ(Coordinate(1U, 3U), gameWithMaze.getOptimalNextCoordinateAt({2U, 3U}));
    EXPECT_EQ(Coordinate(0U, 4U), gameWithMaze.getOptimalNextCoordinateAt({2U, 4U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextCoordinateAt({3U, 0U}));
    EXPECT_EQ(Coordinate(1U, 1U), gameWithMaze.getOptimalNextCoordinateAt({3U, 1U}));
    EXPECT_EQ(Coordinate(3U, 0U), gameWithMaze.getOptimalNextCoordinateAt({3U, 2U}));
    EXPECT_EQ(Coordinate(2U, 3U), gameWithMaze.getOptimalNextCoordinateAt({3U, 3U}));
    EXPECT_EQ(Coordinate(0U, 4U), gameWithMaze.getOptimalNextCoordinateAt({3U, 4U}));
    EXPECT_EQ(Coordinate(3U, 0U), gameWithMaze.getOptimalNextCoordinateAt({4U, 0U}));
    EXPECT_EQ(Coordinate(3U, 1U), gameWithMaze.getOptimalNextCoordinateAt({4U, 1U}));
    EXPECT_EQ(Coordinate(3U, 2U), gameWithMaze.getOptimalNextCoordinateAt({4U, 2U}));
    EXPECT_EQ(Coordinate(2U, 3U), gameWithMaze.getOptimalNextCoordinateAt({4U, 3U}));
    EXPECT_EQ(Coordinate(0U, 4U), gameWithMaze.getOptimalNextCoordinateAt({4U, 4U}));
}

}

}