#include <Math/GameTheory/NimGame.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(NimGameTest, GetGameStateWorks)
{
    NimGame nimGame;

    EXPECT_EQ(GameState::Losing, nimGame.getGameState({0U, 0U, 0U}));
    EXPECT_EQ(GameState::Winning, nimGame.getGameState({10U, 12U, 5U}));
    EXPECT_EQ(GameState::Losing, nimGame.getGameState({9U, 12U, 5U}));
}

TEST(NimGameTest, GetOptimalNextStateWorks)
{
    NimGame nimGame;

    EXPECT_EQ((NimGame::NimState{0U, 0U, 0U}), nimGame.getOptimalNextState({0U, 0U, 0U}));
    EXPECT_EQ((NimGame::NimState{9U, 12U, 5U}), nimGame.getOptimalNextState({10U, 12U, 5U}));
    EXPECT_EQ((NimGame::NimState{8U, 12U, 5U}), nimGame.getOptimalNextState({9U, 12U, 5U}));
}

}

}
