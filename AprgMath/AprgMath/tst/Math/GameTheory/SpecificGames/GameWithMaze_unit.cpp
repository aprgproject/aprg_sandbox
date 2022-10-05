#include <Math/GameTheory/SpecificGames/GameWithMaze.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba{

namespace math
{

namespace
{
using Coordinate = GameWithMaze::Coordinate;
using BooleanMatrix = GameWithMaze::BooleanMatrix;
}

TEST(GameWithMazeTest, Example1Works)
{
    GameWithMaze::BooleanMatrix isBlockedMatrix(5U, 5U,    {false, false, true, false, false,
     true, false, false, false, true,
     false, false, true, false, false,
     true, false, false, false, false,
     false, false, false, false, false});
    GameWithMaze gameWithMaze(isBlockedMatrix);

    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 0U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 1U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 2U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 3U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({0U, 4U}));
    EXPECT_EQ(1U, gameWithMaze.getGrundyNumberAt({1U, 0U}));
    EXPECT_EQ(0U, gameWithMaze.getGrundyNumberAt({1U, 1U}));
    EXPECT_EQ(2U, gameWithMaze.getGrundyNumberAt({1U, 2U}));
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
    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({0U, 2U}));    EXPECT_EQ(GameState::Losing, gameWithMaze.getGameStateAt({0U, 3U}));
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
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextVertexAt({0U, 0U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextVertexAt({0U, 1U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextVertexAt({0U, 2U}));
    EXPECT_EQ(Coordinate(0U, 2U), gameWithMaze.getOptimalNextVertexAt({0U, 3U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextVertexAt({0U, 4U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextVertexAt({1U, 0U}));
    EXPECT_EQ(Coordinate(1U, 0U), gameWithMaze.getOptimalNextVertexAt({1U, 1U}));
    EXPECT_EQ(Coordinate(0U, 2U), gameWithMaze.getOptimalNextVertexAt({1U, 2U}));
    EXPECT_EQ(Coordinate(1U, 1U), gameWithMaze.getOptimalNextVertexAt({1U, 3U}));
    EXPECT_EQ(Coordinate(0U, 4U), gameWithMaze.getOptimalNextVertexAt({1U, 4U}));
    EXPECT_EQ(Coordinate(1U, 0U), gameWithMaze.getOptimalNextVertexAt({2U, 0U}));
    EXPECT_EQ(Coordinate(1U, 1U), gameWithMaze.getOptimalNextVertexAt({2U, 1U}));
    EXPECT_EQ(Coordinate(1U, 2U), gameWithMaze.getOptimalNextVertexAt({2U, 2U}));
    EXPECT_EQ(Coordinate(1U, 3U), gameWithMaze.getOptimalNextVertexAt({2U, 3U}));
    EXPECT_EQ(Coordinate(0U, 4U), gameWithMaze.getOptimalNextVertexAt({2U, 4U}));
    EXPECT_EQ(Coordinate(0U, 0U), gameWithMaze.getOptimalNextVertexAt({3U, 0U}));
    EXPECT_EQ(Coordinate(1U, 1U), gameWithMaze.getOptimalNextVertexAt({3U, 1U}));
    EXPECT_EQ(Coordinate(3U, 0U), gameWithMaze.getOptimalNextVertexAt({3U, 2U}));
    EXPECT_EQ(Coordinate(2U, 3U), gameWithMaze.getOptimalNextVertexAt({3U, 3U}));
    EXPECT_EQ(Coordinate(0U, 4U), gameWithMaze.getOptimalNextVertexAt({3U, 4U}));
    EXPECT_EQ(Coordinate(3U, 0U), gameWithMaze.getOptimalNextVertexAt({4U, 0U}));
    EXPECT_EQ(Coordinate(3U, 1U), gameWithMaze.getOptimalNextVertexAt({4U, 1U}));
    EXPECT_EQ(Coordinate(3U, 2U), gameWithMaze.getOptimalNextVertexAt({4U, 2U}));
    EXPECT_EQ(Coordinate(2U, 3U), gameWithMaze.getOptimalNextVertexAt({4U, 3U}));
    EXPECT_EQ(Coordinate(0U, 4U), gameWithMaze.getOptimalNextVertexAt({4U, 4U}));
}

}

}