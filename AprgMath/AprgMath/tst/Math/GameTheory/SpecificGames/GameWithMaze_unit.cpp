#include <Math/GameTheory/SpecificGames/GameWithMaze.hpp>

#include <gtest/gtest.h>



#include <Common/Debug/AlbaDebug.hpp>

using namespace std;

namespace alba
{

namespace math
{

TEST(GameWithMazeTest, Example1Works)
{
    GameWithMaze::BooleanMatrix isBlockedMatrix(5U, 5U,
    {false, false, true, false, false,
     true, false, false, false, true,
     false, false, true, false, false,
     true, false, false, false, false,
     false, false, false, false, false});
    GameWithMaze gameWithMaze(isBlockedMatrix);

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
    EXPECT_EQ(3U, gameWithMaze.getGrundyNumberAt({4U, 4U}));
    ALBA_PRINT1(gameWithMaze.getString());
}
}

}