#include <Math/GameTheory/NimGame.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(NimGameTest, GetGameStateWorks)
{
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({0U, 0U, 0U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({10U, 12U, 5U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({9U, 12U, 5U}));
}

TEST(NimGameTest, GetOptimalNextStateWorks){
    NimGame nimGame;

    EXPECT_EQ((NimGame::NimState{0U, 0U, 0U}), NimGame::getOptimalNextState({0U, 0U, 0U}));
    EXPECT_EQ((NimGame::NimState{9U, 12U, 5U}), NimGame::getOptimalNextState({10U, 12U, 5U}));
    EXPECT_EQ((NimGame::NimState{8U, 12U, 5U}), NimGame::getOptimalNextState({9U, 12U, 5U}));
}

}
}