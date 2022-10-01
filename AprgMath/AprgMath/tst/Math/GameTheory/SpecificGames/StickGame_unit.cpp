#include <Math/GameTheory/SpecificGames/StickGame.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(StickGameTest, GetGameStateWorks)
{
    StickGame stickGame(3U);

    EXPECT_EQ(GameState::Losing, stickGame.getGameState(0U));
    EXPECT_EQ(GameState::Winning, stickGame.getGameState(1U));
    EXPECT_EQ(GameState::Winning, stickGame.getGameState(2U));
    EXPECT_EQ(GameState::Winning, stickGame.getGameState(3U));
    EXPECT_EQ(GameState::Losing, stickGame.getGameState(4U));
    EXPECT_EQ(GameState::Winning, stickGame.getGameState(5U));
    EXPECT_EQ(GameState::Winning, stickGame.getGameState(6U));
    EXPECT_EQ(GameState::Winning, stickGame.getGameState(7U));
    EXPECT_EQ(GameState::Losing, stickGame.getGameState(8U));
}

TEST(StickGameTest, GetOptimalNumberOfSticksToTakeWorks)
{
    StickGame stickGame(3U);

    EXPECT_EQ(0U, stickGame.getOptimalNumberOfSticksToTake(0U));
    EXPECT_EQ(1U, stickGame.getOptimalNumberOfSticksToTake(1U));
    EXPECT_EQ(2U, stickGame.getOptimalNumberOfSticksToTake(2U));
    EXPECT_EQ(3U, stickGame.getOptimalNumberOfSticksToTake(3U));
    EXPECT_EQ(1U, stickGame.getOptimalNumberOfSticksToTake(4U));
    EXPECT_EQ(1U, stickGame.getOptimalNumberOfSticksToTake(5U));
    EXPECT_EQ(2U, stickGame.getOptimalNumberOfSticksToTake(6U));
    EXPECT_EQ(3U, stickGame.getOptimalNumberOfSticksToTake(7U));
    EXPECT_EQ(1U, stickGame.getOptimalNumberOfSticksToTake(8U));
}

}

}
