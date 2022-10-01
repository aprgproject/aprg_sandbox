#include <Math/GameTheory/NimGame.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba
{

namespace math
{

TEST(NimGameTest, GetGameStateWorks)
{
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({10U, 12U, 5U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({9U, 12U, 5U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({8U, 12U, 5U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({8U, 12U, 4U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({7U, 12U, 4U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({7U, 3U, 4U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({6U, 3U, 4U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({6U, 2U, 4U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({5U, 2U, 4U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({5U, 1U, 4U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({4U, 1U, 4U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({4U, 0U, 4U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({3U, 0U, 4U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({3U, 0U, 3U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({2U, 0U, 3U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({2U, 0U, 2U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({1U, 0U, 2U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({1U, 0U, 1U}));
    EXPECT_EQ(GameState::Winning, NimGame::getGameState({0U, 0U, 1U}));
    EXPECT_EQ(GameState::Losing, NimGame::getGameState({0U, 0U, 0U}));
}

TEST(NimGameTest, GetOptimalNextStateWorks)
{
    EXPECT_EQ((NimState{9U, 12U, 5U}), NimGame::getOptimalNextState({10U, 12U, 5U}));
    EXPECT_EQ((NimState{8U, 12U, 5U}), NimGame::getOptimalNextState({9U, 12U, 5U}));
    EXPECT_EQ((NimState{8U, 12U, 4U}), NimGame::getOptimalNextState({8U, 12U, 5U}));
    EXPECT_EQ((NimState{7U, 12U, 4U}), NimGame::getOptimalNextState({8U, 12U, 4U}));
    EXPECT_EQ((NimState{7U, 3U, 4U}), NimGame::getOptimalNextState({7U, 12U, 4U}));
    EXPECT_EQ((NimState{6U, 3U, 4U}), NimGame::getOptimalNextState({7U, 3U, 4U}));
    EXPECT_EQ((NimState{6U, 2U, 4U}), NimGame::getOptimalNextState({6U, 3U, 4U}));
    EXPECT_EQ((NimState{5U, 2U, 4U}), NimGame::getOptimalNextState({6U, 2U, 4U}));
    EXPECT_EQ((NimState{5U, 1U, 4U}), NimGame::getOptimalNextState({5U, 2U, 4U}));
    EXPECT_EQ((NimState{4U, 1U, 4U}), NimGame::getOptimalNextState({5U, 1U, 4U}));
    EXPECT_EQ((NimState{4U, 0U, 4U}), NimGame::getOptimalNextState({4U, 1U, 4U}));
    EXPECT_EQ((NimState{3U, 0U, 4U}), NimGame::getOptimalNextState({4U, 0U, 4U}));
    EXPECT_EQ((NimState{3U, 0U, 3U}), NimGame::getOptimalNextState({3U, 0U, 4U}));
    EXPECT_EQ((NimState{2U, 0U, 3U}), NimGame::getOptimalNextState({3U, 0U, 3U}));
    EXPECT_EQ((NimState{2U, 0U, 2U}), NimGame::getOptimalNextState({2U, 0U, 3U}));
    EXPECT_EQ((NimState{1U, 0U, 2U}), NimGame::getOptimalNextState({2U, 0U, 2U}));
    EXPECT_EQ((NimState{1U, 0U, 1U}), NimGame::getOptimalNextState({1U, 0U, 2U}));
    EXPECT_EQ((NimState{0U, 0U, 1U}), NimGame::getOptimalNextState({1U, 0U, 1U}));
    EXPECT_EQ((NimState{0U, 0U, 0U}), NimGame::getOptimalNextState({0U, 0U, 1U}));
    EXPECT_EQ((NimState{0U, 0U, 0U}), NimGame::getOptimalNextState({0U, 0U, 0U}));
}

}

}
